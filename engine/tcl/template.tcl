#
# Copyright (c) 2010-2015,2017,2020,2023 LAAS/CNRS
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
#                                           Anthony Mallet on Fri Jan  8 2010
#

namespace eval template {
    #/
    # == *template* TCL engine command

    # default template options: just -h
    variable options {
	-h - --help {
	    template fatal "no options available for this template"
	}
    }

    # default usage message
    variable usage "Supported options:\n  -h.--help\t\tprint usage summary"

    # set to 1 when options have been parsed
    variable gotopt	0

    # save template options
    variable args [set ::argv]

    # save template processed files (dependencies)
    variable deps [list]


    # --- require ----------------------------------------------------------

    #/
    # [[template_require]]
    # === *template require* 'file'
    #
    # Source tcl 'file' and make its content available to the template
    # files. The file name can be absolute or relative. If it is relative, it
    # is interpreted as relative to the template directory
    # (link:dotgen{outfilesuffix}#dotgen_template_dir[`dotgen template dir`]).
    #
    # .Arguments
    # [horizontal]
    # 'file'::
    # Tcl input file to source. Any procedure that it creates is made available
    # to the template files.
    #
    proc require { src } {
      variable deps

      set path [file join [dotgen template dir] $src]
      template message "sourcing $path"

      uplevel #0 [list apply { { src path } {
        if {[catch {
          gsource $path
          slave eval gsource $path
        } m c]} {
          template fatal -2 "$src:[dict get $c -errorline] $m"
        }
      } } $src $path]

      set path [file normalize $path]
      if {$path ni $deps} {
        lappend deps $path
      }
    }
    namespace export require


    # --- parse ------------------------------------------------------------

    #/
    # [[template_parse]]
    # === *template parse* [args 'list'] [perm 'mode'] [{file|string|raw}] 'file' ...]
    #
    # This is the main template function that parses a template source file and
    # instanciate it, writing the result into the current template directory
    # (or in a global variable). This procedure should be invoked for each
    # source file that form a `genom` template.
    #
    # When invoking `template parse`, the last two arguments are the
    # destination file or string. A destination file is specified as `file`
    # 'file' (the filename is relative to the current template output
    # directory). Alternatively, a destination string is specified as `string`
    # 'var', where 'var' is the name of a global variable in which the template
    # engine will store the result of the source instantiation.
    #
    # The output destination file or string is generated by the template from
    # one or several input source. An input source is typically a source file,
    # but it can also be a string or raw (unprocessed) text. An input source
    # file is specified with `file` 'file', where 'file' is a file name
    # relative to the template directory. An input source read from a string is
    # specified as `string` 'text', where 'text' is the text processed by the
    # template engine. Finally, a raw, unprocessed source that is copied
    # verbatim to the destination is specified as `raw` 'text', where 'text' is
    # the text to be output.
    #
    # Additionnaly, each input source, defined as above, can be passed a list
    # of optional arguments by using the special `args` 'list' construction as
    # the first argument of the `template parse` command. The list given after
    # `args` can be retrieved from within the processed template source files
    # from the usual `argv` variable.
    #
    # .Arguments
    # [horizontal]
    # +args+ 'list'::
    # This optional argument should be followed by a list of arguments to pass
    # to the template source file. It should be the very first argument,
    # otherwise it is ignored. Each element of the list is available from the
    # template source file in the 'argv' array.
    #
    # +perm+ 'mode'::
    # This optional argument may be set to specify the permissions to be set
    # for the created file.
    #
    # .Examples
    # ----
    # template parse file mysrc file mydst
    # ----
    # Will parse the input file `mysrc`, process it and save the result in
    # `mydst`.
    #
    # ----
    # template parse args {one two} file mysrc file mydst
    # ----
    # Will do the same as above, but the template code in the input file
    # `mysrc` will have the list `{one two}` accessible via the
    # `argv` variable.
    #
    # ----
    # template parse string "test" file mydst
    # ----
    # Will process the string "test" and save the result in `mydst`.
    #
    proc parse { args } {
        variable deps

	if {[llength $args] < 4 || [llength $args] % 2} {
	    template fatal "wrong # args"
	}
	# process template options, if not done already
	getopt

	# produce output
        set perm {}
	lassign [lrange $args end-1 end] dtype dst
	set out [engine::open $dtype $dst write]

	set savedargs [engine::args [list]]
	foreach { stype src } [lrange $args 0 end-2] {
	    switch -- $stype {
		args	{ engine::args $src }
		perm	{ set perm $src }

		raw {
		    set in [engine::open string $src read]
		    if {[catch {chan copy $in $out} m]} {
			template fatal "$m"
		    }
		    engine::close $in
		}

		string  -
		file	{
		    set in [engine::open $stype $src read]
		    if {$stype == "string"} { set src "<string>" }
		    if {[catch {engine::process $src $in $out} m]} {
                      engine::close $in
                      return -code error $m
		    }
		    engine::close $in

                    if {$stype == "file"} {
                      set src [file join [dotgen template dir] $src]
                      if {$src ni $deps} {
                        lappend deps [file normalize $src]
                      }
                    }
		}

		default {
		    engine::close $out
		    template fatal \
			"unknown source '$stype': must be args, string or file"
		}
	    }
	}
	engine::args $savedargs

	engine::close $out $perm
	return
    }
    namespace export parse


    # --- options ----------------------------------------------------------

    #/
    # [[template_options]]
    # === *template options* 'pattern' 'body' ...
    #
    # Define the list of supported options for the template. Argument is a Tcl
    # switch-like script that must define all supported options. It consists of
    # pairs of 'pattern body'. If an option matching the 'pattern' is passed to
    # the template, the 'body' script is evaluated. A special body specified as
    # "-" means that the body for the next pattern will be used for this
    # pattern.
    #
    # .Examples
    # ----
    # template options {
    #     -h - --help	{ puts "help option" }
    # }
    # ----
    #
    # This will make the template print the text "help option" whenever -h or
    # --help option is passed to the template.
    #
    proc options { ospec } {
	variable options
	variable gotopt

	if {$gotopt} {
	    fatal "options specification must be set before any"	\
		"'template parse' command"
	}

	if {[llength $ospec] % 2} { fatal "invalid options specification" }
	lappend ospec -h - --help { template fatal "help not implemented" }

	set options $ospec

	# process options, if not done already
	getopt
    }
    namespace export options


    # --- deps -------------------------------------------------------------

    #/
    # [[template_deps]]
    # === *template deps*
    #
    # Return the comprehensive list of template files processed so far. This
    # includes files processed via `template require`, `template
    # parse` and `template link`. This list is typically used to generate
    # dependency information in a Makefile.
    #
    proc deps { } {
      variable deps

      # add main template file to the list
      set src [file join [dotgen template dir] template.tcl]
      if {$src ni $deps} {
        lappend deps $src
      }
      return $deps
    }
    namespace export deps


    # --- arg --------------------------------------------------------------

    #/
    # [[template_arg]]
    # === *template arg* [{next|files|names|components}]
    #
    # Process input arguments according to the optional command keyword. If no
    # command is given, it defaults to `next`.
    #
    # .Arguments
    # [horizontal]
    # +next+::
    # Pops the next argument passed to the template, or raise an error if no
    # argument remains. Mostly useful within a `template options` body.
    #
    # +files+::
    # Return a list of readable input files in the current argument list of
    # the template. If no readable file exists, return the first argument
    # (if any) so that ENOENT may eventually be reported by `template parse`.
    #
    # +names+::
    # Return the list of arguments that are not readable input files.
    #
    # +components+::
    # Interpret the list of arguments that are not readable input files
    # (`template arg names`) as component or interface names and return the
    # list of resolved objects. If none is given explicitly, the components and
    # interfaces defined in input files (`template arg files`) are returned.
    #
    # Input files must have been parsed already by `template parse` for this
    # command to return meaningful data.
    #
    #
    proc arg { {opt next} } {
      global argc argv

      switch -- $opt {
        next {
          set optarg [lindex $argv 1]
          if {$optarg == ""} {
            template fatal "missing argument to [lindex $argv 0]"
          }

          set argv [lreplace $argv 1 1]
          incr argc -1
          return $optarg
        }

        files - names {
          lassign {} files names
          set path [dotgen input path]
          foreach a $argv {
            set f [file join $path $a]
            lappend [expr {[file isfile $f] ? "files" : "names"}] $a
          }
          if {![llength $files]} {
            # no readable file given: use first name as a file so that ENOENT
            # is eventually reported when parsing input
            set names [lassign $names files]
          }
          return [set $opt]
        }

        components {
          set comps [lmap n [arg names] {
            set o [list {*}[dotgen component $n] {*}[dotgen interface $n]]
            if {![llength $o]} { template fatal "no such object $n." }
            set o
          }]

          if {![llength $comps]} {
            # default to components and interfaces from input files
            set path [dotgen input path]
            set stinputs [lmap f [arg files] {
              file stat [file join $path $f] st
              expr {"$st(dev)+$st(ino)"}
            }]
            set comps [lmap c [list {*}[dotgen components] \
                                   {*}[dotgen interfaces]] {
              file stat [$c loc file] st
              if {"$st(dev)+$st(ino)" ni $stinputs} continue
              set c
            }]
          }
          return $comps
        }

        default {
          fatal "unknown command '$opt': " \
              "must be next, files, names or components"
        }
      }
    }
    namespace export arg


    # --- usage ------------------------------------------------------------

    #/
    # [[template_usage]]
    # === *template usage* ['string']
    #
    # With a 'string' argument, this procedure defines the template "usage"
    # message. Unless the template redefines a `-h` option with `template
    # options` (<<template_options,`temaplte options`>>), the default
    # behaviour of the template is to print the content of the `template usage`
    # string when `-h` or `--help` option is passed to the template.
    #
    # `template usage`, when invoked without argument, returns the last
    # usage message defined.
    #
    proc usage { args } {
	variable usage

	if {[llength $args] == 0} { return $usage }
	set usage [join $args {}]
	return
    }
    namespace export usage


    # --- message ----------------------------------------------------------

    #/
    # [[template_message]]
    # === *template message* ['string']
    #
    # Print 'string' so that it is visible to the end-user. The text is
    # sent on the standard error channel unconditionnaly.
    #
    proc message { m } {
      if {[dotgen genom verbose]} {
	puts stderr "[dotgen template name]: $m"
      }
    }
    namespace export message


    # --- fatal ------------------------------------------------------------

    #/
    # [[template_fatal]]
    # === *template fatal* ['string']
    #
    # Print an error message and stop. The message indicates the error location
    # as reported by the `TCL` command `[info frame]`.
    #
    proc fatal { args } {
      set m ""
      set skip 0
      switch -glob -- [lindex $args 0] {
        -* {
          set args [lassign $args skip]
          set skip [expr {-$skip}]
        }
      }
      for {set i [expr {2+$skip}]} {$i < [info frame]} {incr i} {
        set info [info frame -$i]
        if {[dict exists $info file]} {
          set f [dict get $info file]
          if {[string match [dotgen template dir]/* $f]} {
            set f [file tail $f]
          }
          if {[dict exists $info line]} {
            set l [dict get $info line]
            set c [lindex [split [dict get $info cmd] \n] 0]
            if {[string length $c] > 40} {
              set c [string range $c 0 40]...
            }
            append m "\n called by: $f:$l $c"
          }
        }
      }

      return -code error -level [expr {[info level]+1}] "[join $args]$m"
    }
    namespace export fatal


    # --- getopt -----------------------------------------------------------

    # Parse options according to the template specification.
    #
    proc getopt { } {
	variable gotopt
	if {$gotopt} { return } else { set gotopt 1 }

	global argc argv
	variable usage
	variable options

	# process options
	while {$argc > 0} {
	    set arg [lindex $argv 0]
	    if {[regexp -- {(--?.+)=(.+)} $arg m o a]} {
		set arg $o
		set argv [linsert $argv 1 $a]
	    }

	    uplevel #0 switch -glob -- $arg [concat $options -* "{
		template fatal \"unknown option $arg\"
	    }" * break]

	    incr argc -1
	    set argv [lrange $argv 1 end]
	}

        return
    }

    namespace ensemble create
}
