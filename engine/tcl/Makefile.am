#
# Copyright (c) 2010-2012 LAAS/CNRS
# All rights reserved.
#
# Permission to use, copy, modify, and distribute this software for any purpose
# with or without   fee is hereby granted, provided   that the above  copyright
# notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS  SOFTWARE INCLUDING ALL  IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS. IN NO EVENT SHALL THE AUTHOR  BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR  ANY DAMAGES WHATSOEVER RESULTING  FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
# OTHER TORTIOUS ACTION,   ARISING OUT OF OR IN    CONNECTION WITH THE USE   OR
# PERFORMANCE OF THIS SOFTWARE.
#
#                                            Anthony Mallet on Fri Jan  8 2010
#
ECHO=	echo

systcldir=$(sysdir)/tcl

dist_systcl_DATA=\
	object.tcl		\
	template.tcl		\
	language.tcl		\
	language-c.tcl		\
	language-c++.tcl	\
	engine.tcl		\
	merge.tcl		\
	lcs.tcl			\
	md5.tcl

nodist_systcl_DATA=\
	version.tcl		\
	pkgIndex.tcl

systcl_LTLIBRARIES=	engine.la
engine_la_SOURCES=\
	engine.h	\
	engine.c	\
	dotgen.c	\
	component.c	\
	service.c	\
	remote.c	\
	port.c		\
	task.c		\
	parameter.c	\
	codel.c		\
	idltype.c

engine_la_CPPFLAGS=	-I$(top_srcdir)/src $(TCL_INCLUDE_SPEC)
engine_la_CPPFLAGS+=	-DTMPLDIR='"$(tmpldir)"'
engine_la_LIBADD=	$(TCL_LIB_SPEC)
engine_la_LDFLAGS=	-module -release $(PACKAGE_VERSION)

BUILT_SOURCES=	version.tcl pkgIndex.tcl
CLEANFILES=	version.tcl pkgIndex.tcl

version.tcl: Makefile
	exec >$@;						\
	$(ECHO) '# $(PACKAGE_STRING) system files';		\
	$(ECHO) 'package provide'				\
		'$(PACKAGE_NAME)-engine $(PACKAGE_VERSION)';

pkgIndex.tcl: Makefile
	l='[list source [file join $$dir version.tcl]]';	\
	for s in $(dist_systcl_DATA); do			\
	  test -f $$s || $(LN_S) $(srcdir)/$$s $$s;		\
	  l="$$l"'|[list source [file join $$dir '"$$s"']]';	\
	done;							\
	test -f engine.so || $(LN_S) .libs/engine.so;		\
	$(ECHO) "package ifneeded $(PACKAGE_NAME)-engine"	\
		"$(PACKAGE_VERSION) $$l" |			\
	$(SED) 's/|/\\n/g' >$@
