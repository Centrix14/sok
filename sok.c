#include <gtk/gtk.h> 
#define ROW_LEN1 10
#define ROW_LEN2 9
#define ROW_LEN3 7
#define KB_LEN ROW_LEN1+ROW_LEN2+ROW_LEN3

void kb_init(GtkWidget *keys[], int len);
void en_init(GtkWidget *keys[], int len);

int main(int argc, char *argv[]) {
	GtkWidget *window;
	GtkWidget *keyboard[KB_LEN];
	GtkWidget *kb_bar, *row1, *row2, *row3;
	GtkWidget *text;
	int i = 0, j = 0;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "sok");
	gtk_window_set_default_size(GTK_WINDOW(window), 200, 60);

	// При закрытии окна программа завершается
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	kb_init(keyboard, KB_LEN);
	en_init(keyboard, KB_LEN);

	kb_bar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	row1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	row2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	row3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

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

	text = gtk_label_new("Type");
	gtk_label_set_selectable(GTK_LABEL(text), TRUE);

	gtk_box_pack_start(GTK_BOX(kb_bar), text, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(kb_bar), row1, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(kb_bar), row2, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(kb_bar), row3, TRUE, TRUE, 5);

	gtk_container_add(GTK_CONTAINER(window), kb_bar);
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
	char *bttn_letter;
	char letter = 'a';
	static int i = 0;

	for (; i < len; i++) {
		bttn_letter[0] = letter+i;
		gtk_button_set_label(GTK_BUTTON(keys[i]), bttn_letter);
	}
}
