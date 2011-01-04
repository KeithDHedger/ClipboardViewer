
include ../flagsandlibs
include ../sources

clipboardviewer_SOURCES = $(COMMONSRC)

clipboardviewer_CFLAGS = -O3
clipboardviewer_CXXFLAGS = -O3

bin_PROGRAMS = clipboardviewer

man1_MANS = ../resources/man/clipboardviewer.1

gladefilesdir = $(pkgdatadir)
gladefiles_DATA = ../resources/glade/ClipboardViewer.glade

pixmapsdir = $(pkgdatadir)/pixmaps
pixmaps_DATA = ../resources/pixmaps/ClipboardViewer.png

install-exec-hook:
	mkdir -p $(DESTDIR)/usr/share/applications
	cp ../resources/pixmaps/clipviewer.desktop $(DESTDIR)/usr/share/applications/clipviewer.desktop
	echo Icon=${prefix}/share/ClipboardViewer/pixmaps/ClipboardViewer.png >> $(DESTDIR)/usr/share/applications/clipviewer.desktop
	echo Exec=${prefix}/bin/clipboardviewer >> $(DESTDIR)/usr/share/applications/clipviewer.desktop
#	update-menus

	mkdir -p $(DESTDIR)/$(pkgdatadir)/scripts
	awk ' {sub(/XXXX/,"${prefix}/bin/clipboardviewer");print; }' ../resources/scripts/form > $(DESTDIR)/$(pkgdatadir)/scripts/MakeClipping
	chmod 755 $(DESTDIR)/$(pkgdatadir)/scripts/MakeClipping
#	ln -sf $(pkgdatadir)/scripts/MakeClipping ~/.gnome2/nautilus-scripts


uninstall-hook:
	rm -f $(DESTDIR)/usr/share/applications/clipviewer.desktop
#	update-menus
	rm -fr $(DESTDIR)/$(pkgdatadir)
	rm -f ~/.gnome2/nautilus-scripts/MakeClipping

