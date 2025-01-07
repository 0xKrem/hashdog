<<<<<<< HEAD
// external libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// internal libs
#include "functions.h"

// local functions
int printHelp();


int main(int argc, char** argv) {
	
	char args[] = {'a', 'd', 'm', 'p', 'c', 's', 't', 'x', 'n'}; // defines possible arguments
	unsigned short nbFlag = strlen(args);

	char*** params; // hold the config and current args

	char** argValues = malloc(nbFlag * sizeof(char*)); // store all argument values
	if (argValues == NULL) {
		printf("Error : Memory allocation failed\n");
	}


	unsigned int* nv = malloc(sizeof(int)); // number of params
	if (nv == NULL) {
		printf("Error: Memory allocation failed\n");
		exit(1);
	} 

	// exit if no args
	if (argc == 1) {
		printHelp();
		exit(0);
	}

	// initializing config-file
	FILE* config = fopen("config", "r");

	if (config == NULL) {
		printf("Error: No config file found\n");
		exit(1);
	} 

	// initializing params from config-file
	params = configParser(config, nv);
	if (params == NULL) {
		fclose(config);
		return 1;
	}

	// parsing arguments
	argParser(argc, argv, args, argValues, nbFlag);

	// fallback to default values
	if (fallbackToConfig(args, argValues, params, *nv) != 0) {
		return 1;
	}
	
	//debug print after fallback
	// printParams(params, *nv);
	// for (unsigned short i = 0; i < nbFlag; i++) {
	// 	printf("-%c = %s\n", args[i], argValues[i]);
	// }

	// validating arguments
	if (argValidate(args, argValues) != 0) {
		return 1;
	}

	printf("\n"); //debug

	// Mode
	if (strcmp(*argVal('m', args, argValues), "dict") == 0) {

		printf("Method : Dictionary Attack\n");
		printf("Target : %s\n", argValues[3]);
		printf("Algorithm : %s\n\n", argValues[0]);
		dictAtk(argValues[1], argValues[0], argValues[3]);

	} else  if (strcmp(*argVal('m', args, argValues), "rainbow") == 0) {

		printf("Method : Rainbow table Attack\n");

	} else  if (strcmp(*argVal('m', args, argValues), "bruteforce") == 0) {
		printf("Method : Bruteforce Attack\n");
		
		bruteforce(*argVal('c', args, argValues), *argVal('a', args, argValues), *argVal('x', args, argValues), *argVal('n', args, argValues), *argVal('p', args, argValues));

	} else { printf("Error : Unavailable method '%s'\n", argValues[2]); }

	// for Mr. Sananes
	fclose(config);

	free(argValues);

	//free params
	for (unsigned int i = 0; i < *nv; i++) {
		free(params[0][i]);
	}
	free(params[0]);
	free(params[1]);
	free(params);
	free(nv);
	return 0;
}


int printHelp() {
	// char args[] = {'a', 'd', 'm', 'p', 'c', 's', 't', 'x', 'n'}; // defines possible arguments
	printf(BOLD YELLOW "This program performs attacks on a hashed passord\n" RESET);
	printf(BOLD YELLOW "It takes the following arguments :\n" RESET);

	printf(BOLD GREEN "-p : Hashed password\n\n" RESET);
	printf("  Example : '5E884898DA28047151D0E56F8DC6292773603D0D6AABBDD62A11EF721D1542D8'\n\n");

	printf(BOLD GREEN "-m : Methode\n" RESET);
	printf("    'dict', 'bruteforce'\n\n" );

	printf(BOLD GREEN "-a : Hashing algorithm\n" RESET);
	printf("  Currently supported : 'md5' or 'sha256'\n\n");

	printf(BOLD GREEN "-d : Dictionnary [dict]\n" RESET);
	printf("  - Provides a wordlist file for a dictionnary attack\n\n");

	printf(BOLD GREEN "-c : Character-set [bruteforce]\n" RESET);
	printf("  - Provides a character set for a bruteforce attack\n");
	printf("  - 'n' : numbers [0-9]\n");
	printf("  - 'l' : lowercase letters [abc]\n");
	printf("  - 'u' : uppercase letters [ABC]\n");
	printf("  Example: 'ln' for lowercase + numbers\n\n");

	printf(BOLD GREEN "-s : Salt\n" RESET);
	printf("  - allows to use a salt to try on the password\n\n");

	printf(BOLD GREEN "-n : Minimum length [bruteforce]\n" RESET);
	printf("  - When in bruteforce mode, this is the base number of characters\n\n");

	printf(BOLD GREEN "-x : Max length [bruteforce]\n" RESET);
	printf("  - When in bruteforce mode, this is the max number of characters\n\n");

	return 0;
}

=======
#include <gtk/gtk.h>
#include "functions.h"

// Déclaration de la fonction on_resolve_button_clicked
static void on_resolve_button_clicked(GtkWidget *widget, gpointer data);

// Variables globales pour les noms des fichiers
const char *file_rockyou = "rockyou.txt";
const char *file_dict = "dict.txt";

// Fonction pour le bouton "Start" sur l'écran de bienvenue
static void on_welcome_start_button_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *main_window = GTK_WIDGET(data);
    gtk_window_present(GTK_WINDOW(main_window));
}

// Fonction pour afficher le contenu d'un fichier
static void display_file_content(GtkWidget *widget, gpointer data) {
    const char *filename = (const char *)data;
    GtkWidget *dialog;
    GtkWidget *scrolled_window;
    GtkWidget *content_view;
    GtkTextBuffer *buffer;
    char *content;
    gsize length;
    GError *error = NULL;

    if (g_file_get_contents(filename, &content, &length, &error)) {
        dialog = gtk_window_new();
        gtk_window_set_title(GTK_WINDOW(dialog), filename);
        gtk_window_set_default_size(GTK_WINDOW(dialog), 600, 400);

        scrolled_window = gtk_scrolled_window_new();
        gtk_window_set_child(GTK_WINDOW(dialog), scrolled_window);

        content_view = gtk_text_view_new();
        gtk_text_view_set_editable(GTK_TEXT_VIEW(content_view), FALSE);
        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(content_view));
        gtk_text_buffer_set_text(buffer, content, length);

        gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), content_view);

        gtk_window_present(GTK_WINDOW(dialog));
        g_free(content);
    } else {
        g_printerr("Error reading file: %s\n", error->message);
        g_error_free(error);
    }
}

// Fonction pour le bouton "Files"
static void on_files_button_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;
    GtkWidget *list_box;
    GtkWidget *list_item;
    const char *files[] = {file_rockyou, file_dict};
    int i;

    dialog = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "Files");
    gtk_window_set_default_size(GTK_WINDOW(dialog), 400, 300);

    list_box = gtk_list_box_new();
    gtk_window_set_child(GTK_WINDOW(dialog), list_box);

    for (i = 0; i < G_N_ELEMENTS(files); i++) {
        list_item = gtk_button_new_with_label(files[i]);
        g_signal_connect(list_item, "clicked", G_CALLBACK(display_file_content), (gpointer)files[i]);
        gtk_list_box_insert(GTK_LIST_BOX(list_box), list_item, -1);
    }

    gtk_window_present(GTK_WINDOW(dialog));
}

// Fonction pour le bouton "Settings"
static void on_settings_button_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *settings_window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(settings_window), "Settings");
    gtk_window_set_default_size(GTK_WINDOW(settings_window), 800, 600);

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

// Fonction de résolution de hash
void resolve_hash(const char *hash, GtkEntryBuffer *result_buffer) {
    char result[256] = "Password not found";  // Message par défaut si le mot de passe n'est pas trouvé

    // Exemple de méthodes de résolution (à compléter)
    if (checkDigest("sha256", (char*)hash) || checkDigest("md5", (char*)hash)) {
        // Appeler les méthodes de résolution appropriées
        // Pour cet exemple, nous utilisons bruteforce et dictAtk directement

        // Appel de brute force (chaîne de caractères arbitraire pour charset, algo, max, min)
        bruteforce("nlu", "sha256", "10", "4", (char*)hash);
        
        // Appel d'attaque par dictionnaire (utilisation de rockyou.txt)
        dictAtk((char *)file_rockyou, "sha256", (char*)hash);
    }

    gtk_entry_buffer_set_text(result_buffer, result, -1);
}

// Fonction appelée lorsque le bouton "Resolve" est cliqué
static void on_resolve_button_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *main_grid = GTK_WIDGET(data);
    GtkWidget *hash_entry = g_object_get_data(G_OBJECT(main_grid), "hash_entry");
    GtkEntryBuffer *result_buffer = g_object_get_data(G_OBJECT(main_grid), "result_buffer");

    // Utilisez gtk_editable_get_text() à la place de gtk_entry_get_text() pour GTK4
    const char *hash = gtk_editable_get_text(GTK_EDITABLE(hash_entry));

    // Appeler la fonction de résolution de hash avec le hash saisi et le buffer de résultat
    resolve_hash(hash, result_buffer);
}


// Fonction principale d'activation de l'application
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
    GtkWidget *result_entry;
    GtkWidget *resolve_button;
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
    g_object_set_data(G_OBJECT(main_grid), "hash_entry", hash_entry);  // Enregistrer pour plus tard

    // Ajouter un espace vide pour éloigner les champs
    gtk_grid_attach(GTK_GRID(main_grid), gtk_label_new(""), 0, 4, 1, 1);

    // Ajouter le label pour "Result is:"
    result_label = gtk_label_new("Result:");
    gtk_grid_attach(GTK_GRID(main_grid), result_label, 0, 5, 1, 1);

    // Ajouter le champ de saisie pour le mot de passe (résultat)
    result_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(result_entry), "Password will be displayed here");
    gtk_entry_set_visibility(GTK_ENTRY(result_entry), TRUE); // Afficher le texte du mot de passe
    gtk_widget_set_halign(result_entry, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(result_entry, GTK_ALIGN_CENTER);
    gtk_grid_attach(GTK_GRID(main_grid), result_entry, 0, 6, 1, 1);
    GtkEntryBuffer *result_buffer = gtk_entry_get_buffer(GTK_ENTRY(result_entry));
    g_object_set_data(G_OBJECT(main_grid), "result_buffer", result_buffer);  // Enregistrer pour plus tard

    // Ajouter un espace vide pour éloigner les champs
    gtk_grid_attach(GTK_GRID(main_grid), gtk_label_new(""), 0, 7, 1, 1);

    // Ajouter le bouton "Resolve"
    resolve_button = gtk_button_new_with_label("Resolve");
    g_signal_connect(resolve_button, "clicked", G_CALLBACK(on_resolve_button_clicked), main_grid);
    gtk_widget_set_halign(resolve_button, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(resolve_button, GTK_ALIGN_CENTER);
    gtk_grid_attach(GTK_GRID(main_grid), resolve_button, 0, 8, 1, 1);

    // Connexion du bouton "Start" à la fenêtre principale
    g_signal_connect(welcome_start_button, "clicked", G_CALLBACK(on_welcome_start_button_clicked), main_window);
    gtk_grid_attach(GTK_GRID(welcome_grid), welcome_start_button, 0, 1, 1, 1);

    gtk_window_present(GTK_WINDOW(welcome_window));
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.HashResolver", G_APPLICATION_DEFAULT_FLAGS);
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
>>>>>>> dbc4c29506f54b019524cdf595c5b7ab00ccfadd
