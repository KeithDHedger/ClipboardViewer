//
//Keith Hedger
//Wed Apr 18 18:07:43 BST 2007
//
//globals.h
//

//#include <gnome.h>
#include <glade/glade.h>
#include <glib/gstdio.h>
#include <glib.h>

#ifndef _GLOBALS_
#define _GLOBALS_

#define PATHTOPIX "../resources/pixmaps"
#define PATHTOSCRIPTS "../resources/scripts"
#define PROGRAMNAME "ClipboardViewer"
#define GLADEFILE "../resources/glade/"PROGRAMNAME".glade"
#define GLADENAME PROGRAMNAME".glade"

extern gchar			*gladepath;
extern gchar			*prefixPathToPix;
extern gchar			*prefixPathToScripts;
extern char			*tempname;

extern GtkWindow		*mainwindow;
extern GladeXML			*mainui;
extern GtkClipboard		*mainclipboard;
typedef struct mainSignals
{
	gchar	*name;
	void	(*fptr)(GtkButton*,gpointer);
};

#endif
