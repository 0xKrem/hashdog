#include <stdio.h>
#include <openssl/sha.h>
#include <string.h>
#include <stdlib.h>

int sha_hash(char *str, char *hash) {
    unsigned char buff[SHA256_DIGEST_LENGTH]; 

    SHA256((unsigned char *)str, strlen(str), buff);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash + (i * 2), "%02x", buff[i]);
    }
    hash[SHA256_DIGEST_LENGTH * 2] = '\0';
    return 0;
}

int dictAtk(char dict[255], char algo[7], char target[255]){
	unsigned short bSize = 255;
	char buffer[bSize];
	unsigned int count = 0;
	char* hash;
	// setting a ptr to the data
	FILE *pDict = fopen(dict, "r");

	// check local arguments
	if (pDict == NULL) {
		printf("Error: wordlist '%s' doesn't exist\n", dict);
		exit(1);
	}

	while (fgets(buffer, bSize, pDict) != NULL) {
		//remove '\n' that prevent matching
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

