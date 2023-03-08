#
# Copyright (c) 2010-2015,2017,2022-2023 LAAS/CNRS
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
#                                           Anthony Mallet on Tue Jan 12 2010
#

#/
# Skeleton template
# -----------------

# Default template for user skeleton file generation.

template usage "Skeleton generation template\n" [regsub -all [join {
  { *#/? ?} {----} {::} {[*]([^*\n]+)[*]} {[+]([^\n]+?)[+]}
} |] {
  #/ === Synopsys
  #
  # *genom3* *skeleton* [*-l c++*] [*-C* 'dir']
  #     [-x] [--extern='component'[,...]]
  #	[*-m* 'tool'] [*-t*] [*-f*]
  #	'file.gen' [...] ['object'] [...]
  #
  # === Description
  #
  # The skeleton template generates the skeleton of the codel functions
  # defined in the input .gen file. It also generates a sample build
  # infrastructure for building them. By default, files are generated in the
  # same directory as the input .gen file. The `-C` option can be used to
  # specify another output directory.
  #
  # The `+-l c+++` option is specific to `C` codels. It generates a skeleton
  # that compiles the codels with a `{cpp}` compiler. This is useful for
  # invoking `{cpp}` code from the codels (Note that this is different from
  # having `{cpp}` codels.)
  #
  # Files generated with this template are freely modifiable (and are actually
  # required to be modified in order to provide some real codels). They are
  # provided only as a sample - yet sensible - implementation. The only
  # requirement is that codels provide a `pkg-config` file (`.pc`)
  # named `<component>-genom3.pc` and telling the other templates how to
  # link with the codels library.
  #
  # The template can also be invoked in 'merge' mode, where it updates existing
  # skeletons. This mode tries to merge modifications in the .gen file, for
  # instance service addition or new interface definitions, into existing
  # codels. In case of conflicting files, there are several merge strategies:
  # option `-u` places conflicts markers in the source file, option `-i`
  # interactively asks what to do, and the generic option `-m tool` runs `tool`
  # on the conflicting files. `tool` can be any merge tool, for instance
  # `meld`.
  #
  # === Example
  # ----
  # user@host:~$ genom3 skeleton demo.gen
  # creating ./codels/demo_motion_codels.c
  # creating ./codels/demo_codels.c
  # [...]
  # creating ./codels/Makefile.am
  # ----
  #
  # === Supported options
  #
  # +-l c+++::
  # +--language=c+++ ::
  #		Compile C codels with a C++ compiler
  #
  # +-C+::
  # +--directory='dir'+ ::
  #		Output files in dir instead of source directory
  #
  # +-x+::
  #		Generate skeleton for all codels, including externally defined
  #		ones.
  # +--extern=['component'[,...]]+ ::
  #		Generate skeleton for codels defined in those components.
  #
  # +-m+::
  # +--merge='tool'+ ::
  #		Merge conflicting files with tool
  # +-i+ ::
  #		Interactively merge conflicting files, alias for
  #		`-m interactive`
  # +-u+ ::
  #		Automatically merge conflicting files, alias for `-m auto`
  # +-f+::
  # +--force+ ::
  #		Overwrite existing files (use with caution)
  # +-t+::
  # +--terse+ ::
  #		Produce terse output: no documentation is generated
  # +-h+::
  # +--help+ ::
  #		Print usage summary (this text)
} {\1\2}]

# defaults: no file overwrite
engine mode -overwrite -merge-if-change
set terse no

# parse options
template options {
  -l - --language	{ set lang [template arg] }
  -C - --directory	{ set outdir [template arg] }
  -x			{ set extrefs [list] }
  --extern		{ set extrefs [split [template arg] {, }] }
  -m - --merge		{
    engine merge-tool [template arg]; engine mode +merge-if-change
  }
  -i			{
    engine merge-tool interactive; engine mode +merge-if-change
  }
  -u			{
    engine merge-tool auto; engine mode +merge-if-change
  }
  -f - --force		{ engine mode +overwrite }
  -t - --terse		{ set terse yes }
  -h - --help		{ puts [template usage]; exit 0 }
}

# process input files
set inputs [template arg files]
if {![llength $inputs]} { puts [template usage]; exit 2 }
dotgen parse file {*}$inputs
set input [file tail [lindex $inputs 0]]
if {![info exists outdir]} {
  set outdir [file dirname [lindex $inputs 0]]
}

# list of local idl source files
set idls [list]
set base [file normalize $outdir]
foreach f [dotgen input deps] {
  set f [file normalize $f]
  if {[string match $base/* $f]} {
    lappend idls [string range $f [string length $base/] end]
  }
}

# list of extern references
set externs [list]
if {[info exists extrefs]} {
  switch [llength $extrefs] {
    0 { set externs [list {*}[dotgen components] {*}[dotgen interfaces]] }
    default {
      set externs [lmap e $extrefs {
        set o [list {*}[dotgen component $e] {*}[dotgen interface $e]]
        if {![llength $o]} { error "no such object $e." }
        set o
      }]
    }
  }
}

# get components to generate stubs for, default to components and interfaces
# defined in input files
set components [template arg components]
if {![llength $components]} { error "no component or interface." }

# check options consistency
set iface [list]
foreach o $components {
  if {[$o lang] ni $iface} { lappend iface [$o lang] }
}
if {[llength $iface] != 1} {
  error "inconsistent component languages: [join $iface {, }]."
}

if {![info exists lang]} {
  set lang $iface
}

switch -- "$iface" {
  c {}
  default {
    template fatal "codel interface in $iface is not yet supported."
  }
}
if {$iface ne $lang} {
    switch -- "$iface|$lang" {
	c|c++ {}
	default {
	    template fatal \
		"codel interface in $iface compiled in $lang is not allowed"
	}
    }
}

# generate codel files
#
engine chdir $outdir
set src [lang $iface; fileext]
set ext [lang $lang; fileext]

foreach c $components {
  set e [expr {[llength $externs] ? $externs : $c}]

  # one source file for each task
  foreach t [$c tasks] {
    if {[$t loc context] ni $e} continue

    template parse args [list $c $t $e]		\
        file codels.codel$src file codels/[$c name]_[$t name]_codels$ext
  }

  # and one file for codels with no associated task
  template parse args [list $c "" $e]		\
      file codels.codel$src file codels/[$c name]_codels$ext

    # mandatory pkg-config file
    template parse					\
	args [list $c] file component.pc.in		\
	file [$c name]-genom3.pc.in
    template parse					\
	args [list $c] file component-uninstalled.pc.in	\
	file [$c name]-genom3-uninstalled.pc.in
}


# asciidoc template
if {!$terse} {
  template parse args [list $components $input]		\
      file readme.adoc file README.adoc
}


# generate user build files fragment
#
set skelopts [list "-l '$lang'"]
if {$terse} { lappend skelopts "-t" }
if {[info exists extrefs]} {
  switch -- [llength $extrefs] {
    0 { lappend skelopts -x }
    default { lappend skelopts "--extern='[join $extrefs ,]'" }
  }
}

template parse perm a+x					\
    string "#!/bin/sh\nautoreconf -vi\n"		\
    file bootstrap.sh
if {"component" in [lmap c $components {$c class}]} {
  template parse					\
      file ag_templates.m4 file autoconf/ag_templates.m4
}
template parse						\
    args [list $components $argv $lang $terse]		\
    file top.configure.ac file configure.ac
template parse						\
    args [list $components $input $idls $terse $skelopts]	\
    file top.Makefile.am file Makefile.am
template parse						\
    args [list $components $externs $input $lang]		\
    file codels.Makefile.am file codels/Makefile.am
