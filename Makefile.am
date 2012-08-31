
SUBDIRS = ClipboardViewer/app ClipboardViewer/debug#***MMM***

remake:
	$(shell ./remakesourcelist)

srcpkg:
	tar  --exclude ".svn" -cvzf ClipboardViewer.tar.gz ClipboardViewer Makefile.am autogen.sh configure.ac remakesourcelist
