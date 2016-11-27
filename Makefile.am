# Makefile for rpm library.

AUTOMAKE_OPTIONS = 1.4 foreign

LINT = splint

CLEANFILES = *.gcov .libs/*.gcda .libs/*.gcno *.gcno *.gcda

EXTRA_DIST = \
	ChangeLog \
	$(srcdir)/rpm/__init__.py \
	$(srcdir)/rpm/transaction.py \
	rpmdebug-py.c

AM_CPPFLAGS = -I. \
	-I$(top_srcdir) \
	-I$(top_srcdir)/build \
	-I$(top_srcdir)/lib \
	-I$(top_builddir)/lib \
	-I$(top_srcdir)/rpmdb \
	-I$(top_srcdir)/rpmio \
	-I$(top_srcdir)/misc \
	@WITH_DB_CPPFLAGS@ \
	@WITH_LUA_CPPFLAGS@ \
	@WITH_FILE_CPPFLAGS@ \
	@WITH_PCRE_CPPFLAGS@ \
	@WITH_POPT_CPPFLAGS@ \
	@WITH_XAR_CPPFLAGS@ \
	@WITH_ZLIB_CPPFLAGS@ \
	-I@WITH_PYTHON_INCDIR@

noinst_HEADERS = system-py.h header-py.h \
	rpmal-py.h rpmds-py.h rpmdb-py.h rpmfd-py.h rpmfts-py.h \
	rpmfi-py.h rpmkeyring-py.h rpmmacro-py.h rpmmi-py.h \
	rpmps-py.h rpmtd-py.h rpmte-py.h rpmts-py.h \
	spec-py.h

# XXX TODO: switch to _rpm.la _rpmb.la
pkgpyexec_LTLIBRARIES = _rpmmodule.la _rpmbmodule.la
pkgpyexec_SCRIPTS = $(srcdir)/rpm/__init__.py $(srcdir)/rpm/transaction.py

#X _rpmmodule_la_CFLAGS = -fno-strict-aliasing
_rpmmodule_la_SOURCES = \
	rpmmodule.c header-py.c \
	rpmal-py.c rpmds-py.c rpmdb-py.c rpmfd-py.c rpmfts-py.c\
	rpmfi-py.c rpmkeyring-py.c rpmmacro-py.c rpmmi-py.c \
	rpmps-py.c rpmtd-py.c rpmte-py.c rpmts-py.c
_rpmmodule_la_DEPENDENCIES = rpm/_rpm.so
_rpmmodule_la_LDFLAGS = -module -avoid-version -shared
_rpmmodule_la_LIBADD = \
	$(top_builddir)/lib/librpm.la \
	$(top_builddir)/rpmdb/librpmdb.la \
	$(top_builddir)/rpmio/librpmio.la \
	$(top_builddir)/misc/librpmmisc.la \
	@LTLIBINTL@ \
	-lpython$(PYTHON_VERSION)

_rpmbmodule_la_SOURCES = \
	rpmbmodule.c spec-py.c
_rpmbmodule_la_DEPENDENCIES = rpm/_rpmb.so
_rpmbmodule_la_LDFLAGS = -module -avoid-version -shared
_rpmbmodule_la_LIBADD = \
        $(top_builddir)/build/librpmbuild.la \
        $(top_builddir)/lib/librpm.la \
        $(top_builddir)/rpmio/librpmio.la \
	@LTLIBINTL@ \
	-lpython$(PYTHON_VERSION)

rpm:
	@mkdir -p rpm
	@-cp $(srcdir)/rpm/__init__.py rpm/__init__.py
	@-cp $(srcdir)/rpm/transaction.py rpm/transaction.py

rpm/_rpm.so:	rpm
	@ln -sf ../.libs/_rpmmodule.so rpm/_rpm.so

rpm/_rpmb.so:	rpm
	@ln -sf ../.libs/_rpmbmodule.so rpm/_rpmb.so

clean-local:
	rm -f rpm/_rpm.so rpm/_rpmb.so

EXTRA_DIST += .cppcheck.supp
#	--std=posix
#	--template="{file},{line},{severity},{id},{message}"
#	--suppress=obsoleteFunctionsalloca
#	--template=gcc
CPPCHECK = @__CPPCHECK@ -q --force --inline-suppr -j 4 \
	--template="{file},{line},{severity},{id},{message}" \
	--suppressions-list=.cppcheck.supp \
	--report-progress \
	-UNOTYET -UNOTNOW -UNOTNEEDED -UDYING -UDEAD -UREFERENCE \
	-U__cplusplus -U__LCLINT__ -USWIG \
	-URPM_VENDOR_MANDRIVA \
	-URPM_VENDOR_WINDRIVER \
	-DHAVE_CONFIG_H \
	--enable=warning,style,performance,portability,information,unusedFunction,missingInclude

.PHONY: cppcheck
cppcheck:
	$(CPPCHECK) $(AM_CPPFLAGS) \
	    $(_rpmmodule_la_SOURCES) $(_rpmbmodule_la_SOURCES)

# rpmmodule.c header-py.c \
# 	rpmal-py.c rpmds-py.c rpmdb-py.c rpmfd-py.c rpmfi-py.c rpmmi-py.c \
# 	rpmmacro-py.c rpmps-py.c rpmte-py.c rpmts-py.c
# rpmmodule.c header-py.c
splint_srcs = \
 	rpmal-py.c rpmds-py.c rpmdb-py.c rpmfd-py.c rpmfts-py.c \
	rpmfi-py.c rpmkeyring-py.c rpmmacro-py.c rpmmi-py.c \
	rpmps-py.c rpmtd-py.c rpmte-py.c rpmts-py.c \
	spec-py.c

.PHONY:	lint
lint:
	$(LINT) $(DEFS) $(INCLUDES) $(splint_srcs)

# FIXME: using .libs/ is not really correct, but whatever
#check-local:
#	@export PYTHONPATH=$(PYTHONPATH):$(shell pwd):$(shell pwd)/.libs/ && \
#	cd test && python test_rpm.py
