//
//Keith Hedger
//Wed Apr 18 18:07:43 BST 2007
//
//globals.cpp
//

#include <glade/glade.h>
#include <glib/gstdio.h>
#include <glib.h>

#include "globals.h"

gchar			*gladepath=NULL;
gchar			*prefixPathToPix=PATHTOPIX;
gchar			*prefixPathToScripts;
char			*tempname;

GtkWindow		*mainwindow;
GladeXML		*mainui;
GtkClipboard	*mainclipboard;
