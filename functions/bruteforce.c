#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../functions.h"

char* makeCharset(char* charset, char* sumchar);
void generateCombinations(const char *charset, char *current, int position, int length, char *algo, char* target);

int bruteforce(char* argCharset, char* algo, char* maxStr, char* minStr, char* target) {
	// char* pass = malloc(sizeof(char) * minLength);

	char* charset = malloc(sizeof(char) * 90);

	strcpy(charset, "\0");
	makeCharset(argCharset, charset);

	printf("charset = %s\n", charset);
	
	// convert min and max to int
	char* end; // return value for strol()
	int min, max;

	// string to long
	min = strtol(minStr, &end, 10);
	if (*end != '\0') { // if strtol() fails
		printf("Error: bruteforce.length.min : cannot convert to integer\n");
		exit(1);
	}

	max = strtol(maxStr, &end, 10);
	if (*end != '\0') {
		printf("Error: bruteforce.length.max : cannot convert to integer\n");
		exit(1);
	}

	char current[max + 1];
	printf("From %d charaters to %d characters\n",min, max); // debug
	// verifying mix and max
	if (max < min) {
		printf("Error: bruteforce.length.max cannot be greater than bruteforce.length.min\n");
		return 1;
	}


	for(int i = min; i <= max; i ++) {
		generateCombinations(charset, current, 0, i, algo, target);
	}
	
	return 0;
}

char* makeCharset(char* charset, char* sumchar) {
	// charsets
	char* special = "¹~#{[|`\\^@]}$£%*µ?,.;/:§!<>";
	char* lower = "azertyuiopqsdfghjklmwxcvbn";
	char* upper = "AZERTYUIOPQSDFGHJKLMWXCVBN";
	char* num = "0123456789";

	char* used = malloc(sizeof(char) * 4);
	int len = strlen(charset);

	for (int i = 0; i < len; ++i) {
		switch(charset[i]) {
			case 's':
				// if 's' is not already used
				if (strchr(used, 's') == NULL) {

					// add special to the charset
					strcat(sumchar, special);

					// add 's' to used
					strcat(used, "s");
				}
				break;
			case 'l':
				// if 's' is not already used
				if (strchr(used, 'l') == NULL) {

					// add lower to the charset
					strcat(sumchar, lower);

					// add 's' to used
					strcat(used, "l");
				}
				break;
			case 'u':
				// if 's' is not already used
				if (strchr(used, 'u') == NULL) {

					// add upper to the charset
					strcat(sumchar, upper);

					// add 's' to used
					strcat(used, "u");
				}
				break;
			case 'n':
				// if 's' is not already used
				if (strchr(used, 'n') == NULL) {

					// add num to the charset
					strcat(sumchar, num);

					// add 's' to used
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


void generateCombinations(const char *charset, char *current, int position, int length, char *algo, char* target) {

    // stop when word is long enough
    if (position == length) {
		char* hash = malloc(sizeof(char) * 64);
        current[position] = '\0';  // properly end string

        if (strcmp(algo, "sha256") == 0) {
			sha_hash(current, hash);
		}

		if (strcasecmp(hash, target) == 0) {

			printf("Found password : %s\n", current);

			free(hash);
			exit(0);
		} else {
			printf("[Try] %s = %s\n", current, hash);
		}
		free(hash);

		return;
	}

	// Iterate through all characters in the charset
	for (int i = 0; charset[i] != '\0'; i++) {
		current[position] = charset[i];  // Set the current character
		generateCombinations(charset, current, position + 1, length, algo, target);  // Recursively generate the next character
	}
}

