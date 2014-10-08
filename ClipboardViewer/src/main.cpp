//
//Keith Hedger
//Tue Jun 12 16:22:48 BST 2007-2013
//
//clipboardview.cpp
//

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <glib.h>

#include "globals.h"
#include "config.h"

bool		manual=false;

char* truncateText(char* txt)
{
	if(strlen(txt)<25)
		return(strdup(txt));

	char* retstr;

	asprintf(&retstr,"%.10s ... %s",txt,&txt[strlen(txt)-10]);
	for(int j=0;j<strlen(retstr);j++)
	 if(retstr[j]=='\n')
		 	retstr[j]='.';

	return(retstr);
}

void setCurrentClip(void)
{
	currentClip++;
	if(currentClip==MAXCLIPS)
		currentClip=0;
}

void showContents(int clipnum)
{
	if(clip[clipnum].text!=NULL)
		{
			gtk_text_buffer_set_text((GtkTextBuffer*)bufferBox,clip[clipnum].text,-1);
			gtk_notebook_set_current_page((GtkNotebook*)notebook,0);
			return;
		}

	if(clip[clipnum].image!=NULL)
		{
			gtk_image_set_from_pixbuf((GtkImage*)imageBox,clip[clipnum].image);
			gtk_notebook_set_current_page((GtkNotebook*)notebook,1);
			return;
		}
}

void clipChanged(GtkClipboard* clipboard,gpointer user_data)
{
	char*	droptext=NULL;

	if (manual==true)
		{
			manual=false;
			return;
		}
	
	if (gtk_clipboard_wait_is_text_available(mainclipboard)==true)
		{
			setCurrentClip();
			if(clip[currentClip].text != NULL)
				free(clip[currentClip].text);
			clip[currentClip].text=gtk_clipboard_wait_for_text(clipboard);

			if(clip[currentClip].image != NULL)
				{
					g_object_unref(clip[currentClip].image);
					clip[currentClip].image=NULL;
				}
			gtk_notebook_set_current_page((GtkNotebook*)notebook,0);

			gtk_combo_box_text_remove((GtkComboBoxText*)clipListDrop,currentClip);
			droptext=truncateText(clip[currentClip].text);
			gtk_combo_box_text_insert_text((GtkComboBoxText*)clipListDrop,currentClip,droptext);
			free(droptext);

			gtk_combo_box_set_active((GtkComboBox*)clipListDrop,currentClip);
			showContents(currentClip);
		}

	if (gtk_clipboard_wait_is_image_available(mainclipboard)==true)
		{

			setCurrentClip();
			if(clip[currentClip].text != NULL)
				{
					free(clip[currentClip].text);
					clip[currentClip].text=NULL;
				}
			if(clip[currentClip].image != NULL)
				g_object_unref(clip[currentClip].image);

			clip[currentClip].image=gtk_clipboard_wait_for_image(clipboard);
			gtk_notebook_set_current_page((GtkNotebook*)notebook,0);
			gtk_combo_box_set_active((GtkComboBox*)clipListDrop,currentClip);
			showContents(currentClip);
		}


	clip[currentClip].realclip=gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
	gtk_clipboard_store(clip[currentClip].realclip);
}

void setClip(GtkWidget* widget,gpointer data)
{
	int clipnum=gtk_combo_box_get_active((GtkComboBox*)widget);

	showContents(clipnum);
	if((clip[clipnum].text !=NULL) && (clip[clipnum].realclip!=NULL))
		{
			manual=true;
			gtk_clipboard_set_text(mainclipboard,clip[clipnum].text,-1);
			showContents(clipnum);
		}
	if((clip[clipnum].image !=NULL) && (clip[clipnum].realclip!=NULL))
		{
			manual=true;
			gtk_clipboard_set_image(mainclipboard,clip[clipnum].image);
			showContents(clipnum);
		}
	return;
}

void doShutdown(GtkButton *button, gpointer window_ptr)
{
	gtk_main_quit();
	exit(0);
}

void doAbout(GtkWidget* widget,gpointer data)
{
	const char*	authors[]={"K.D.Hedger <"MYEMAIL">","\nMore by the same author\n","Xfce4-Composite-Editor\nhttp://gtk-apps.org/content/show.php/Xfce4-Composite-Editor?content=149523\n","KKEdit\nhttp://gtk-apps.org/content/show.php?content=158161\n","Manpage Editor\nhttp://gtk-apps.org/content/show.php?content=160219\n","GtkSu\nhttp://gtk-apps.org/content/show.php?content=158974\n","ASpell GUI\nhttp://gtk-apps.org/content/show.php/?content=161353",NULL};
	const char	copyright[] ="Copyright \xc2\xa9 2013 K.D.Hedger";
	char*		license=NULL;
	char*		doc=NULL;
	FILE*		fd=NULL;
	long		fsize=0;

	asprintf(&doc,"%s/docs/gpl-3.0.txt",DATADIR);
	fd=fopen(doc,"r");

	if(fd!=NULL)
		{
			fseek(fd,0,SEEK_END);
			fsize=ftell(fd);
			fseek(fd,0,SEEK_SET);
			license=(char*)malloc(fsize+1);
			fread(license,fsize,1,fd);
			fclose(fd);
			license[fsize]=0;
		}

	gtk_show_about_dialog(NULL,"authors",authors,"copyright",copyright,"version",VERSION,"website",MYWEBSITE,"program-name","ClipboardViewer","logo-icon-name","ClipboardViewer","license",license,NULL); 
}

void doSticky(GtkWidget* widget,gpointer data)
{
	if(gtk_toggle_button_get_active((GtkToggleButton*)widget)==true)
		{
			gtk_window_stick(GTK_WINDOW(window));
			gtk_button_set_label((GtkButton*)widget,"Un-Stick");
			gtk_window_set_keep_above((GtkWindow*)window,true);
		}
	else
		{
			gtk_window_unstick(GTK_WINDOW(window));		
			gtk_button_set_label((GtkButton*)widget,"Stick");
			gtk_window_set_keep_above((GtkWindow*)window,false);
		}

}

void buildMainGui(void)
{
	GtkWidget*	vbox;
	GtkWidget*	hbox;
	GtkWidget*	button;

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title((GtkWindow*)window,"Clipboard");
	gtk_window_set_default_size((GtkWindow*)window,320,60);
	vbox=gtk_vbox_new(false,8);

	notebook=gtk_notebook_new();
	gtk_notebook_set_show_tabs((GtkNotebook*)notebook,false);

//text clip
	scrollBox=gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollBox),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	bufferBox=(GtkWidget*)gtk_text_buffer_new(NULL);
	viewBox=(GtkWidget*)gtk_text_view_new_with_buffer((GtkTextBuffer*)bufferBox);
	gtk_text_view_set_wrap_mode((GtkTextView*)viewBox,GTK_WRAP_WORD);
	gtk_container_add(GTK_CONTAINER(scrollBox),(GtkWidget*)viewBox);

	gtk_notebook_append_page((GtkNotebook*)notebook,scrollBox,NULL);

//image clip
	scrollPicBox=gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollPicBox),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	imageBox=gtk_image_new();
	gtk_scrolled_window_add_with_viewport((GtkScrolledWindow*)scrollPicBox,imageBox);

	gtk_notebook_append_page((GtkNotebook*)notebook,scrollPicBox,NULL);

	gtk_container_add(GTK_CONTAINER(vbox),(GtkWidget*)notebook);

//buttons
	hbox=gtk_hbox_new(false,8);

	button=gtk_button_new_from_stock(GTK_STOCK_ABOUT);
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(doAbout),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,false,false,4);

	button=gtk_toggle_button_new_with_label("Un-Stick");
	gtk_toggle_button_set_active((GtkToggleButton*)button,true);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(doSticky),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,true,true,2);

//combo box
	char	tbuff[64]={0};
	clipListDrop=gtk_combo_box_text_new();
	for(int j=0;j<MAXCLIPS;j++)
		{
			sprintf(tbuff,"Clip No. %i",j);
			gtk_combo_box_text_append_text((GtkComboBoxText*)clipListDrop,tbuff);
			clip[j].text=NULL;
			clip[j].image=NULL;
			clip[j].realclip=NULL;
		}
	gtk_combo_box_set_active((GtkComboBox*)clipListDrop,0);
	g_signal_connect(G_OBJECT(clipListDrop),"changed",G_CALLBACK(setClip),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),clipListDrop,true,true,2);

	button=gtk_button_new_from_stock(GTK_STOCK_QUIT);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(doShutdown),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,false,false,2);
	gtk_box_pack_start(GTK_BOX(vbox),(GtkWidget*)hbox,false,false,2);

	g_signal_connect(G_OBJECT(window),"delete-event",G_CALLBACK(doShutdown),NULL);
	gtk_container_add(GTK_CONTAINER(window),(GtkWidget*)vbox);
}

int main(int argc, char **argv)
{
	gtk_init(&argc,&argv);

	mainclipboard=gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
	g_signal_connect(G_OBJECT(mainclipboard),"owner-change",G_CALLBACK(clipChanged),NULL);

	tempname=tempnam("./","image");
	strcat(tempname,".png");

	if (argc>1 && g_ascii_strcasecmp(argv[1],"--nogui")==0)
		{
			GdkPixbuf	*image=gtk_clipboard_wait_for_image(mainclipboard);
		
			if (image!=NULL)
				{
					gdk_pixbuf_save(image,tempname, "png",NULL,NULL, NULL, NULL);
					g_object_unref((gpointer) image);
					printf(tempname);
					free(tempname);
				}
			else
				{
					gchar	*clipText=gtk_clipboard_wait_for_text(mainclipboard);

				if (clipText!=NULL)
					{
						printf(clipText);
						free(clipText);
					}
				}
			return 0;
		}

	if (argc>1 && g_ascii_strcasecmp(argv[1],"--query")==0)
		{
			GdkPixbuf	*image=gtk_clipboard_wait_for_image(mainclipboard);
			if (image!=NULL)
				{
					printf("image\n");
					g_object_unref((gpointer) image);
					return 0;
				}
			gchar	*clipText=gtk_clipboard_wait_for_text(mainclipboard);
			if (clipText!=NULL)
				{
					printf("text\n");
					g_free(clipText);
					return 0;
				}
		}

	if (argc>1)
		{
			printf("clipboardviewer %s\n%s: invalid option\n",VERSION,argv[1]);
			printf("Usage:	clipboardviewer [--nogui] [--query]\n");
			return 1;
		}

	buildMainGui();
	gtk_window_stick(GTK_WINDOW(window));
	gtk_window_set_keep_above((GtkWindow*)window,true);
	clipChanged(mainclipboard,NULL);
	gtk_window_set_default_icon_name(PACKAGE);
	gtk_widget_show_all(window);
	
	gtk_main();
}
