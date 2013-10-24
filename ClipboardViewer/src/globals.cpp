//
//Keith Hedger
//Wed Apr 18 18:07:43 BST 2007-2013
//
//globals.cpp
//

#include <gtk/gtk.h>

#include "globals.h"

char*			tempname;
GtkClipboard	*mainclipboard;

GtkWidget*		scrollBox=NULL;
GtkWidget*		textBox=NULL;
GtkWidget*		viewBox=NULL;
GtkWidget*		bufferBox=NULL;
GtkWidget*		window=NULL;
GtkWidget*		notebook=NULL;
GtkWidget*		scrollPicBox=NULL;
GtkWidget*		imageBox=NULL;
GtkWidget*		clipListDrop=NULL;

//GdkPixbuf*		imageList[5]={NULL};
//char*			textList[5]={NULL};
int				currentClip=0;
clips			clip[5];
