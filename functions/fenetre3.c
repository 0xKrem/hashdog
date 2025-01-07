#include <gtk/gtk.h>
#include <string.h>

// Fonction pour "résoudre" un hash (exemple simple)
static void resolve_hash(GtkWidget *button, gpointer data) {
    GtkEntry *hash_entry = GTK_ENTRY(((GtkWidget **)data)[0]);
    GtkLabel *result_label = GTK_LABEL(((GtkWidget **)data)[1]);

    const gchar *hash = gtk_editable_get_text(GTK_EDITABLE(hash_entry)); // Remplacement pour GTK4

    gchar *result = NULL;
    if (g_strcmp0(hash, "h123636272727727727291982") == 0) {
        result = g_strdup("password123");
    } else {
        result = g_strdup("Unknown hash");
    }

    gtk_label_set_text(result_label, result);
    g_free(result);
}

// Fonction pour ouvrir un fichier de dictionnaire
static void open_file_dialog(GtkWidget *button, gpointer data) {
    GtkFileDialog *dialog = gtk_file_dialog_new();
    gtk_file_dialog_set_title(dialog, "Select a Dictionary");
    gtk_file_dialog_set_modal(dialog, TRUE);
    gtk_file_dialog_open(dialog, GTK_WINDOW(data), NULL, NULL, NULL);
}

// Fonction pour gérer l'affichage des paramètres
static void show_settings(GtkWidget *button, gpointer window) {
    GtkWidget *settings_window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(settings_window), "Settings");
    gtk_window_set_default_size(GTK_WINDOW(settings_window), 400, 300);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_start(grid, 10);
    gtk_widget_set_margin_end(grid, 10);
    gtk_widget_set_margin_top(grid, 10);
    gtk_widget_set_margin_bottom(grid, 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_window_set_child(GTK_WINDOW(settings_window), grid);

    // Default Bruteforce Character Set
    GtkWidget *bruteforce_label = gtk_label_new("Default Bruteforce Character Set:");
    gtk_grid_attach(GTK_GRID(grid), bruteforce_label, 0, 0, 1, 1);
    GtkWidget *checkbox_upper = gtk_check_button_new_with_label("Upper Case");
    GtkWidget *checkbox_lower = gtk_check_button_new_with_label("Lower Case");
    GtkWidget *checkbox_numbers = gtk_check_button_new_with_label("Numbers");
    GtkWidget *checkbox_symbols = gtk_check_button_new_with_label("Symbols");
    gtk_grid_attach(GTK_GRID(grid), checkbox_upper, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), checkbox_lower, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), checkbox_numbers, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), checkbox_symbols, 0, 4, 1, 1);

    // Default Wordlist
    GtkWidget *wordlist_label = gtk_label_new("Default Wordlist:");
    gtk_grid_attach(GTK_GRID(grid), wordlist_label, 0, 5, 1, 1);
    GtkWidget *wordlist_button = gtk_button_new_with_label("Select Wordlist");
    g_signal_connect(wordlist_button, "clicked", G_CALLBACK(open_file_dialog), settings_window);
    gtk_grid_attach(GTK_GRID(grid), wordlist_button, 1, 5, 1, 1);

    // Default Output Path
    GtkWidget *output_label = gtk_label_new("Default Output Path:");
    gtk_grid_attach(GTK_GRID(grid), output_label, 0, 6, 1, 1);
    GtkWidget *output_button = gtk_button_new_with_label("Select Output Path");
    g_signal_connect(output_button, "clicked", G_CALLBACK(open_file_dialog), settings_window);
    gtk_grid_attach(GTK_GRID(grid), output_button, 1, 6, 1, 1);

    gtk_widget_set_visible(settings_window, TRUE);
}

int main(int argc, char *argv[]) {
    gtk_init();

    GtkWidget *window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Hash Resolver");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_start(grid, 10);
    gtk_widget_set_margin_end(grid, 10);
    gtk_widget_set_margin_top(grid, 10);
    gtk_widget_set_margin_bottom(grid, 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_window_set_child(GTK_WINDOW(window), grid);

    GtkWidget *hash_label = gtk_label_new("Enter the hash:");
    gtk_grid_attach(GTK_GRID(grid), hash_label, 0, 0, 1, 1);

    GtkWidget *hash_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), hash_entry, 1, 0, 1, 1);

    GtkWidget *resolve_button = gtk_button_new_with_label("Resolve");
    gtk_grid_attach(GTK_GRID(grid), resolve_button, 1, 1, 1, 1);

    GtkWidget *result_label = gtk_label_new("Result:");
    gtk_grid_attach(GTK_GRID(grid), result_label, 0, 2, 1, 1);

    GtkWidget *result_value = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), result_value, 1, 2, 1, 1);

    GtkWidget *settings_button = gtk_button_new_with_label("Settings");
    gtk_widget_set_halign(settings_button, GTK_ALIGN_END);
    gtk_widget_set_valign(settings_button, GTK_ALIGN_START);
    gtk_grid_attach(GTK_GRID(grid), settings_button, 2, 0, 1, 1);

    GtkWidget *data[] = {hash_entry, result_value};
    g_signal_connect(resolve_button, "clicked", G_CALLBACK(resolve_hash), data);
    g_signal_connect(settings_button, "clicked", G_CALLBACK(show_settings), window);

    gtk_widget_set_visible(window, TRUE);

    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);

    return 0;
}
