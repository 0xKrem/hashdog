#include <gtk/gtk.h>
#include <string.h>

static void resolve_hash(GtkWidget *button, gpointer data) {
    GtkEntry *hash_entry = GTK_ENTRY(((GtkWidget **)data)[0]);
    GtkLabel *result_label = GTK_LABEL(((GtkWidget **)data)[1]);

    const gchar *hash = gtk_editable_get_text(GTK_EDITABLE(hash_entry));

    gchar *result = NULL;
    if (g_strcmp0(hash, "h") == 0) {
        result = g_strdup("password123");
    } else {
        result = g_strdup("Unknown hash");
    }

    gtk_label_set_text(result_label, result);
    g_free(result);
}

static void open_file_dialog(GtkWidget *button, gpointer data) {
    GtkFileDialog *dialog = gtk_file_dialog_new();
    gtk_file_dialog_set_title(dialog, "Select a Dictionary");
    gtk_file_dialog_set_modal(dialog, TRUE);
    gtk_file_dialog_open(dialog, GTK_WINDOW(data), NULL, NULL, NULL);
}

static void toggle_theme(GtkWidget *button, gpointer provider) {
    const gchar *current_label = gtk_button_get_label(GTK_BUTTON(button));

    if (g_strcmp0(current_label, "Light") == 0) {
        gtk_css_provider_load_from_string(GTK_CSS_PROVIDER(provider), "* { background: white; color: black; }");
        gtk_button_set_label(GTK_BUTTON(button), "Dark");
    } else {
        gtk_css_provider_load_from_string(GTK_CSS_PROVIDER(provider), "* { background: black; color: white; }");
        gtk_button_set_label(GTK_BUTTON(button), "Light");
    }
}

static void verbose_mode(GtkWidget *button, gpointer data) {
    GtkButton *yes_button = GTK_BUTTON(data);
    GtkButton *no_button = GTK_BUTTON(button);
    gtk_widget_set_sensitive(GTK_WIDGET(yes_button), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(no_button), FALSE);
}

static void show_save_message(GtkWidget *button, gpointer data) {
    GtkLabel *message_label = GTK_LABEL(data);
    gtk_label_set_text(message_label, "Modifications are saved");
}

static void show_settings(GtkWidget *button, gpointer window) {
    g_print("Entering show_settings function\n");

    GtkWidget *settings_window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(settings_window), "Settings");
    gtk_window_set_default_size(GTK_WINDOW(settings_window), 400, 300);
    gtk_window_set_transient_for(GTK_WINDOW(settings_window), GTK_WINDOW(window));
    g_signal_connect(settings_window, "destroy", G_CALLBACK(gtk_window_destroy), NULL);

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

    // Attack Mode
    GtkWidget *attack_mode_label = gtk_label_new("Attack Mode:");
    gtk_grid_attach(GTK_GRID(grid), attack_mode_label, 0, 0, 1, 1);

    const char *modes[] = {"Dictionary", "Bruteforce"};
    GtkStringList *mode_list = gtk_string_list_new(modes);
    GtkWidget *attack_mode_combo = gtk_drop_down_new(G_LIST_MODEL(mode_list), NULL);
    gtk_grid_attach(GTK_GRID(grid), attack_mode_combo, 1, 0, 1, 1);

    // Bruteforce Settings
    GtkWidget *bruteforce_label = gtk_label_new("Default Bruteforce Character Set:");
    gtk_grid_attach(GTK_GRID(grid), bruteforce_label, 0, 1, 1, 1);
    GtkWidget *checkbox_upper = gtk_check_button_new_with_label("Upper Case");
    GtkWidget *checkbox_lower = gtk_check_button_new_with_label("Lower Case");
    GtkWidget *checkbox_numbers = gtk_check_button_new_with_label("Numbers");
    GtkWidget *checkbox_symbols = gtk_check_button_new_with_label("Symbols");
    gtk_grid_attach(GTK_GRID(grid), checkbox_upper, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), checkbox_lower, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), checkbox_numbers, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), checkbox_symbols, 0, 5, 1, 1);

    GtkWidget *min_password_length_label = gtk_label_new("Min Password Length:");
    gtk_grid_attach(GTK_GRID(grid), min_password_length_label, 0, 6, 1, 1);
    GtkWidget *min_password_length_spin = gtk_spin_button_new_with_range(4, 100, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(min_password_length_spin), 4);
    gtk_grid_attach(GTK_GRID(grid), min_password_length_spin, 1, 6, 1, 1);

    GtkWidget *max_password_length_label = gtk_label_new("Max Password Length:");
    gtk_grid_attach(GTK_GRID(grid), max_password_length_label, 0, 7, 1, 1);
    GtkWidget *max_password_length_spin = gtk_spin_button_new_with_range(4, 100, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(max_password_length_spin), 10);
    gtk_grid_attach(GTK_GRID(grid), max_password_length_spin, 1, 7, 1, 1);

    GtkWidget *salt_label = gtk_label_new("Default Salt:");
    gtk_grid_attach(GTK_GRID(grid), salt_label, 0, 8, 1, 1);
    GtkWidget *salt_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), salt_entry, 1, 8, 1, 1);

    GtkWidget *algorithm_label = gtk_label_new("Default Algorithm:");
    gtk_grid_attach(GTK_GRID(grid), algorithm_label, 0, 9, 1, 1);
    const char *algorithms[] = {"SHA256", "MD5"};
    GtkStringList *algorithm_list = gtk_string_list_new(algorithms);
    GtkWidget *algorithm_combo = gtk_drop_down_new(G_LIST_MODEL(algorithm_list), NULL);
    gtk_grid_attach(GTK_GRID(grid), algorithm_combo, 1, 9, 1, 1);

    GtkWidget *wordlist_label = gtk_label_new("Default Wordlist:");
    gtk_grid_attach(GTK_GRID(grid), wordlist_label, 0, 10, 1, 1);
    GtkWidget *wordlist_button = gtk_button_new_with_label("Select Wordlist");
    g_signal_connect(wordlist_button, "clicked", G_CALLBACK(open_file_dialog), settings_window);
    gtk_grid_attach(GTK_GRID(grid), wordlist_button, 1, 10, 1, 1);

    GtkWidget *output_label = gtk_label_new("Default Output Path:");
    gtk_grid_attach(GTK_GRID(grid), output_label, 0, 11, 1, 1);
    GtkWidget *output_button = gtk_button_new_with_label("Select Output Path");
    g_signal_connect(output_button, "clicked", G_CALLBACK(open_file_dialog), settings_window);
    gtk_grid_attach(GTK_GRID(grid), output_button, 1, 11, 1, 1);

    GtkWidget *verbose_label = gtk_label_new("Verbose Mode:");
    gtk_grid_attach(GTK_GRID(grid), verbose_label, 0, 12, 1, 1);

    GtkWidget *verbose_yes = gtk_button_new_with_label("Yes");
    GtkWidget *verbose_no = gtk_button_new_with_label("No");
    gtk_widget_set_sensitive(GTK_WIDGET(verbose_no), FALSE);
    g_signal_connect(verbose_yes, "clicked", G_CALLBACK(verbose_mode), verbose_no);
    g_signal_connect(verbose_no, "clicked", G_CALLBACK(verbose_mode), verbose_yes);
    gtk_grid_attach(GTK_GRID(grid), verbose_yes, 1, 12, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), verbose_no, 1, 13, 1, 1);

    GtkWidget *mode_label = gtk_label_new("Mode:");
    gtk_grid_attach(GTK_GRID(grid), mode_label, 0, 14, 1, 1);
    GtkWidget *theme_button = gtk_button_new_with_label("Light");
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_signal_connect(theme_button, "clicked", G_CALLBACK(toggle_theme), provider);
    gtk_grid_attach(GTK_GRID(grid), theme_button, 1, 14, 1, 1);

    // Save Button
    GtkWidget *save_button = gtk_button_new_with_label("Save");
    GtkWidget *message_label = gtk_label_new("");
    g_signal_connect(save_button, "clicked", G_CALLBACK(show_save_message), message_label);
    gtk_grid_attach(GTK_GRID(grid), save_button, 0, 15, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), message_label, 1, 15, 1, 1);

    gtk_widget_set_visible(settings_window, TRUE);

    g_print("Exiting show_settings function\n");
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Hash Resolver");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 800);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_destroy), NULL);

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
    gtk_grid_attach(GTK_GRID(grid), hash_entry, 0, 1, 1, 1);

    GtkWidget *resolve_button = gtk_button_new_with_label("Resolve Hash");
    GtkWidget *result_label = gtk_label_new("");
    GtkWidget *widgets[] = {hash_entry, result_label};
    g_signal_connect(resolve_button, "clicked", G_CALLBACK(resolve_hash), widgets);
    gtk_grid_attach(GTK_GRID(grid), resolve_button, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), result_label, 0, 3, 1, 1);

    GtkWidget *settings_button = gtk_button_new_with_label("Settings");
    g_signal_connect(settings_button, "clicked", G_CALLBACK(show_settings), window);
    gtk_grid_attach(GTK_GRID(grid), settings_button, 0, 4, 1, 1);

    gtk_widget_set_visible(window, TRUE);
}

int main(int argc, char *argv[]) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.HashResolver", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

