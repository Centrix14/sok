/*
* sok -- simple on-screen keyboard
* v1.0
* 21.11.2019
* by Centrix
*/

#include <stdio.h>
#include <ctype.h>
#include <gtk/gtk.h> 

#define ROW_LEN1 10
#define ROW_LEN2 9
#define ROW_LEN3 7
#define KB_LEN ROW_LEN1+ROW_LEN2+ROW_LEN3

char buffer[256];
int pos = 0;

void kb_init(GtkWidget *keys[], int len);
void en_init(GtkWidget *keys[], int len);
void kb_input(GtkWidget *bttn, gpointer label);
void caps_lk_click(GtkWidget *bttn, GtkWidget *keyboard[]);
void tab_click(GtkWidget *bttn, gpointer label);
void enter_click(GtkWidget *bttn, gpointer label);
void space_click(GtkWidget *bttn, gpointer label);
void ac_click(GtkWidget *bttn, gpointer keyboard[]);
void er_click(GtkWidget *bttn, gpointer label);

int main(int argc, char *argv[]) {
	GtkWidget *window;
	GtkWidget *keyboard[KB_LEN];
	GtkWidget *kb_bar, *row1, *row2, *row3, *top_bar, *main_box;
	GtkWidget *text, *caps_lk, *tab, *enter, *space, *ac, *er;
	int i = 0, j = 0;

	gtk_init(&argc, &argv);

	/* window block */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "sok");
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 60);

	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	/* keyboard block */
	kb_init(keyboard, KB_LEN);
	en_init(keyboard, KB_LEN);

	kb_bar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	row1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	row2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	row3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

	text = gtk_label_new("Type");
	gtk_label_set_selectable(GTK_LABEL(text), TRUE);

	for (int i = 0; i < KB_LEN; i++) {
		g_signal_connect(G_OBJECT(keyboard[i]), "clicked", G_CALLBACK(kb_input), text);
	}

	/* tab block */
	tab = gtk_button_new_with_label("tab");
	g_signal_connect(G_OBJECT(tab), "clicked", G_CALLBACK(tab_click), text);
	gtk_box_pack_start(GTK_BOX(row1), tab, TRUE, TRUE, 5);

	/* caps_lk block */
	caps_lk = gtk_button_new_with_label("caps_lk");
	g_signal_connect(G_OBJECT(caps_lk), "clicked", G_CALLBACK(caps_lk_click), keyboard);
	gtk_box_pack_start(GTK_BOX(row2), caps_lk, TRUE, TRUE, 5);

	/* ac block */
	ac = gtk_button_new_with_label("ac");
	g_signal_connect(G_OBJECT(ac), "clicked", G_CALLBACK(ac_click), keyboard);
	gtk_box_pack_start(GTK_BOX(row3), ac, TRUE, TRUE, 5);

	/* packing the keyboard */
	for (; i < ROW_LEN1; i++) {
		gtk_box_pack_start(GTK_BOX(row1), keyboard[i+j], TRUE, TRUE, 5);
	}
	j += i;
	for (i = 0; i < ROW_LEN2; i++) {
		gtk_box_pack_start(GTK_BOX(row2), keyboard[i+j], TRUE, TRUE, 5);
	}
	j += i;
	for (i = 0; i < ROW_LEN3; i++) {
		gtk_box_pack_start(GTK_BOX(row3), keyboard[i+j], TRUE, TRUE, 5);
	}

	/* enter block */
	enter = gtk_button_new_with_label("enter");
	g_signal_connect(G_OBJECT(enter), "clicked", G_CALLBACK(enter_click), text);
	gtk_box_pack_start(GTK_BOX(row3), enter, TRUE, FALSE, 5);

	/* er block */
	er = gtk_button_new_with_label("<x");
	g_signal_connect(G_OBJECT(er), "clicked", G_CALLBACK(er_click), text);

	/* top_bar block */
	top_bar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_box_pack_start(GTK_BOX(top_bar), text, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(top_bar), er, TRUE, FALSE, 5);

	/* packaging the kb_bar */
	gtk_box_pack_start(GTK_BOX(kb_bar), row1, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(kb_bar), row2, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(kb_bar), row3, TRUE, TRUE, 5);

	/* space block */
	space = gtk_button_new_with_label("Space");
	g_signal_connect(G_OBJECT(space), "clicked", G_CALLBACK(space_click), text);
	gtk_box_pack_start(GTK_BOX(kb_bar), space, TRUE, TRUE, 5);

	/* main_box block */
	main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_pack_start(GTK_BOX(main_box), top_bar, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(main_box), kb_bar, TRUE, TRUE, 5);

	gtk_container_add(GTK_CONTAINER(window), main_box);
	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}

void kb_init(GtkWidget *keys[], int len) {
	for (int i = 0; i < len; i++) {
		keys[i] = gtk_button_new();
	}
}

void en_init(GtkWidget *keys[], int len) {
	char bttn_letter[2];
	char layout[26] = "qwertyuiopasdfghjklzxcvbnm";
	static int i = 0;

	for (; i < len; i++) {
		bttn_letter[0] = layout[i];
		gtk_button_set_label(GTK_BUTTON(keys[i]), bttn_letter);
	}
}

void kb_input(GtkWidget *bttn, gpointer label) {
	char bttn_text[256] = "";

	sprintf(bttn_text, "%s", gtk_button_get_label(GTK_BUTTON(bttn)));
	buffer[pos++] = bttn_text[0];
	gtk_label_set_text(GTK_LABEL(label), buffer);
}

void kb_swap(GtkWidget *keyboard[], int len, int type) { 
	char key[2];
	char new[2];

	for (int i = 0; i < len; i++) {
		sprintf(key, "%s", (char*)gtk_button_get_label(GTK_BUTTON(keyboard[i])));

		if (type == 1)
			sprintf(new, "%c", toupper(key[0]));
		else
			sprintf(new, "%c", tolower(key[0]));

		gtk_button_set_label(GTK_BUTTON(keyboard[i]), new);
	}
}

void caps_lk_click(GtkWidget *bttn, GtkWidget *keyboard[]) {
	static int state = 0;

	state = !state;
	kb_swap(keyboard, 26, state);
}

void tab_click(GtkWidget *bttn, gpointer label) {
	buffer[pos++] = '	';
	gtk_label_set_text(GTK_LABEL(label), buffer);
}

void enter_click(GtkWidget *bttn, gpointer label) {
	buffer[pos++] = '\n';
	gtk_label_set_text(GTK_LABEL(label), buffer);
}

void space_click(GtkWidget *bttn, gpointer label) {
	buffer[pos++] = ' ';
	gtk_label_set_text(GTK_LABEL(label), buffer);
}

void ac_click(GtkWidget *bttn, gpointer keyboard[]) {
	char new_chars[26] = "1234567890.,!?+-*/=\"\';:@#%";
	char bttn_char[2];

	for (int i = 0; i < 26; i++) {
		bttn_char[0] = new_chars[i];
		gtk_button_set_label(GTK_BUTTON(keyboard[i]), bttn_char);
	}
}

void er_click(GtkWidget *bttn, gpointer label) {
	if ( pos > 0 ) {
		buffer[--pos] = 0;
		gtk_label_set_text(GTK_LABEL(label), buffer);
	}
}
