
include ../flagsandlibs
include ../sources

clipboardviewer_SOURCES = $(COMMONSRC)

clipboardviewer_CFLAGS = -O3
clipboardviewer_CXXFLAGS = -O3

bin_PROGRAMS = clipboardviewer

man1_MANS = ../resources/man/clipboardviewer.1

install-exec-local:
	$(shell cp ../resources/pixmaps/clipviewer.desktop /usr/share/applications/clipviewer.desktop)
	$(shell update-menus)
	$(shell echo Icon=${prefix}/share/ClipboardViewer/pixmaps/ClipboardViewer.png >> /usr/share/applications/clipviewer.desktop)
	$(shell echo Exec=${prefix}/bin/clipboardviewer >> /usr/share/applications/clipviewer.desktop)

uninstall-local:
	$(shell rm /usr/share/applications/clipviewer.desktop)
	$(shell update-menus)

