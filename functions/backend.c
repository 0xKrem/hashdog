#include "../backend.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

// Définition de la fonction makeCharset
char* makeCharset(char* charset, char* sumchar) {
    char* special = "¹~#{[|`\\^@]}$£%*µ?,.;/:§!<>";
    char* lower = "azertyuiopqsdfghjklmwxcvbn";
    char* upper = "AZERTYUIOPQSDFGHJKLMWXCVBN";
    char* num = "0123456789";

    char* used = malloc(sizeof(char) * 4);
    int len = strlen(charset);

    for (int i = 0; i < len; ++i) {
        switch(charset[i]) {
            case 's':
                if (strchr(used, 's') == NULL) {
                    strcat(sumchar, special);
                    strcat(used, "s");
                }
                break;
            case 'l':
                if (strchr(used, 'l') == NULL) {
                    strcat(sumchar, lower);
                    strcat(used, "l");
                }
                break;
            case 'u':
                if (strchr(used, 'u') == NULL) {
                    strcat(sumchar, upper);
                    strcat(used, "u");
                }
                break;
            case 'n':
                if (strchr(used, 'n') == NULL) {
                    strcat(sumchar, num);
                    strcat(used, "n");
                }
                break;
            default:
                printf("Error: Invalid charset character '%c'\n", charset[i]);
                exit(1);
        }
    }
    return sumchar;
}

// Implémentation des autres fonctions fournies
int bruteforce(char* argCharset, char* algo, char* maxStr, char* minStr, char* target) {
    char* charset = malloc(sizeof(char) * 90);
    strcpy(charset, "\0");
    makeCharset(argCharset, charset);

    printf("charset = %s\n", charset);
    
    char* end;
    int min, max;

    min = strtol(minStr, &end, 10);
    if (*end != '\0') {
        printf("Error: bruteforce.length.min : cannot convert to integer\n");
        exit(1);
    }

    max = strtol(maxStr, &end, 10);
    if (*end != '\0') {
        printf("Error: bruteforce.length.max : cannot convert to integer\n");
        exit(1);
    }

    char current[max + 1];
    printf("From %d characters to %d characters\n", min, max);
    if (max < min) {
        printf("Error: bruteforce.length.max cannot be greater than bruteforce.length.min\n");
        return 1;
    }

    for(int i = min; i <= max; i++) {
        if (generateCombinations(charset, current, 0, i, algo, target)) {
            break;
        }
    }

    return 0;
}

int checkDigest(char* algo, char* password) {
    unsigned short lenTarget = strlen(password);

    if (strcasecmp(algo, "sha256") == 0 && lenTarget != 64) {
        return lenTarget;
    }
    if (strcasecmp(algo, "md5") == 0 && lenTarget != 32) {
        return lenTarget;
    }

    return -1;
}

int checkDigestCharset(char* password) {
    const char *hashCharset = "0123456789abcdefABCDEF";
    const unsigned short lenHashCharset = 22;
    unsigned short lenTarget = strlen(password);

    for (unsigned short i = 0; i < lenTarget; ++i) {
        char isValid = 0;

        for (unsigned short j = 0; j < lenHashCharset; ++j) {
            if (password[i] == hashCharset[j]) {
                isValid = 1;
            }
        }
        if (isValid == 0) {
            return password[i];
        }
    }
    return 0;
}

int generateCombinations(const char *charset, char *current, int position, int length, char *algo, char* target) {
    if (position == length) {
        char* hash = malloc(sizeof(char) * 64);
        current[position] = '\0';

        if (strcmp(algo, "sha256") == 0) {
            sha_hash(current, hash);
        }

        if (strcasecmp(hash, target) == 0) {
            printf("Found password : %s\n", current);
            free(hash);
            return 1; // Arrêter la génération
        } else {
            printf("[Try] %s = %s\n", current, hash);
        }
        free(hash);

        return 0;
    }

    for (int i = 0; charset[i] != '\0'; i++) {
        current[position] = charset[i];
        if (generateCombinations(charset, current, position + 1, length, algo, target)) {
            return 1; // Arrêter la génération
        }
    }
    return 0;
}

int sha_hash(char *str, char *hash) {
    unsigned char buff[SHA256_DIGEST_LENGTH];

    SHA256((unsigned char *)str, strlen(str), buff);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash + (i * 2), "%02x", buff[i]);
    }
    hash[SHA256_DIGEST_LENGTH * 2] = '\0';
    return 0;
}

int dictAtk(char dict[255], char algo[7], char target[255]) {
    unsigned short bSize = 255;
    char buffer[bSize];
    unsigned int count = 0;
    char* hash;
    FILE *pDict = fopen(dict, "r");

    if (pDict == NULL) {
        printf("Error: wordlist '%s' doesn't exist\n", dict);
        exit(1);
    }

    while (fgets(buffer, bSize, pDict) != NULL) {
        buffer[strlen(buffer) - 1] = '\0';
        count++;

        if (strcasecmp(algo, "sha256") == 0) {
            hash = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
            if (hash == NULL) {
                printf("Error: Memory allocation failed\n");
            }
            sha_hash(buffer, hash);

        } else if (strcasecmp(algo, "md5") == 0) {
            printf("Implemented soon\n");
            return 1;
        }
        if (strcasecmp(hash, target) == 0) {
            printf("Tried : %u words\n", count);
            printf("Found password : %s\n", buffer);
            free(hash);
            return 0;
        } else {
            printf("[Try] %s = %s\n", buffer, hash);
        }
        free(hash);
    }
    printf("Tried : %u words\n", count);
    printf("Found 0 match\n");
    fclose(pDict);
    return 0;
}
