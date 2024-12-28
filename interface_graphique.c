#include <gtk/gtk.h>

// Fonction pour le bouton "Start" sur l'écran de bienvenue
static void on_welcome_start_button_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *main_window = GTK_WIDGET(data);
    gtk_window_present(GTK_WINDOW(main_window));
}

// Fonction pour le bouton "Settings"
static void on_settings_button_clicked(GtkWidget *widget, gpointer data) {
    g_print("Settings button clicked\n");

    // Créer une nouvelle fenêtre pour les paramètres
    GtkWidget *settings_window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(settings_window), "Settings");
    gtk_window_set_default_size(GTK_WINDOW(settings_window), 800, 600);

    // Créer un conteneur et ajouter des options de paramètres
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(settings_window), box);

    // Mode (Dark, Light)
    GtkWidget *mode_label = gtk_label_new("Mode:");
    gtk_box_append(GTK_BOX(box), mode_label);
    GtkStringList *mode_list = gtk_string_list_new((const char *[]){"Dark", "Light", NULL});
    GtkWidget *mode_combo = gtk_drop_down_new(G_LIST_MODEL(mode_list), NULL);
    gtk_box_append(GTK_BOX(box), mode_combo);

    // Bruteforce timeout
    GtkWidget *timeout_label = gtk_label_new("Bruteforce timeout:");
    gtk_box_append(GTK_BOX(box), timeout_label);
    GtkWidget *timeout_spin_button = gtk_spin_button_new_with_range(1, 3600, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(timeout_spin_button), 5);
    gtk_box_append(GTK_BOX(box), timeout_spin_button);

    // Default algorithm (md5, sha256)
    GtkWidget *algorithm_label = gtk_label_new("Default algorithm:");
    gtk_box_append(GTK_BOX(box), algorithm_label);
    GtkStringList *algorithm_list = gtk_string_list_new((const char *[]){"md5", "sha256", NULL});
    GtkWidget *algorithm_combo = gtk_drop_down_new(G_LIST_MODEL(algorithm_list), NULL);
    gtk_box_append(GTK_BOX(box), algorithm_combo);

    // Default wordlist (rockyou.txt, dict.txt)
    GtkWidget *wordlist_label = gtk_label_new("Default wordlist:");
    gtk_box_append(GTK_BOX(box), wordlist_label);
    GtkStringList *wordlist_list = gtk_string_list_new((const char *[]){"rockyou.txt", "dict.txt", NULL});
    GtkWidget *wordlist_combo = gtk_drop_down_new(G_LIST_MODEL(wordlist_list), NULL);
    gtk_box_append(GTK_BOX(box), wordlist_combo);

    // Default salt (texte défini par l'utilisateur)
    GtkWidget *salt_label = gtk_label_new("Default salt:");
    gtk_box_append(GTK_BOX(box), salt_label);
    GtkWidget *salt_entry = gtk_entry_new();
    gtk_box_append(GTK_BOX(box), salt_entry);

    // Default attack mode (dictionary attack, bruteforce)
    GtkWidget *attack_mode_label = gtk_label_new("Default attack mode:");
    gtk_box_append(GTK_BOX(box), attack_mode_label);
    GtkStringList *attack_mode_list = gtk_string_list_new((const char *[]){"dictionaryattack", "bruteforce", NULL});
    GtkWidget *attack_mode_combo = gtk_drop_down_new(G_LIST_MODEL(attack_mode_list), NULL);
    gtk_box_append(GTK_BOX(box), attack_mode_combo);

    // Minimum password length
    GtkWidget *min_length_label = gtk_label_new("Minimum password length:");
    gtk_box_append(GTK_BOX(box), min_length_label);
    GtkWidget *min_length_spin_button = gtk_spin_button_new_with_range(1, 128, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(min_length_spin_button), 4);
    gtk_box_append(GTK_BOX(box), min_length_spin_button);

    // Maximum password length
    GtkWidget *max_length_label = gtk_label_new("Maximum password length:");
    gtk_box_append(GTK_BOX(box), max_length_label);
    GtkWidget *max_length_spin_button = gtk_spin_button_new_with_range(1, 128, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(max_length_spin_button), 10);
    gtk_box_append(GTK_BOX(box), max_length_spin_button);

    // Default output path
    GtkWidget *output_path_label = gtk_label_new("Default output path:");
    gtk_box_append(GTK_BOX(box), output_path_label);
    GtkWidget *output_path_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(output_path_entry), "Enter path");
    gtk_box_append(GTK_BOX(box), output_path_entry);

    // Default bruteforce character set (nlu)
    GtkWidget *charset_label = gtk_label_new("Default bruteforce character set:");
    gtk_box_append(GTK_BOX(box), charset_label);
    GtkStringList *charset_list = gtk_string_list_new((const char *[]){"nlu", NULL});
    GtkWidget *charset_combo = gtk_drop_down_new(G_LIST_MODEL(charset_list), NULL);
    gtk_box_append(GTK_BOX(box), charset_combo);

    // Verbose mode
    GtkWidget *verbose_label = gtk_label_new("Verbose mode:");
    gtk_box_append(GTK_BOX(box), verbose_label);
    GtkWidget *verbose_switch = gtk_switch_new();
    gtk_box_append(GTK_BOX(box), verbose_switch);

    gtk_window_present(GTK_WINDOW(settings_window));
}

// Fonction pour le bouton "Files"
static void on_files_button_clicked(GtkWidget *widget, gpointer data) {
    g_print("Files button clicked\n");

    // Créer une nouvelle fenêtre pour les fichiers
    GtkWidget *files_window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(files_window), "Files");
    gtk_window_set_default_size(GTK_WINDOW(files_window), 800, 600);

    // Créer un conteneur et ajouter du contenu pour les fichiers
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(files_window), box);

    // Exemple : Ajouter une liste de fichiers
    GtkWidget *file_label = gtk_label_new("List of Dictionary Files:");
    gtk_box_append(GTK_BOX(box), file_label);
    GtkWidget *file_list = gtk_label_new("rockyou.txt\n\n\
dict.txt\n\n\
words.txt\n\n\
common-passwords.txt\n\n\
other-dictionary.txt");
    gtk_box_append(GTK_BOX(box), file_list);

    gtk_window_present(GTK_WINDOW(files_window));
}

// Fonction pour l'activation de l'application
static void on_app_activate(GApplication *app, gpointer user_data) {
    GtkWidget *welcome_window;
    GtkWidget *welcome_grid;
    GtkWidget *welcome_label;
    GtkWidget *welcome_start_button;
    GtkWidget *main_window;
    GtkWidget *main_grid;
    GtkWidget *hash_label;
    GtkWidget *hash_entry;
    GtkWidget *result_label;
    GtkWidget *password_entry;
    GtkWidget *settings_button;
    GtkWidget *files_button;

    // Fenêtre de bienvenue
    welcome_window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(welcome_window), "Welcome");
    gtk_window_set_default_size(GTK_WINDOW(welcome_window), 800, 600);

    welcome_grid = gtk_grid_new();
    gtk_widget_set_halign(welcome_grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(welcome_grid, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(welcome_window), welcome_grid);

    welcome_label = gtk_label_new("Welcome to the platform");
    gtk_grid_attach(GTK_GRID(welcome_grid), welcome_label, 0, 0, 1, 1);

    welcome_start_button = gtk_button_new_with_label("Start");
    GtkWidget *button_label = gtk_button_get_child(GTK_BUTTON(welcome_start_button));
    gtk_widget_set_name(button_label, "start_button_label");
    gtk_widget_set_size_request(welcome_start_button, 100, 50);
    gtk_widget_set_halign(welcome_start_button, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(welcome_start_button, GTK_ALIGN_CENTER);

    // Fenêtre principale
    main_window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(main_window), "Main Interface");
    gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);

    main_grid = gtk_grid_new();
    gtk_widget_set_margin_top(main_grid, 20); // Ajouter un grand espace en haut
    gtk_widget_set_halign(main_grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(main_grid, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW(main_window), main_grid);

    // Ajouter le bouton "Settings" en haut à droite
    settings_button = gtk_button_new_with_label("Settings");
    g_signal_connect(settings_button, "clicked", G_CALLBACK(on_settings_button_clicked), NULL);
    gtk_widget_set_halign(settings_button, GTK_ALIGN_END);
    gtk_widget_set_valign(settings_button, GTK_ALIGN_START);
    gtk_grid_attach(GTK_GRID(main_grid), settings_button, 1, 0, 1, 1);

    // Ajouter le bouton "Files" en haut à droite
    files_button = gtk_button_new_with_label("Files");
    g_signal_connect(files_button, "clicked", G_CALLBACK(on_files_button_clicked), NULL);
    gtk_widget_set_halign(files_button, GTK_ALIGN_END);
    gtk_widget_set_valign(files_button, GTK_ALIGN_START);
    gtk_grid_attach(GTK_GRID(main_grid), files_button, 2, 0, 1, 1);

    // Ajouter le champ de saisie pour le hash
    hash_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(hash_entry), "Enter hash");
    gtk_widget_set_halign(hash_entry, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(hash_entry, GTK_ALIGN_CENTER);
    gtk_grid_attach(GTK_GRID(main_grid), hash_entry, 0, 3, 1, 1);

    // Ajouter un espace vide pour éloigner les champs
    gtk_grid_attach(GTK_GRID(main_grid), gtk_label_new(""), 0, 4, 1, 1);

    // Ajouter le label pour "Result is:"
    result_label = gtk_label_new("Result:");
    gtk_grid_attach(GTK_GRID(main_grid), result_label, 0, 5, 1, 1);

    // Ajouter le champ de saisie pour le mot de passe (résultat)
    password_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Password will be displayed here");
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), TRUE); // Afficher le texte du mot de passe
    gtk_widget_set_halign(password_entry, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(password_entry, GTK_ALIGN_CENTER);
    gtk_grid_attach(GTK_GRID(main_grid), password_entry, 0, 6, 1, 1);

    // Ajouter un espace vide pour éloigner les champs
    gtk_grid_attach(GTK_GRID(main_grid), gtk_label_new(""), 0, 7, 1, 1);

    // Connexion du bouton "Start" à la fenêtre principale
    g_signal_connect(welcome_start_button, "clicked", G_CALLBACK(on_welcome_start_button_clicked), main_window);
    gtk_grid_attach(GTK_GRID(welcome_grid), welcome_start_button, 0, 1, 1, 1);

    gtk_window_present(GTK_WINDOW(welcome_window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.SimpleGUI", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);

    // Ajouter le CSS pour personnaliser le bouton
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider,
                                      "#start_button_label {"
                                      "  background-color: white;"
                                      "  color: black;"
                                      "  font-size: 20px;"
                                      "}");
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
