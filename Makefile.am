
SUBDIRS = ClipboardViewer/app ClipboardViewer/debug#***MMM***

remake:
	$(shell ./remakesourcelist)

srcpkg:
	mkdir -p /tmp/ClipboardViewer/ClipboardViewer
	cp -r ClipboardViewer Makefile.am autogen.sh configure.ac remakesourcelist /tmp/ClipboardViewer/ClipboardViewer
	rm -r /tmp/ClipboardViewer/ClipboardViewer/ClipboardViewer/app/.deps /tmp/ClipboardViewer/ClipboardViewer/ClipboardViewer/debug/.deps
	cd /tmp/ClipboardViewer/ClipboardViewer && tar -cvzf /tmp/ClipboardViewer.tar.gz .
	
#	cd ..
#	rm -r /tmp/ClipboardViewer
