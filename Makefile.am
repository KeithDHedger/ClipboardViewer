
SUBDIRS = ClipboardViewer/app ClipboardViewer/debug#***MMM***

gladefilesdir = $(pkgdatadir)
gladefiles_DATA = ClipboardViewer/resources/glade/ClipboardViewer.glade
pixfilesdir = $(pkgdatadir)/pixmaps
pixfiles_DATA = ClipboardViewer/resources/pixmaps/ClipboardViewer.png
scriptfilesdir = $(pkgdatadir)/scripts
scriptfiles_DATA = ClipboardViewer/resources/scripts/readme

remake:
	$(shell ./remakesourcelist)

install-exec-hook:
	cp ClipboardViewer/resources/pixmaps/clipviewer.desktop /usr/share/applications/clipviewer.desktop
	update-menus

#	mkdir -p $(pkgdatadir)/pixmaps
#	cp ClipboardViewer/resources/pixmaps/ClipboardViewer.png $(pkgdatadir)/pixmaps

	echo Icon=${prefix}/share/ClipboardViewer/pixmaps/ClipboardViewer.png >> /usr/share/applications/clipviewer.desktop
	echo Exec=${prefix}/bin/clipboardviewer >> /usr/share/applications/clipviewer.desktop
#
#	mkdir -p $(pkgdatadir)/scripts
	echo -e "#!/bin/bash\n""CLIPBIN=${prefix}/bin/clipboardviewer\n" | cat - ../resources/scripts/MakeClipping > $(pkgdatadir)/scripts/MakeClipping
	chmod 755 $(pkgdatadir)/scripts/MakeClipping
	ln -s $(pkgdatadir)/scripts/MakeClipping ~/.gnome2/nautilus-scripts

uninstall-hook:
	$(shell rm /usr/share/applications/clipviewer.desktop)
	$(shell update-menus)
	$(shell rm $(pkgdatadir)/scripts/MakeClipping)
#	$(shell rmdir $(pkgdatadir)/scripts)
#	$(shell rm $(pkgdatadir)/pixmaps/ClipboardViewer.png)
#	$(shell rmdir $(pkgdatadir)/pixmaps)
#	$(shell rm $(pkgdatadir)/ClipboardViewer.glade)
#	$(shell rmdir $(pkgdatadir))
	$(shell rm ~/.gnome2/nautilus-scripts/MakeClipping)
	$(shell rmdir $(pkgdatadir)/pixmaps)
	$(shell rmdir $(pkgdatadir)/scripts)
	$(shell rmdir $(pkgdatadir))

