#
# Copyright (c) 2010-2012 LAAS/CNRS
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

# Template for type mappings generation.

template usage {*}{
    "\n"
    "Mappings generation template.\n"
    "\n"
    "Mappings are the translation of IDL types defined in the .gen file into\n"
    "native type definitions. By default, this template generates the\n"
    "mappings for the codels language (defined in the .gen file). This can be\n"
    "changed with the -l option (several -l options can be given, for\n"
    "multiple mappings generation). The generated files are named after the\n"
    "component name, that is suffixed with _types. The suffix can be changed\n"
    "with the -s option.\n"
    "\n"
    "Supported options:\n"
    "  -l, --language=lang\tgenerate mappings for language\n"
    "  -s, --suffix=string\tset output file name suffix\n"
    "  --signature\t\tgenerate codel signatures and types mappings\n"
    "  -MD\t\t\tgenerate dependency information (in out.d)\n"
    "  -MF=file\t\tgenerate dependency in file instead of out.d\n"
    "  -MT=target\t\tchange the target of the dependency rules\n"
    "  -C, --directory=dir\toutput files in dir instead of current directory\n"
    "  -C, --directory=dir\toutput files in dir instead of current directory\n"
    "  -p, --preserve\tdo not overwrite existing files\n"
    "  -m, --modify\t\toverwrite files even if they did not change\n"
    "  -h, --help\t\tprint usage summary (this text)"
}

# defaults
variable dir		.
variable suffix		_types
variable sign		[list]
variable deps		off
variable dfile		"out.d"
variable dtarget	""
engine mode +overwrite +move-if-change

# parse options
template options {
	 --signature	{ set sign [list file codels.h] }
    -s - --suffix	{ set suffix [template arg] }
    -l - --language	{ lappend lang [template arg] }
    -MD			{ set deps on }
    -MF			{ set dfile [template arg] }
    -MT			{ set dtarget [template arg] }
    -C - --directory	{ set dir [template arg] }
    -p - --preserve	{ engine mode -overwrite }
    -m - --modify	{ engine mode -move-if-change }
    -h - --help		{ puts [template usage]; exit 0 }
}

# check/process input files
if {![llength $argv]} { puts [template usage]; exit 2 }
foreach f $argv { dotgen parse file $f }
engine chdir $dir

# generate header
set header " Generated by [dotgen genom version]. Do not edit.\n"
append header " Source file: $argv\n"
if {![catch {dotgen input notice} notice]} {
  append header $notice
}

# generate types definitions
set out [list]
foreach c [dotgen components] {
    if {[info exists lang]} { set l $lang } else { set l [$c language] }
    foreach l $l {
      lang $l
      template parse					\
          args [list $c $l]				\
          raw [comment $header]\n			\
          string [language mapping]			\
          {*}$sign					\
          file "[$c name]_[cname $l]$suffix[fileext header]"
      lappend out "[$c name]_[cname $l]$suffix[fileext header]"
    }
}

# dependencies
if {$dtarget == ""} { set dtarget $out }
if {$deps} {
  set deps [list]
  foreach d [concat [dotgen input deps] [template deps]] {
    lappend deps "$dtarget: $d"
    lappend deps "$d:"
  }
  engine mode +overwrite -move-if-change
  template parse raw [join $deps "\n"]\n file $dfile
}
