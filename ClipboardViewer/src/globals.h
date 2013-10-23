//
//Keith Hedger
//Wed Apr 18 18:07:43 BST 2007
//
//globals.h
//

#include <gtk/gtk.h>

#ifndef _GLOBALS_
#define _GLOBALS_

//#define PATHTOPIX "../resources/pixmaps"
//#define PATHTOSCRIPTS "../resources/scripts"
//#define PROGRAMNAME "ClipboardViewer"
//#define GLADEFILE "../resources/glade/"PROGRAMNAME".glade"
//#define GLADENAME PROGRAMNAME".glade"
#define VERSION "0.2.0"
#define MYEMAIL "kdhedger68713@gmail.com"
#define MYWEBSITE "http://keithhedger.hostingsiteforfree.com"

//extern gchar			*gladepath;
//extern gchar			*prefixPathToPix;
//extern gchar			*prefixPathToScripts;
extern char*			tempname;
//
//extern GtkWindow			*mainwindow;
//extern GladeXML			*mainui;
extern GtkClipboard		*mainclipboard;
//typedef struct mainSignals
//{
//	gchar	*name;
//	void	(*fptr)(GtkButton*,gpointer);
//};

extern GtkWidget*		scrollBox;
extern GtkWidget*		textBox;
extern GtkWidget*		viewBox;
extern GtkWidget*		bufferBox;
extern GtkWidget*		window;
extern GtkWidget*		notebook;
extern GtkWidget*		scrollPicBox;
extern GtkWidget*		imageBox;

//extern GtkWidget*		badWordLabel;

//extern GtkWidget*		spellCheckWord;
//extern GtkWidget*		wordListDropbox;
//extern char*			badWord;
//extern char*			goodWord;
//
//extern AspellConfig*	aspellConfig;
//extern AspellSpeller*	spellChecker;
//
//extern int				numWords;


#endif
