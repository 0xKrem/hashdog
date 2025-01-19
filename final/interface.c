#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

// Pointeurs globaux pour stocker les widgets
GtkWidget *hash_entry;
GtkWidget *result_label;
GtkWidget *attack_mode_combo;
GtkWidget *wordlist_entry;
GtkWidget *min_password_length_spin;
GtkWidget *max_password_length_spin;
GtkWidget *checkbox_upper, *checkbox_lower, *checkbox_numbers, *checkbox_symbols;

// Fonction pour afficher une boite de dialogue d'erreur
void show_error_message(const char *message) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// Fonction pour recuperer les options du bruteforce
void get_charset_options(char *options) {
    strcpy(options, "");
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox_upper))) strcat(options, "u");
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox_lower))) strcat(options, "l");
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox_numbers))) strcat(options, "d");
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox_symbols))) strcat(options, "s");
}

// Fonction principale pour resoudre le hash
static void resolve_hash(GtkWidget *button, gpointer data) {
    const gchar *hash_input = gtk_entry_get_text(GTK_ENTRY(hash_entry));

    if (strlen(hash_input) == 0) {
        show_error_message("Veuillez entrer un hash.");
        return;
    }

    const char *algo = NULL;
    if (!checkCharValid(hash_input, &algo)) {
        show_error_message("Hash invalide. Assurez-vous qu'il est en format MD5 ou SHA-256.");
        return;
    }

    const char *mode = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(attack_mode_combo));

    if (strcmp(mode, "Dictionary") == 0) {
        const char *dict_path = gtk_entry_get_text(GTK_ENTRY(wordlist_entry));
        if (strlen(dict_path) == 0) {
            show_error_message("Veuillez s�lectionner un fichier dictionnaire.");
            return;
        }
        if (dictAtk((char *)dict_path, (char *)algo, (char *)hash_input) == 0) {
            gtk_label_set_text(GTK_LABEL(result_label), "Mot de passe trouv� !");
        } else {
            gtk_label_set_text(GTK_LABEL(result_label), "Aucune correspondance trouv�e.");
        }

    } else if (strcmp(mode, "Bruteforce") == 0) {
        char charset[10];
        get_charset_options(charset);

        int min_len = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(min_password_length_spin));
        int max_len = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(max_password_length_spin));

        if (bruteforce(charset, (char *)algo, g_strdup_printf("%d", max_len), g_strdup_printf("%d", min_len), (char *)hash_input) == 0) {
            gtk_label_set_text(GTK_LABEL(result_label), "Mot de passe trouv� !");
        } else {
            gtk_label_set_text(GTK_LABEL(result_label), "Aucune correspondance trouv�e.");
        }
    }
}

// Fonction pour ouvrir un selecteur de fichier pour le dictionnaire
static void open_file_dialog(GtkWidget *button, gpointer data) {
    GtkWidget *dialog = gtk_file_chooser_dialog_new("S�lectionner un fichier dictionnaire", NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
                                                    "_Annuler", GTK_RESPONSE_CANCEL, "_Ouvrir", GTK_RESPONSE_ACCEPT, NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        gtk_entry_set_text(GTK_ENTRY(wordlist_entry), filename);
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

// Fonction principale GTK3
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Hash Resolver");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Champ Hash
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Entrer le hash:"), 0, 0, 1, 1);
    hash_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), hash_entry, 1, 0, 1, 1);

    // Mode d'attaque
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Mode d'attaque:"), 0, 1, 1, 1);
    attack_mode_combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(attack_mode_combo), "Dictionary");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(attack_mode_combo), "Bruteforce");
    gtk_grid_attach(GTK_GRID(grid), attack_mode_combo, 1, 1, 1, 1);

    // Selection du fichier dictionnaire
    wordlist_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), wordlist_entry, 1, 2, 1, 1);
    GtkWidget *select_file_button = gtk_button_new_with_label("S�lectionner...");
    g_signal_connect(select_file_button, "clicked", G_CALLBACK(open_file_dialog), NULL);
    gtk_grid_attach(GTK_GRID(grid), select_file_button, 2, 2, 1, 1);

    // Parametres Bruteforce
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Min Password Length:"), 0, 3, 1, 1);
    min_password_length_spin = gtk_spin_button_new_with_range(4, 100, 1);
    gtk_grid_attach(GTK_GRID(grid), min_password_length_spin, 1, 3, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Max Password Length:"), 0, 4, 1, 1);
    max_password_length_spin = gtk_spin_button_new_with_range(4, 100, 1);
    gtk_grid_attach(GTK_GRID(grid), max_password_length_spin, 1, 4, 1, 1);

    checkbox_upper = gtk_check_button_new_with_label("Upper Case");
    gtk_grid_attach(GTK_GRID(grid), checkbox_upper, 0, 5, 1, 1);
    checkbox_lower = gtk_check_button_new_with_label("Lower Case");
    gtk_grid_attach(GTK_GRID(grid), checkbox_lower, 1, 5, 1, 1);
    checkbox_numbers = gtk_check_button_new_with_label("Numbers");
    gtk_grid_attach(GTK_GRID(grid), checkbox_numbers, 0, 6, 1, 1);
    checkbox_symbols = gtk_check_button_new_with_label("Symbols");
    gtk_grid_attach(GTK_GRID(grid), checkbox_symbols, 1, 6, 1, 1);

    // Bouton Resolve
    GtkWidget *resolve_button = gtk_button_new_with_label("R�soudre le Hash");
    g_signal_connect(resolve_button, "clicked", G_CALLBACK(resolve_hash), NULL);
    gtk_grid_attach(GTK_GRID(grid), resolve_button, 0, 7, 2, 1);

    result_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), result_label, 0, 8, 2, 1);

    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
   GtkApplication *app = gtk_application_new("com.example.HashResolver", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
