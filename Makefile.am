#
# Copyright (c) 2009-2014,2020 LAAS/CNRS
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
#                                             Anthony Mallet on Wed Dec 16 2009
#
ACLOCAL_AMFLAGS = -I autoconf

if ENABLE_RUNTIME
pkgconfigdir=	$(libdir)/pkgconfig
pkgconfig_DATA=	genom3.pc genom3-c-client.pc
endif

if ENABLE_TOOL
  dist_bin_SCRIPTS=\
	profundis

if WITH_TCL
  TCLDIR=\
	engine/tcl		\
	templates/interactive	\
	templates/example	\
	templates/mappings	\
	templates/skeleton
endif

  TOOLDIR=\
	compat			\
	pcpp			\
	src			\
	templates/common	\
	$(TCLDIR)		\
	doc			\
	regress
endif
if ENABLE_RUNTIME
  RUNTIMEDIR=\
	runtime/genom3/c	\
	runtime/genom3/c++
endif

SUBDIRS=\
	$(RUNTIMEDIR)		\
	$(TOOLDIR)


# distcheck configuration
DISTCHECK_CONFIGURE_FLAGS=	CFLAGS='-Wall -Werror'
DISTCHECK_CONFIGURE_FLAGS+=	--enable-docgen
if WITH_TCL
  DISTCHECK_CONFIGURE_FLAGS+=	--with-tcl="$(TCL_BIN_DIR)"
endif

if ENABLE_TOOL
# message
install-data-hook:
	@echo '=============================================================='
	@echo '    Installation complete.'
	@echo ''
	@echo '    Documentation is available in'
	@echo '    $(docdir)'
	@echo '=============================================================='
endif
