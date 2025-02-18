#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

// Définition de la structure pour les mots et leurs fréquences
typedef struct {
    char *mot;
    int frequence;
} MotFrequence;

// Fonction pour sauvegarder les statistiques dans un fichier texte
void sauvegarder_statistiques(const char *nom_fichier, int nb_carac, int nb_carac_spec, int nb_carac_non_spec, int nb_mots, int nb_lignes, int nb_paragraphes, MotFrequence *tableau_mots, int nb_mots_dico) {
    FILE *file = fopen(nom_fichier, "w");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sauvegarde");
        return;
    }

    fprintf(file, "------ Résultats de l'analyse ------\n");
    fprintf(file, "Nombre total de caractères       : %d\n", nb_carac);
    fprintf(file, "Nombre de caractères spécifiques : %d\n", nb_carac_spec);
    fprintf(file, "Nombre de caractères non spécifiques : %d\n", nb_carac_non_spec);
    fprintf(file, "Nombre de mots                   : %d\n", nb_mots);
    fprintf(file, "Nombre de lignes                 : %d\n", nb_lignes);
    fprintf(file, "Nombre de paragraphes            : %d\n", nb_paragraphes);

    fprintf(file, "\nDictionnaire des mots et leurs fréquences:\n");
    for (int i = 0; i < nb_mots_dico; i++) {
        fprintf(file, "%s: %d\n", tableau_mots[i].mot, tableau_mots[i].frequence);
    }

    printf("\nFichier sauvegarder dans Sauvegarder_fichier.");

    fclose(file);
}


//Function to dislay stats of text(.txt or binary)
void outcome_stat(FILE *file) {
    // Initializing counters
    int nb_mots = 0;
    int nb_lignes = 0;
    int nb_paragraphes = 0;
    int nb_carac = 0;          // All of characters
    int nb_carac_spec = 0;     // specific character (espaces, sauts de ligne, etc.)
    int nb_carac_non_spec = 0; // No-specific character (lettres, chiffres, etc.)
    char a, prev_char = '\0';
    int dans_un_mot = 0;
    int ligne_vide = 1; // Using to detect empty lines

    // check if file is accessible
    fseek(file, 0, SEEK_END);
    long taille = ftell(file);
    printf("Taille du fichier : %ld octets\n", taille);

    // if file is empty, exit immediately
    if (taille == 0) {
        printf("Le fichier est vide.\n");
        return;
    }

    // Remake the cursor to the beginning of the file 
    fseek(file, 0, SEEK_SET);

    // Reading the file character by character
    while ((a = fgetc(file)) != EOF) {
        nb_carac++; // Ever chacacter is counted

        // Detected the character type
        if (isspace(a)) {
            nb_carac_spec++;
            dans_un_mot = 0; // End of only word
        } else {
            nb_carac_non_spec++;
            if (!dans_un_mot && (isalnum(a) || a == '\'')) {
                // counts a word when it start
                dans_un_mot = 1;
                nb_mots++;
            }
        }

        // manage a line
        if (a == '\n') {
            nb_lignes++;
            if (ligne_vide) {
                nb_paragraphes++;
            }
            ligne_vide = 1; // Reset the empty line
        } else if (!isspace(a)) {
            ligne_vide = 0; // Line no empty detected
        }

        // Managing of word with apostrophe
        if (a == '\'' && prev_char != '\0' && isalpha(prev_char)) {
            dans_un_mot = 0; // Seperate after one apostrophe
        }

        prev_char = a;
    }

    // If file don't finish by a line break, add a row
    if (nb_carac > 0 && a != '\n') {
        nb_lignes++;
        if (ligne_vide) {
            nb_paragraphes++;
        }
    }

    // Result of function
    printf("\n------ Résultats de l'analyse ------\n");
    printf("Nombre total de caractères       : %d\n", nb_carac);
    printf("Nombre de caractères spécifiques : %d\n", nb_carac_spec);
    printf("Nombre de caractères non spécifiques : %d\n", nb_carac_non_spec);
    printf("Nombre de mots                   : %d\n", nb_mots);
    printf("Nombre de lignes                 : %d\n", nb_lignes);
    printf("Nombre de paragraphes            : %d\n", nb_paragraphes);

    // Sauvegarder les statistiques dans un fichier texte
    sauvegarder_statistiques("Sauvegarde_fichier", nb_carac, nb_carac_spec, nb_carac_non_spec, nb_mots, nb_lignes, nb_paragraphes, NULL, 0);
}

// frequency of all word.txt
void analyser_frequence_txt(FILE *file , char *word_search) {
    fseek(file, 0, SEEK_END);
    long taille_fichier = ftell(file);
    rewind(file); // Retourner au début du fichier

    // Allouer une chaîne pour le contenu du fichier (+1 pour '\0')
    char *contenu = malloc(taille_fichier + 1);
    if (contenu == NULL) {
        fprintf(stderr, "Erreur : Impossible d'allouer de la mémoire pour le contenu du fichier.\n");
        return;
    }

    // Lire le contenu du fichier
    fread(contenu, 1, taille_fichier, file);
    contenu[taille_fichier] = '\0'; // Ajouter le caractère de fin de chaîne

    // Délimiteurs pour séparer les mots
    const char *delim = " \t\n\r.,;:!?()[]{}\"'";

    // Tableau dynamique pour stocker les mots et leurs fréquences
    MotFrequence *tableau_mots = NULL;
    int nb_mots = 0;

    // Tokeniser le contenu du fichier pour extraire les mots
    char *mot = strtok(contenu, delim);
    while (mot != NULL) {
        // Vérifier si le mot est déjà dans le tableau
        int trouve = 0;
        for (int i = 0; i < nb_mots; i++) {
            if (strcmp(tableau_mots[i].mot, mot) == 0) {
                tableau_mots[i].frequence++;
                trouve = 1;
                break;
            }
        }

        // Si le mot n'est pas trouvé, l'ajouter au tableau
        if (!trouve) {
            MotFrequence *tmp = realloc(tableau_mots, (nb_mots + 1) * sizeof(MotFrequence));
            if (tmp == NULL) {
                fprintf(stderr, "Erreur : Impossible de réallouer de la mémoire.\n");
                free(tableau_mots);
                free(contenu);
                return;
            }

            tableau_mots = tmp;
            tableau_mots[nb_mots].mot = strdup(mot);
            tableau_mots[nb_mots].frequence = 1;
            nb_mots++;
        }

        mot = strtok(NULL, delim);
    }

    // Afficher les mots et leurs fréquences
    printf("Dictionnaire des mots et leurs fréquences :\n");
    for (int i = 0; i < nb_mots; i++) {
        printf("%s: %d\n", tableau_mots[i].mot, tableau_mots[i].frequence);
    }

    // Calculer la fréquence moyenne
    int somme_frequences = 0;
    for (int i = 0; i < nb_mots; i++) {
        somme_frequences += tableau_mots[i].frequence;
    }
    double moyenne_frequence = (double)somme_frequences / nb_mots;

    // Afficher les mots dont la fréquence est supérieure à la moyenne
    printf("\nMots les plus fréquents (fréquence supérieure à la moyenne de %.2f) :\n", moyenne_frequence);
    for (int i = 0; i < nb_mots; i++) {
        if (tableau_mots[i].frequence > moyenne_frequence) {
            printf("%s: %d\n", tableau_mots[i].mot, tableau_mots[i].frequence);
        }
    }

    // Recherche d'un mot spécifique
    printf("\nRecherche d'un mot spécifique, tapez le mot à chercher : ");
    scanf("%s", word_search);

    int trouve = 0;
    for (int i = 0; i < nb_mots; i++) {
        if (strcmp(word_search, tableau_mots[i].mot) == 0) {
            printf("Le mot '%s' apparaît dans le texte %d fois.\n", tableau_mots[i].mot, tableau_mots[i].frequence);
            trouve = 1;
            break;
        }
    }

    // Sauvegarder les statistiques dans un fichier texte
    sauvegarder_statistiques("Sauvegarde_fichier", 0, 0, 0, nb_mots, 0, 0, tableau_mots, nb_mots);

    if (!trouve) {
        printf("Le mot '%s' n'a pas été trouvé dans le texte.\n", word_search);
    }

    // Libérer la mémoire allouée
    for (int i = 0; i < nb_mots; i++) {
        free(tableau_mots[i].mot);
    }
    free(tableau_mots);
    free(contenu);
}

int main(){

    int nb_carac, nb_carac_spec, nb_carac_non_spec, nb_mots, nb_lignes, nb_paragraphes;
    MotFrequence *tableau_mots;
    char nom_file1[100];
    char nom_file2[100];
    char final_file[100];
    char word_search[100];
    char nom_fichier[100];
    

    printf("Bienvenue dans notre analyseur de texte !\n\n");

    setlocale(LC_ALL, "fr_FR.UTF-8");

    char filename[256]; // Définir un tableau pour stocker le nom du fichier

    // Demander le chemin ou le nom du fichier à ouvrir
    printf("Entrez le chemin ou le nom du fichier : ");
    fgets(filename, 256, stdin);

    // Retirer le caractère de nouvelle ligne à la fin de la chaîne
    filename[strcspn(filename, "\n")] = '\0';

    // Vérifier le chemin fourni
    printf("Chemin fourni : %s\n", filename);

    // Ouvrir le fichier en mode lecture
    FILE *HE = fopen(filename, "r");
    if (HE == NULL) {
        perror("Erreur lors de l'ouverture du fichier"); // Afficher un message d'erreur si l'ouverture échoue
        return 1;
    }

    printf("Le fichier %s a été ouvert avec succès.\n", filename);

    // Statis of file (text)
    outcome_stat(HE);
    

    printf("\n");
    printf("**************************************************\n");


    // Analyze's frequency of word
    analyser_frequence_txt(HE , word_search);

    fclose(HE);
    return 0;
}


