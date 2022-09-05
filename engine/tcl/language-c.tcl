#
# Copyright (c) 2010-2018,2020,2022 LAAS/CNRS
# All rights reserved.
#
# Redistribution  and  use  in  source  and binary  forms,  with  or  without
# modification, are permitted provided that the following conditions are met:
#
#   1. Redistributions of  source  code must retain the  above copyright
#      notice and this list of conditions.
#   2. Redistributions in binary form must reproduce the above copyright
#      notice and  this list of  conditions in the  documentation and/or
#      other materials provided with the distribution.
#
# THE SOFTWARE  IS PROVIDED "AS IS"  AND THE AUTHOR  DISCLAIMS ALL WARRANTIES
# WITH  REGARD   TO  THIS  SOFTWARE  INCLUDING  ALL   IMPLIED  WARRANTIES  OF
# MERCHANTABILITY AND  FITNESS.  IN NO EVENT  SHALL THE AUTHOR  BE LIABLE FOR
# ANY  SPECIAL, DIRECT,  INDIRECT, OR  CONSEQUENTIAL DAMAGES  OR  ANY DAMAGES
# WHATSOEVER  RESULTING FROM  LOSS OF  USE, DATA  OR PROFITS,  WHETHER  IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR  OTHER TORTIOUS ACTION, ARISING OUT OF OR
# IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#
#                                           Anthony Mallet on Tue Jan 26 2010
#
package require Tcl 8.5

namespace eval language::c {

    # --- filext -----------------------------------------------------------

    # Return the canonical file extensions in C
    #
    proc fileext { kind } {
	if {$kind == "header"} { return ".h" } else { return ".c" }
    }


    # --- comment ----------------------------------------------------------

    # Return a string that is a valid comment in C.
    #
    proc comment { text } {
      return [string map {**/ */} /*[join [split $text "\n"] "\n *"]*/]
    }


    # --- mapping ----------------------------------------------------------

    # Return the C mapping of types or codels
    #
    proc mapping { objects locations } {
      set m ""

      foreach obj $objects {
        switch -- [$obj class] {
          type {
            switch -- [$obj kind] {
              {const}		{ append m [genconst $obj $locations] }
              {enum}		{ append m [genenum $obj $locations] }
              {struct}		{ append m [genstruct $obj $locations] }
              {union}		{ append m [genunion $obj $locations] }
              {typedef}		{ append m [gentypedef $obj $locations] }
              {sequence}	{ append m [gensequence $obj $locations] }
              {optional}	{ append m [genoptional $obj $locations] }
              {exception}	{ append m [genexception $obj $locations] }

              {forward struct} -
              {forward union}	{ append m [genforward $obj $locations] }

              {pause event} -
              {event}		{ append m [genevent $obj $locations] }

              {port}		{ append m [genport $obj $locations] }
              {remote}		{ append m [genremote $obj $locations] }
              {native}		{ append m [gennative $obj $locations] }
            }
          }

          codel {
            append m "\n#ifdef __cplusplus"
            append m "\nextern \"C\" {"
            append m "\n#endif"
            append m "\n[signature $obj " " $locations];"
            append m "\n#ifdef __cplusplus"
            append m "\n}"
            append m "\n#endif"
          }
        }
      }

      set p ""
      if {[regexp {u?int(8|16|32|64)_t} $m]} {
        append p "#include <stdint.h>\n"
      }
      if {[regexp {bool} $m]} {
        append p "#include <stdbool.h>\n"
      }
      if {[regexp {sequence} $m]} {
        append p "#include \"genom3/c/idlsequence.h\"\n"
      }
      if {[regexp {genom_context} $m]} {
        append p "#include \"genom3/c/context.h\"\n"
      }

      return $p$m
    }


    # --- declarator -------------------------------------------------------

    # Return the C mapping of a type declarator.
    #
    proc declarator { type {var {}} } {
	switch -- [$type kind] {
	    {boolean}			{ set d "bool" }
	    {unsigned short}		{ set d "uint16_t" }
	    {short}			{ set d "int16_t" }
	    {unsigned long}		{ set d "uint32_t" }
	    {unsigned long long}	{ set d "uint64_t" }
	    {long}			{ set d "int32_t" }
	    {long long}			{ set d "int64_t" }
	    {float}			{ set d "float" }
	    {double}			{ set d "double" }
	    {char}			{ set d "int8_t" }
	    {octet}			{ set d "uint8_t" }
            {event}			{ set d "genom_event" }
	    {any}			{ error "type any not supported yet" }

            {native}			{ set d "[$type cname] *" }
            {exception}			{ set d [$type cname]_detail }

	    {const}			-
	    {enum}			-
	    {struct}			-
	    {union}			-
	    {typedef}			-
            {port}			-
            {remote}			{ set d [$type cname] }

	    {enumerator}		-
	    {struct member}		-
	    {union member}		-
	    {forward struct}		-
	    {forward union}		{ set d [declarator [$type type]] }

	    {string} {
		if {[catch { $type length } l]} {
		    set d "char *"
		} else {
		    set d "char\[$l\]"
		}
	    }

	    {array} {
		if {[catch { $type length } l]} { set l {} }
		set d "[declarator [$type type]]"
                set b [string first \[ $d]
                if {$b < 0} {
                  append d "\[$l\]"
                } else {
                  set d "[string range $d 0 $b-1]\[$l\][string range $d $b end]"
                }
	    }

            sequence - optional {
              set t [$type type]

              set d [$type kind]
              if {![catch {$type length} l]} {
                append d $l
              }

              if {[catch {$t fullname}]} {
                append d [cname " [cname [$t kind]]"]
              } else {
                append d [cname " [cname [$t fullname]]"]
              }
              if {![catch {$t length} l]} { append d $l }
              while {[$t kind] == "sequence" || [$t kind] == "optional"} {
                set t [$t type]
                if {[catch {$t fullname}]} {
                  append d [cname " [cname [$t kind]]"]
                } else {
                  append d [cname " [cname [$t fullname]]"]
                }
                if {![catch {$t length} l]} { append d $l }
              }
            }

	    default {
		template fatal "internal error: unhandled type '[$type kind]'"
	    }
	}

	if {[string length $var] > 0} { set d [cdecl $d $var] }
	return $d
    }


    # --- address ----------------------------------------------------------

    # Return the C mapping of a variable address.
    #
    proc address { type {var {}} } {
      switch -- [[$type final] kind] {
        string - array - native	{ return $var }
        default			{ return &($var) }
      }
    }


    # --- dereference ------------------------------------------------------

    # Return the C mapping for dereferencing a parameter passed by value or
    # reference.
    #
    proc dereference { type kind {var {}} } {
      switch -- $kind {
        {value}		{
          switch -- [[$type final] kind] {
            sequence - optional - struct - union - exception - port - remote {
              return *($var)
            }
            default {
              return $var
            }
          }
        }
        {reference}	{
          switch -- [[$type final] kind] {
            string - array {
              if {[catch {[$type final] length}]} {
                return "*($var)"
              } else {
                return $var
              }
            }
            default {
              return "*($var)"
            }
          }
        }
        default	{
          template fatal \
              "unknown argument kind \"$kind\": must be value or reference"
        }
      }
    }


    # --- argument ---------------------------------------------------------

    # Return the C mapping for declaring a parameter.
    #
    proc argument { type kind {var {}} } {
      switch -- $kind {
        {value}		{
          switch -- [[$type final] kind] {
             sequence - optional - struct - union - exception - port - remote {
               return "const [declarator $type *$var]"
             }
             string - array - native {
               return "const [declarator $type $var]"
             }
             default {
               return [declarator $type $var]
             }
           }
        }
        {reference}	{
          switch -- [[$type final] kind] {
            string - array {
              if {[catch { [$type final] length }]} {
                return [declarator $type *$var]
              } else {
                return [declarator $type $var]
              }
            }
            default {
              return [declarator $type *$var]
            }
          }
        }

        default	{
          template fatal \
              "unknown argument kind \"$kind\": must be value or reference"
        }
      }
    }


    # --- return-value -----------------------------------------------------

    # Return the C mapping for declaring a returned value.
    #
    proc return-value { type kind } {
      switch -- $kind {
        reference {
          switch -- [[$type final] kind] {
            string {
              # handle char[] explicitly
              if {![catch { [$type final] length }]} {
                return "char *"
              }
            }
            string - array {
              # handle arrays[] explicitly
              if {![catch { [$type final] length }]} {
                return [declarator [[$type final] type] *]
              }
            }
          }
        }
      }

      # default to same as 'argument'
      return [argument $type $kind]
    }


    # --- pass -------------------------------------------------------------

    # Return the C mapping for passing a variable.
    #
    proc pass { type kind {var {}} } {
      set ftype [$type final]
      switch -- $kind {
        {value}		{
          switch -- [$ftype kind] {
            array {
              switch -- [[[$ftype type] final] kind] {
                array - string {
                  # need explicit cast to const type **.
                  # see http://c-faq.com/ansi/constmismatch.html
                  return "((const [[$ftype type] declarator (*)])$var)"
                }
              }
            }
            sequence - optional - struct - union - exception - port - remote {
              return &($var)
            }
          }
          return $var
        }
        {reference}	{
          switch -- [$ftype kind] {
            string - array {
              if {[catch {$ftype length}]} {
                return "&($var)"
              } else {
                return $var
              }
            }
            default {
              return "&($var)"
            }
          }
        }
        default	{
          template fatal \
              "unknown argument kind \"$kind\": must be value or reference"
        }
      }
    }


    # --- signature --------------------------------------------------------

    # Return the C signature of a codel
    #
    proc signature { codel {symchar " "} {location 0}} {
	set ret genom_event
	set sym [cname $codel]
	set arg [list]
	foreach p [$codel parameters] {
          set a ""
          switch -glob -- [$p dir]/[$p src] {
            in/* - */port - */remote {
              append a [[$p type] argument value [$p name]]
            }
            inout/* - out/* {
              append a [[$p type] argument reference [$p name]]
            }
          }
          lappend arg $a
	}
        lappend arg {const genom_context self}

        set m ""
        if {$location} {
	  append m [genloc $codel]\n
	}
        set p [string repeat " " [string length "${sym}("]]
        set sig [wrap "${sym}([join $arg {, }])" $p ,]
        append m [join [list $ret $sig] $symchar]
	return $m
    }


    # --- member -----------------------------------------------------------

    # Return the C construction to access members of type
    #
    proc member { type mlist } {
      if {[llength $mlist] == 0} return ""
      set mlist [lassign $mlist member]

      switch -- [$type kind] {
        {boolean}				-
        {unsigned short} - {short}		-
        {unsigned long} - {long}		-
        {unsigned long long} - {long long}	-
        {float} - {double}			-
        {char} - {octet}			-
        {enum} - {enumerator} - {string} {
          # basic types: no member
          template fatal "[$type kind] has no member"
        }

        {array} {
          append access "\[$member\]"
          set type [$type type]
        }

        {sequence} {
          append access "._buffer\[$member\]"
          set type [$type type]
        }

        {struct} - {exception} {
          set m [$type members $member]
          if {[llength $m] == 0} {
            template fatal "[$type kind] has no member $member"
          }
          append access ".$member"
          set type $m
        }

        {union} {
          set m [$type members $member]
          if {[llength $m] == 0} {
            template fatal "[$type kind] has no member $member"
          }
          append access "._u.$member"
          set type $m
        }

        optional {
          set type [$type type]
          append access "._value"
          set mlist [concat $member $mlist]
        }

        {forward struct} - {forward union}	-
        {struct member} - {union member}	-
        {typedef} {
          set type [$type type]
          set mlist [concat $member $mlist]
        }

        default { error "internal error: unhandled type '[$type kind]'" }
      }

      if {[llength $mlist] > 0} {
        append access [member $type $mlist]
      }

      return $access
    }


    # --- invoke -----------------------------------------------------------

    # Return the C invocation of a codel
    #
    proc invoke { codel params } {
      if {[llength $params] != 1 + [llength [$codel parameters]]} {
        template fatal [subst [join {
          "wrong # arguments in \"[$codel name] invoke\":"
          "[join $params {, }]"
          "expecting:"
          "[signature $codel]"
        } "\n"]]
      }

      set sym [cname $codel]
      return "${sym}([join $params {, }])"
    }


    # --- genconst ---------------------------------------------------------

    # Return the C mapping of a const
    #
    proc genconst { type locations } {
        if {[catch {$type fullname}]} return ""

	set n [cname [$type fullname]]
	set t [declarator [$type type]]

	set v [$type value]
	switch [$type valuekind] {
	    bool	{ set v [expr {$v?"true":"false"}] }
	    char	{ set v "'$v'" }
	    string	{ set v "\"[string map {\" \\\"} $v]\"" }
	    enum	{ set v [cname $v] }
	}

        if {$locations} { append m [genloc $type] }
	append m "\nstatic const $t $n = $v;"
	return [guard $m $n]
    }


    # --- genenum ----------------------------------------------------------

    # Return the C mapping of an enum.
    #
    proc genenum { type locations } {
      set n [cname [$type fullname]]

      if {$locations} { append m [genloc $type] }
      append m "\ntypedef uint32_t $n;"
      append m "\nenum {"
      set v -1
      set comma {}
      foreach e [$type members] {
        append m "${comma}"
        if {$locations} { append m [genloc $e] }
        append m "\n  [cname [$e fullname]] =\t[incr v]"
        set comma ,
      }
      append m "\n};"
      return [guard $m $n]
    }


    # --- gensequence ------------------------------------------------------

    # Return the C mapping of a sequence.
    #
    proc gensequence { type locations } {
	set n [declarator $type]

	set f ""
        switch [[$type type] kind] {
          sequence { append f [gensequence [$type type] $locations] }
          optional { append f [genoptional [$type type] $locations] }
        }

        if {$locations} { append m [genloc $type] }
	append m "\ntypedef struct $n {"
        append m "\n  uint32_t _maximum, _length;"
	if {[catch {$type length} l]} {
	    append m "\n  [declarator [$type type] *_buffer];"
	    append m "\n  void (*_release)(void *_buffer);"
	} else {
	    append m "\n  [declarator [$type type] _buffer\[$l\]];"
	}
	append m "\n} $n;"
	return $f[guard $m $n]
    }


    # --- genoptional ------------------------------------------------------

    # Return the C mapping of an optional.
    #
    proc genoptional { type locations } {
      set n [declarator $type]

      set f ""
      switch [[$type type] kind] {
        sequence { append f [gensequence [$type type] $locations] }
        optional { append f [genoptional [$type type] $locations] }
      }

      if {$locations} { append m [genloc $type] }
      append m "\ntypedef struct $n {"
      append m "\n  bool _present;"
      append m "\n  [declarator [$type type] _value];"
      append m "\n} $n;"
      return $f[guard $m $n]
    }


    # --- genstruct --------------------------------------------------------

    # Return the C mapping of a struct. The typedef is output first to handle
    # recursive structures with anonymous sequences.
    #
    proc genstruct { type locations } {
	set n [cname [$type fullname]]

        if {$locations} { append m [genloc $type] }
	append m "\ntypedef struct $n $n;"

	set f ""
	set s "\nstruct $n {"
	foreach e [$type members] {
          if {$locations} { append s [genloc $e] }
	    append s "\n [declarator $e [cname [$e name]]];"
            switch [[$e type] kind] {
              sequence { append f [gensequence [$e type] $locations] }
              optional { append f [genoptional [$e type] $locations] }
            }
	}
	append s "\n};"
	return [guard $m $n]$f[guard $s "${n}_definition"]
    }


    # --- genunion ---------------------------------------------------------

    # Return the C mapping of a union. The typedef is output first to handle
    # recursive and forward decls.
    #
    proc genunion { type locations } {
	set n [cname [$type fullname]]
	set discr [$type discriminator]

        if {$locations} { append m [genloc $type] }
	append m "\ntypedef struct $n $n;"

	set f ""
	append s "\nstruct $n {"
        if {$locations} { append s [genloc $discr] }
	append s "\n [declarator $discr] _d;"
	append s "\n union {"
	foreach e [$type members] {
            if {$locations} { append s [genloc $e] }
	    append s "\n  [declarator $e [cname [$e name]]];"
            switch [[$e type] kind] {
              sequence { append f [gensequence [$e type] $locations] }
              optional { append f [genoptional [$e type] $locations] }
            }
	}
	append s "\n } _u;"
	append s "\n};"
	return [guard $m $n]$f[guard $s "${n}_definition"]
    }


    # --- genexception -----------------------------------------------------

    # Return the C mapping of an exception.
    #
    proc genexception { type locations } {
      set n [$type cname]
      set f ""
      set s ""

      append m "\n#include \"genom3/c/exception.h\""
      if {$locations} { append m [genloc $type] }
      append m "\nconst char genom_extern_weak "
      append m "${n}_id\[\] = \"[$type fullname]\";"

      if {$locations} { append m [genloc $type] }
      if {[llength [$type members]]} {
        append m "\ntypedef struct ${n}_detail ${n}_detail;"

        append s "\nstruct ${n}_detail {"
        foreach e [$type members] {
          if {$locations} { append s [genloc $e] }
          append s "\n [declarator $e [$e name]];"
          switch [[$e type] kind] {
            sequence { append f [gensequence [$e type] $locations] }
            optional { append f [genoptional [$e type] $locations] }
          }
        }
        append s "\n};"

        append s "\nstatic inline genom_event"
        append s "\n${n}(${n}_detail *d, genom_context self) {"
        append s "\n return self->raise(${n}_id, d, sizeof(*d), self);"
        append s "\n}"
      } else {
        append m "\ntypedef void ${n}_detail;"

        append s "\nstatic inline genom_event"
        append s "\n${n}(genom_context self) {"
        append s "\n return self->raise(${n}_id, NULL, 0, self);"
        append s "\n}"
      }

      return [guard $m $n]$f[guard $s "${n}_definition"]
    }


    # --- genforward -------------------------------------------------------

    # Return the C mapping of forward declaration.
    #
    proc genforward { type locations } {
	set n [cname [$type fullname]]

        if {$locations} { append m [genloc $type] }
	append m "\ntypedef struct $n $n;"
	return [guard $m $n]
    }


    # --- genevent ---------------------------------------------------------

    # Return the C mapping of an event.
    #
    proc genevent { type locations } {
      set n [$type cname]
      append m "\n#include \"genom3/c/exception.h\""
      if {$locations} { append m [genloc $type] }
      append m "\nconst char genom_extern_weak $n\[\] = \"[$type fullname]\";"
      return [guard $m $n]
    }


    # --- genport ----------------------------------------------------------

    # Return the C mapping of a port.
    #
    proc genport { type locations } {
      set n [declarator $type]
      set p [$type port]
      set t [$p datatype]

      set f ""
      if {[$t kind] eq "sequence"} {
        append f [gensequence $t $locations]
      }

      append m "\n#include \"genom3/c/exception.h\""
      if {$locations} { append m [genloc $type] }
      append m "\ntypedef struct $n {"
      set rval [$t return-value reference]
      switch -- [$p kind]/[$p dir] {
        simple/in {
          append m "\n  $rval (*data)(genom_context self);"
          append m "\n  genom_event (*read)(genom_context self);"
        }
        simple/out {
          append m "\n  $rval (*data)(genom_context self);"
          append m "\n  genom_event (*write)(genom_context self);"
        }

        multiple/in {
          append m "\n  $rval (*data)(const char *id, genom_context self);"
          append m "\n  genom_event (*read)"
          append m   "(const char *id, genom_context self);"
        }

        multiple/out {
          append m "\n  $rval (*data)(const char *id, genom_context self);"
          append m "\n  genom_event (*write)"
          append m   "(const char *id, genom_context self);"
          append m "\n  genom_event (*open)"
          append m   "(const char *id, genom_context self);"
          append m "\n  genom_event (*close)"
          append m   "(const char *id, genom_context self);"
        }

        default	{ error "invalid port direction" }
      }
      append m "\n} $n;"
      return $f[guard $m $n]
    }


    # --- genremote --------------------------------------------------------

    # Return the C mapping of a remote.
    #
    proc genremote { type locations } {
      set n [declarator $type]
      set r [$type remote]

      set f ""
      set arg [list]
      foreach p [$r parameters] {
        switch -- [$p dir] {
          in		{ set a [[$p type] argument value [$p name]] }
          out - inout	{ set a [[$p type] argument reference [$p name]] }
          default	{ template fatal "invalid parameter direction" }
        }
        lappend arg $a

        if {[[$p type] kind] eq "sequence"} {
          append f [gensequence [$p type] $locations]
        }
      }
      lappend arg {genom_context self}

      append m "\n#include \"genom3/c/exception.h\""
      if {$locations} { append m [genloc $type] }
      append m "\ntypedef struct $n {"
      append m "\n  genom_event (*call)([join $arg {, }]);"
      append m "\n} $n;"
      return $f[guard $m $n]
    }


    # --- gennative --------------------------------------------------------

    # Return the C mapping of a native.
    #
    proc gennative { type locations } {
      set n [cname [$type fullname]]

      if {$locations} { append m [genloc $type] }
      append m "\ntypedef struct $n $n;"

      return [guard $m $n]
    }


    # --- gentypedef -------------------------------------------------------

    # Return the C mapping of a typedef.
    #
    proc gentypedef { type locations } {
	set n [cname [$type fullname]]

	set f ""
        switch [[$type type] kind] {
          sequence { append f [gensequence [$type type] $locations] }
          optional { append f [genoptional [$type type] $locations] }
        }

        if {$locations} { append m [genloc $type] }
	append m "\ntypedef [declarator [$type type] $n];"
	return $f[guard $m $n]
    }


    # --- genloc -----------------------------------------------------------

    # Return the C mapping of a source location
    #
    proc genloc { type } {
	if {[catch {$type loc} tloc]} { return "" }

	set f [lindex $tloc 0]
	set l [lindex $tloc 1]
	return "\n#line $l \"[string map {\" \\\"} $f]\""
    }


    # --- guard -----------------------------------------------------------

    # Protect a string with guards
    #
    proc guard { string name } {
	append m "\n#ifndef _${name}_c_type"
	append m "\n# define _${name}_c_type"
	append m $string
	append m "\n#endif /* _${name}_c_type */"
	append m "\n"
	return $m
    }


    # --- cdecl ------------------------------------------------------------

    # Given a type string and a name, declare name of type type. The subtlety
    # comes from arrays, because name should preceede the brackets, if any.
    #
    proc cdecl { type name } {
      set b [string first \[ $type]
      if { $b < 0 } {
        set pre $type
        set post ""
      } else {
        set pre [string range $type 0 $b-1]
        set post [string range $type $b end]
        if {[string index $name 0] eq "*"} {
          set name "($name)"
        }
      }

      if {[string index $pre end] eq "*"} {
        return "$pre$name$post"
      }
      return "$pre $name$post"
    }


    # --- cname ------------------------------------------------------------

    # Cannonical name of an object or string in C.
    # Remove leading :: and map other :: to _
    #
    proc cname { object } {
	if {![catch {$object class} class]} {
	    switch -- $class {
              codel	{ set object [$object name] }
              type	{ set object [$object fullname] }
	    }
	}

	if { [string first :: $object] == 0 } {
	    set object [string range $object 2 end]
	}

	return [string map {:: _ { } _ + x} $object]
    }
}
