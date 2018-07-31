/*
 *
 * ©K. D. Hedger. Tue 31 Jul 14:10:47 BST 2018 keithdhedger@gmail.com

 * This file (globals.cpp) is part of ClipboardViewer.

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

#include "globals.h"

char*			tempname;
GtkClipboard*	mainclipboard;

GtkWidget*		scrollBox=NULL;
GtkWidget*		textBox=NULL;
GtkWidget*		viewBox=NULL;
GtkWidget*		bufferBox=NULL;
GtkWidget*		window=NULL;
GtkWidget*		notebook=NULL;
GtkWidget*		scrollPicBox=NULL;
GtkWidget*		imageBox=NULL;
GtkWidget*		clipListDrop=NULL;

int				currentClip=0;
clips			clip[MAXCLIPS];
