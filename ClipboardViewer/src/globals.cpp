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


GtkWidget*		scrollBox=NULL;
GtkWidget*		textBox=NULL;
GtkWidget*		viewBox=NULL;
GtkWidget*		bufferBox=NULL;
GtkWidget*		window=NULL;
//GtkWidget*		badWordLabel=NULL;

//spellcheck
//GtkWidget*		spellCheckWord=NULL;
//GtkWidget*		wordListDropbox;
//char*			badWord=NULL;
//char*			goodWord=NULL;
//AspellConfig*	aspellConfig;
//AspellSpeller*	spellChecker=0;
//
//int				numWords=0;
