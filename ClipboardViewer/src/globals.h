//
//Keith Hedger
//Wed Apr 18 18:07:43 BST 2007-2013
//
//globals.h
//

#include <gtk/gtk.h>

#ifndef _GLOBALS_
#define _GLOBALS_

#define MAXCLIPS 20
#define MYEMAIL "kdhedger68713@gmail.com"
#define MYWEBSITE "http://keithhedger.hostingsiteforfree.com"
struct clips
{
	GdkPixbuf*			image;
	char*				text;
};


extern char*			tempname;
extern GtkClipboard*	mainclipboard;

extern GtkWidget*		scrollBox;
extern GtkWidget*		textBox;
extern GtkWidget*		viewBox;
extern GtkWidget*		bufferBox;
extern GtkWidget*		window;
extern GtkWidget*		notebook;
extern GtkWidget*		scrollPicBox;
extern GtkWidget*		imageBox;
extern GtkWidget*		clipListDrop;

extern int				currentClip;
extern clips			clip[MAXCLIPS];

#endif
