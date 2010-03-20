
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
	cp ../resources/pixmaps/clipviewer.desktop /usr/share/applications/clipviewer.desktop
	echo Icon=${prefix}/share/ClipboardViewer/pixmaps/ClipboardViewer.png >> /usr/share/applications/clipviewer.desktop
	echo Exec=${prefix}/bin/clipboardviewer >> /usr/share/applications/clipviewer.desktop
	update-menus


	mkdir -p $(pkgdatadir)/scripts
	echo -e "#!/bin/bash\n""CLIPBIN=${prefix}/bin/clipboardviewer\n" | cat - ../resources/scripts/MakeClipping > $(pkgdatadir)/scripts/MakeClipping
	chmod 755 $(pkgdatadir)/scripts/MakeClipping
	ln -sf $(pkgdatadir)/scripts/MakeClipping ~/.gnome2/nautilus-scripts

uninstall-hook:
	rm -f /usr/share/applications/clipviewer.desktop
	update-menus
	rm -fr $(pkgdatadir)
	rm -f ~/.gnome2/nautilus-scripts/MakeClipping

