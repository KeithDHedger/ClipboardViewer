/*
 *
 * ©K. D. Hedger. Tue 31 Jul 14:10:54 BST 2018 keithdhedger@gmail.com

 * This file (globals.h) is part of ClipboardViewer.

 * ClipboardViewer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.

 * ClipboardViewer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with ClipboardViewer.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtk/gtk.h>
#include "internet.h"

#ifndef _GLOBALS_
#define _GLOBALS_

#define MAXCLIPS 20
#define MAXDROPTXTLEN 40

struct clips
{
	GdkPixbuf*			image;
	char*				text;
	GtkClipboard*		realclip;
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
