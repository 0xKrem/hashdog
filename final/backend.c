#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include "functions.h"

// Fonction pour construire le charset a partir des options
void makeCharset(const char *options, char *charset) {
    strcpy(charset, "");
    if (strchr(options, 'l')) strcat(charset, "abcdefghijklmnopqrstuvwxyz");
    if (strchr(options, 'u')) strcat(charset, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    if (strchr(options, 'd')) strcat(charset, "0123456789");
    if (strchr(options, 's')) strcat(charset, "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");
  
}

// Fonction Bruteforce
int bruteforce(char* argCharset, char* algo, char* maxStr, char* minStr, char* target) {
    char charset[90];
    strcpy(charset, "");
    makeCharset(argCharset, charset);

    int min = strtol(minStr, NULL, 10);
    int max = strtol(maxStr, NULL, 10);

    if (max < min) {
        printf("Erreur : la longueur maximale ne peut pas etre inferieure a la longueur minimale.\n");
        return 1;
    }

    char current[max + 1];
    for(int i = min; i <= max; i++) {
        generateCombinations(charset, current, 0, i, algo, target);
    }
    return 0;
}

// Generation des combinaisons pour bruteforce
void generateCombinations(const char *charset, char *current, int position, int length, char *algo, char* target) {
    if (position == length) {
        current[position] = '\0';
        char hash[65];

        if (strcmp(algo, "sha256") == 0) {
            sha_hash(current, hash);
        } else if (strcmp(algo, "md5") == 0) {
            md5_hash(current, hash);
        }

        if (strcasecmp(hash, target) == 0) {
            printf("Mot de passe trouv� : %s\n", current);
            exit(0);
        }
        return;
    }

    for (int i = 0; charset[i] != '\0'; i++) {
        current[position] = charset[i];
        generateCombinations(charset, current, position + 1, length, algo, target);
    }
}

// Attaque par dictionnaire
int dictAtk(char *dict, char *algo, char *target) {
    FILE *pDict = fopen(dict, "r");
    if (!pDict) {
        printf("Erreur : Impossible d'ouvrir le fichier dictionnaire\n");
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pDict)) {
        buffer[strcspn(buffer, "\n")] = 0;
        char hash[65];

        if (strcmp(algo, "sha256") == 0) {
            sha_hash(buffer, hash);
        } else if (strcmp(algo, "md5") == 0) {
            md5_hash(buffer, hash);
        }

        if (strcasecmp(hash, target) == 0) {
            printf("Mot de passe trouv� : %s\n", buffer);
            fclose(pDict);
            return 0;
        }
    }

    fclose(pDict);
    printf("Aucune correspondance trouv�e\n");
    return 1;
}

// Fonction de hachage SHA-256
int sha_hash(char *str, char *hash) {
    unsigned char buff[SHA256_DIGEST_LENGTH]; 
    SHA256((unsigned char *)str, strlen(str), buff);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash + (i * 2), "%02x", buff[i]);
    }
    hash[SHA256_DIGEST_LENGTH * 2] = '\0';
    return 0;
}

// Fonction de hachage MD5 (d�sactivation de l'avertissement OpenSSL si necessaire)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
int md5_hash(char *str, char *hash) {
    unsigned char buff[MD5_DIGEST_LENGTH]; 
    MD5((unsigned char *)str, strlen(str), buff);
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(hash + (i * 2), "%02x", buff[i]);
    }
    hash[MD5_DIGEST_LENGTH * 2] = '\0';
    return 0;
}
#pragma GCC diagnostic pop

// V�rification de la validit� d'un hash
int checkCharValid(const char *target, const char **algo) {
    size_t len = strlen(target);

    if (len == 32) {
        *algo = "md5";
    } else if (len == 64) {
        *algo = "sha256";
    } else {
        return 0; // Longueur invalide
    }

    for (size_t i = 0; i < len; i++) {
        if (!isxdigit(target[i])) {
            return 0; // Caractere non hexadecimal detecte
        }
    }

    return 1; // Hachage valide
}
