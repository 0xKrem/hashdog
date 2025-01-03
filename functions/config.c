#include "../config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char validateCharset(char* key, char* charset) {
    unsigned short len = strlen(key);

    for(int i = 0; i < len; ++i) {
        if (strchr(charset, key[i]) == NULL) {
            return key[i];
        }
    }
    return -1;
}

char* cleanValue(char* value) {
    int len = strlen(value);
    int i;
    char* buff = malloc(sizeof(char) * 100);
    if (buff == NULL) {
        printf("Error: Memory allocation failed\n");
    }

    for (i = 0; i < len; ++i) {
        if (value[i] == '\n' || value[i] == '#') {
            buff[i] = '\0';
            break;
        }
        buff[i] = value[i];
    }
    free(value);

    return buff;
}

char* stringVerify(char* value) {
    int i;

    if (value[0] != '"') {
        return value;
    }

    if (value[strlen(value) - 1] != '"') {
        return NULL;
    }

    for (i = 0; i < strlen(value) - 1; ++i) {
        value[i] = value[i+1];
    }
    value[strlen(value) - 2] = '\0';
    return value;
}

int storeParams(char* key, char* value, char*** params, unsigned int len) {
    for (unsigned int i = 0; i < len; ++i) {
        if (strcmp(params[0][i], key) == 0) {
            return 1;
        }
    }

    if (len > 1) {
        params[0] = allocateParam(params[0], len);
        params[1] = allocateParam(params[1], len);
    }

    params[0][len] = malloc(sizeof(char) * strlen(key));
    params[1][len] = malloc(sizeof(char) * strlen(value));

    strcpy(params[0][len], key);
    strcpy(params[1][len], value);

    return 0;
}

char** allocateParam(char** paramList, unsigned int len) {
    char** newParam = malloc(sizeof(char*) * (len + 1));

    for (unsigned int i = 0; i < len; ++i) {
        newParam[i] = paramList[i];
    }
    free(paramList);

    return newParam;
}

void printParams(char*** params, unsigned int len) {
    for (unsigned int i = 0; i < len; ++i) {
        printf("%s = %s\n", params[0][i], params[1][i]);
    }
}

char* queryConfig(char*** params, unsigned int len, char* key) {
    for (unsigned int i = 0; i < len; ++i) {
        if (strcmp(params[0][i], key) == 0) {
            return params[1][i];
        }
    }
    return NULL;
}
