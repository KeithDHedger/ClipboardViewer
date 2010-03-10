

include ../flagsandlibs
include ../sources

clipboardviewerdebug_SOURCES = $(COMMONSRC)

clipboardviewerdebug_CFLAGS = -ggdb -O0
clipboardviewerdebug_CXXFLAGS = -ggdb -O0

bin_PROGRAMS = clipboardviewerdebug

install-exec-local:
	cd $(DESTDIR)$(bindir) && \
	rm clipboardviewerdebug

