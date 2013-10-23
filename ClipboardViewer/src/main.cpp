//
//Keith Hedger
//Tue Jun 12 16:22:48 BST 2007
//
//clipboardview.cpp
//

#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <sys/stat.h>

#include "globals.h"

#if 0
gboolean check(gpointer data)
{
	GtkTextBuffer	*buffer;
	GtkTextIter	startIter;
	GtkTextIter	endIter;

	if (gtk_clipboard_wait_is_text_available(mainclipboard)==true)
		{
		buffer=gtk_text_view_get_buffer (GTK_TEXT_VIEW (glade_xml_get_widget(mainui,"textclip")));
		gchar	*clipText=gtk_clipboard_wait_for_text(mainclipboard);
		if (clipText==NULL)
			return true;
		gtk_text_buffer_get_bounds(buffer,&startIter,&endIter);

		gchar*	oldText=gtk_text_buffer_get_text(buffer,&startIter,&endIter,true);
		
		if (g_ascii_strcasecmp(clipText,oldText)!=0)
			gtk_text_buffer_set_text(buffer,clipText,-1);
		gtk_notebook_set_current_page(GTK_NOTEBOOK(glade_xml_get_widget(mainui,"cliptype")),0);
		g_free(clipText);
		g_free(oldText);
		}

	if (gtk_clipboard_wait_is_image_available(mainclipboard)==true)
		{
		GtkImage	*image=GTK_IMAGE(glade_xml_get_widget(mainui,"imageclip"));
		GdkPixbuf	*pixbuf=gtk_clipboard_wait_for_image(mainclipboard);
		if (pixbuf==NULL)
			return true;

		gtk_image_set_from_pixbuf (image,pixbuf);
		gtk_notebook_set_current_page(GTK_NOTEBOOK(glade_xml_get_widget(mainui,"cliptype")),1);
		g_object_unref(pixbuf);
		}

	return true;
}
#endif
void doShutdown(GtkButton *button, gpointer window_ptr)
{
	gtk_main_quit();
}

void doAbout(GtkWidget* widget,gpointer data)
{
	const char*	authors[]={"K.D.Hedger <"MYEMAIL">","\nMore by the same author\n","Xfce4-Composite-Editor\nhttp://gtk-apps.org/content/show.php/Xfce4-Composite-Editor?content=149523\n","KKEdit\nhttp://gtk-apps.org/content/show.php?content=158161\n","Manpage Editor\nhttp://gtk-apps.org/content/show.php?content=160219\n","GtkSu\nhttp://gtk-apps.org/content/show.php?content=158974",NULL};
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

	gtk_show_about_dialog(NULL,"authors",authors,"copyright",copyright,"version",VERSION,"website",MYWEBSITE,"program-name","Aspell GUI","logo-icon-name","AspellGUI","license",license,NULL); 
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
	GtkWidget*	image;

	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title((GtkWindow*)window,"Aspell GUI");
	gtk_window_set_default_size((GtkWindow*)window,320,60);
	vbox=gtk_vbox_new(false,8);

//text to spell check
	scrollBox=gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollBox),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
	bufferBox=(GtkWidget*)gtk_text_buffer_new(NULL);
	viewBox=(GtkWidget*)gtk_text_view_new_with_buffer((GtkTextBuffer*)bufferBox);
	gtk_text_view_set_wrap_mode((GtkTextView*)viewBox,GTK_WRAP_WORD);
	gtk_container_add(GTK_CONTAINER(scrollBox),(GtkWidget*)viewBox);
	gtk_container_add(GTK_CONTAINER(vbox),(GtkWidget*)scrollBox);

//buttons
	hbox=gtk_hbox_new(false,8);

	button=gtk_button_new_from_stock(GTK_STOCK_ABOUT);
	g_signal_connect_after(G_OBJECT(button),"clicked",G_CALLBACK(doAbout),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,false,false,4);

//	button=gtk_button_new_from_stock(GTK_STOCK_SPELL_CHECK);
//	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(doSpellCheckDoc),NULL);
//	gtk_box_pack_start(GTK_BOX(hbox),button,false,false,2);

//	image=gtk_image_new_from_stock(GTK_STOCK_SPELL_CHECK,GTK_ICON_SIZE_MENU);
//	button=gtk_button_new_with_label("Check Word");
//	gtk_button_set_image((GtkButton*)button,image);

//	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(checkWord),NULL);
//	gtk_box_pack_start(GTK_BOX(hbox),button,false,false,2);

	button=gtk_toggle_button_new_with_label("Un-Stick");
	gtk_toggle_button_set_active((GtkToggleButton*)button,true);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(doSticky),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,true,true,2);

	button=gtk_button_new_from_stock(GTK_STOCK_QUIT);
	g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(doShutdown),NULL);
	gtk_box_pack_start(GTK_BOX(hbox),button,false,false,2);
	gtk_container_add(GTK_CONTAINER(vbox),(GtkWidget*)hbox);

	g_signal_connect(G_OBJECT(window),"delete-event",G_CALLBACK(doShutdown),NULL);
	gtk_container_add(GTK_CONTAINER(window),(GtkWidget*)vbox);
}

int main(int argc, char **argv)
{
	gtk_init(&argc,&argv);
	buildMainGui();
	gtk_widget_show_all(window);
	gtk_main();
}
#if 0
int mainXX(int argc, char **argv)
{
	GtkWindow	*window;
	gchar		*gladepath;

	gtk_init(&argc,&argv);
	mainclipboard=gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);

	tempname=tempnam("./","image");
	strcat(tempname,".png");

	if (argc>1 && g_ascii_strcasecmp(argv[1],"--nogui")==0)
		{
		GdkPixbuf	*image=gtk_clipboard_wait_for_image(mainclipboard);
		
		if (image!=NULL)
			{
			gdk_pixbuf_save(image,tempname, "png",NULL,NULL, NULL, NULL);
			g_object_unref((gpointer) image);
			g_printf(tempname);
			free(tempname);
			}
		else
			{
			gchar	*clipText=gtk_clipboard_wait_for_text(mainclipboard);
			
			if (clipText!=NULL)
				{
				g_printf(clipText);
				g_free(clipText);
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

	if (g_file_test(GLADEFILE,G_FILE_TEST_EXISTS)==TRUE)
		{
			gladepath=GLADEFILE;
			prefixPathToPix=PATHTOPIX;
			prefixPathToScripts=PATHTOSCRIPTS;
		}
	else
		{
			asprintf(&gladepath,"%s","/usr/share/ClipboardViewer/ClipboardViewer.glade");
			asprintf(&prefixPathToPix,"%s","/usr/share/ClipboardViewer/pixmaps");
			asprintf(&prefixPathToScripts,"%s","/usr/share/ClipboardViewer/scripts");
		}

	mainui = glade_xml_new(gladepath, NULL, NULL);
	window = GTK_WINDOW(glade_xml_get_widget(mainui, "clipwindow"));
	gtk_window_stick(GTK_WINDOW(window));
	check(NULL);
	glade_xml_signal_connect_data(mainui,"endprogram",G_CALLBACK(endProgram),GUINT_TO_POINTER(window));

	g_timeout_add(1000,check,NULL);
	gtk_main();
	return 0;
}
#endif