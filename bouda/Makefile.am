## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src data pixmaps launchers

boudadocdir = ${prefix}/doc/bouda
boudadoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS

EXTRA_DIST = $(boudadoc_DATA)

# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done

