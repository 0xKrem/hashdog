#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../functions.h"

/* Input : main function argument-count and argument-value
 *		   array of strings (type char**) and max number of flags
 *
 * Output : int 0
 */
int argParser(int argc, char** argv, char args[], char* values[], unsigned short nbFlag) {
	unsigned short flagCount = 0;
	unsigned short valIndex;
	char* used = malloc(sizeof(char) * nbFlag + 1);

	if (used == NULL) {
		printf("Error: Memory allocation failed\n");
		exit(1);
	}

	// retrieve the valid flags
	for (unsigned short i = 1; i < argc - 1; ++i) {

		if (argv[i][0] == '-' &&		// must start with "-"
			strlen(argv[i]) == 2  &&		// must be of length 2 
			strchr(args, argv[i][1]) &&		// 2nd char must be valid flag 
			strchr(used, argv[i][1]) == NULL &&		// 2nd char must not be used already
			argv[i + 1][0] != '-' ) {		// next arg must not be a flag

			// add flag to 'used'
			strcat(used, &argv[i][1]);

			// the position of the letter inside the 'args' string
			valIndex = strchr(args, argv[i][1]) - args;

			// allocate the size of the argument (argv[i + 1])
			values[valIndex] = (char*) malloc(strlen(argv[i + 1]) + 1);
			if (values[valIndex] == NULL) {
				printf("Error : Memory allocation failed\n");
			}

			// copy the value
			strcpy(values[valIndex], argv[i + 1]);

			flagCount++;

			// break if all flags are already used
			if (flagCount == nbFlag) { 
				break;
			}
		}
	}

	return 0;
}

char** argVal(char c, char args[], char** argValues) {
	int len = strlen(args);

	for (unsigned int i = 0; i < len; ++i) {
		if (args[i] == c) {
			return &argValues[i];
		}
	}
	return NULL;
}

int argValidate(char args[], char** argValues) {

	// check digest length
	if (checkDigest(*argVal('a', args, argValues), *argVal('p', args, argValues)) >= 0) {
		printf("Error : Invalid hash length\n");
		exit(1);
	}

	// check digest charset
	char ret = checkDigestCharset(*argVal('p', args, argValues));
	if (ret != 0 ){
		printf("Error: Invalid character '%c' in hash\n", ret);
		exit(1);
	}

	// validating hashing algorithm 
	char* validAlgos[] = {"md5", "sha256"};
	char isValid = 0;

	for (int i = 0; i < 2; ++i) {
		if (strcmp(*argVal('a', args, argValues), validAlgos[i]) == 0) {
			isValid = 1;
		}
	}
	if (isValid == 0) {
		printf("Error: Unsupported hashing algorithm '%s'\n", *argVal('a', args, argValues));
		exit(1);
	}

	// validating salt file
	if (strcmp(*argVal('s', args, argValues), "") != 0) {
		FILE* salt = fopen(*argVal('s', args, argValues), "r");
		if (salt == NULL) {
			printf("Error: Can not open file '%s'\n", *argVal('s', args, argValues));
			exit(1);

		}
	}

	return 0;
}

int fallbackToConfig(char args[], char** argValues, char*** params, unsigned int nv) {

	// falling back on config-file values
	if (*argVal('a', args, argValues) == NULL) {
		*argVal('a', args, argValues) = queryConfig(params, nv, "attack.algorithm");
	}
	if (*argVal('d', args, argValues) == NULL) {
		*argVal('d', args, argValues) = queryConfig(params, nv, "path.wordlist");
	}
	if (*argVal('m', args, argValues) == NULL) {
		*argVal('m', args, argValues) = queryConfig(params, nv, "attack.mode");
	}
	if (*argVal('c', args, argValues) == NULL) {
		*argVal('c', args, argValues) = queryConfig(params, nv, "bruteforce.charset");
	}
	if (*argVal('s', args, argValues) == NULL) {
		*argVal('s', args, argValues) = queryConfig(params, nv, "attack.salt");
	}
	if (*argVal('t', args, argValues) == NULL) {
		*argVal('t', args, argValues) = queryConfig(params, nv, "bruteforce.timeout");
	}	
	if (*argVal('x', args, argValues) == NULL) {
		*argVal('x', args, argValues) = queryConfig(params, nv, "bruteforce.length.max");
	}
	if (*argVal('n', args, argValues) == NULL) {
		*argVal('n', args, argValues) = queryConfig(params, nv, "bruteforce.length.min");
	}

	return 0;
}

