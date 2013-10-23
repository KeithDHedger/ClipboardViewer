
include ../flagsandlibs
include ../sources

clipboardviewer_SOURCES = $(COMMONSRC)

clipboardviewer_CFLAGS = -O3
clipboardviewer_CXXFLAGS = -O3

bin_PROGRAMS = clipboardviewer

man1_MANS = ../resources/man/clipboardviewer.1

docfilesdir = $(pkgdatadir)/docs
docfiles_DATA = ../resources/docs/*

pixmapsdir = $(pkgdatadir)/pixmaps
pixmaps_DATA = ../resources/pixmaps/*

install-exec-hook:

	mkdir -vp $(DESTDIR)${prefix}/share/applications $(DESTDIR)${prefix}/share/pixmaps||true

	cp ../resources/pixmaps/clipviewer.desktop $(DESTDIR)${prefix}/share/applications/clipviewer.desktop
	cp ../resources/pixmaps/ClipboardViewer.png $(DESTDIR)${prefix}/share/pixmaps

uninstall-hook:
	rm -f $(DESTDIR)${prefix}/share/applications/clipviewer.desktop $(DESTDIR)${prefix}/share/pixmaps/ClipboardViewer.png
	rm -fr $(DESTDIR)/$(pkgdatadir)

