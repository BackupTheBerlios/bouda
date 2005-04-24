## Process this file with automake to produce Makefile.in

## Created by Anjuta

## gladedir = $(datadir)/bouda/glade
## glade_DATA = bouda.glade

INCLUDES = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DBOUDA_DATA=\"$(prefix)/share/bouda/\" \
	-DBOUDA_CONFIG=\"$(prefix)/share/bouda/bouda.config\" \
	-DBOUDA_PIXMAPS=\"$(prefix)/share/bouda/pixmaps\" \
	-DBOUDA_LAUNCHERS=\"$(prefix)/share/bouda/launchers\" \
	$(PACKAGE_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = bouda

bouda_SOURCES = \
	main.c\
	xutils.c xutils.h\
	read-icon-list.c read-icon-list.h \
	read-png.c read-png.h \
	mouse-events.c mouse-events.h \
	cairo-canvas.c cairo-canvas.h \
	bouda.c bouda.h \
	read-properties.c read-properties.h \
	validate-config.c \
	validate-config.h 

bouda_LDFLAGS = 

bouda_LDADD = $(PACKAGE_LIBS)

## EXTRA_DIST = $(glade_DATA)
