#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char validateCharset(char* key, char* charset);
char* cleanValue(char* value);
int storeParams(char* key, char* value, char*** params, unsigned int len);
char** allocateParam(char** paramList, unsigned int len);
void printParams(char*** params, unsigned int len);
char* stringVerify(char* value);

/*
 * Input : config file as a stream
 * Output : pointer to 2 arrays of string representing key/value pair
*/
char*** configParser(FILE* config, unsigned int* nv) {

	unsigned int n = 0; // current file line
	*nv = 0; // valid line counter
	unsigned short len = 200;
	int index;

	char line[len]; // current line
	char ret; // return value
	char alpha[] = "azertyuiopqsdfghjklmwxcvbn";
	char nums[] = "0123456789";

	char* key = malloc(sizeof(char) * 100); //store the current key
	char* value = malloc(sizeof(char) * 100); //store the current value
	char* pDelimiter; // store the ptr to the '='
	
	char* keyChars = malloc(sizeof(char) * 150); //store the valid key charset
	char* valueChars = malloc(sizeof(char) * 150); //store the valid value charset

	char*** params = malloc(sizeof(char**) * 2); // this is what we return
	char** paramKeys = malloc(sizeof(char*)); // this contains all the valid keys
	char** paramValues = malloc(sizeof(char*)); // this contains all the valid values

	if (params == NULL) {
		printf("Error: Memory allocation failed\n");
	}
	params[0] = paramKeys;
	params[1] = paramValues;

	// creating key charset
	strcpy(keyChars, alpha);
	strcat(keyChars, ".\n");

	// creating value charset
	strcpy(valueChars, alpha);
	strcat(valueChars, nums);
	strcat(valueChars, ":");
	strcat(valueChars, "\\./\"");

	while(fgets(line, len, config)) {
		n++;
		strcpy(key, "");
		strcpy(value, "");
		
		// detect comments and empty lines
		if (line[0] == '#' || line[0] == '\n') {
			continue;
		}

		// checking for a '='
		pDelimiter = strchr(line, '=');
		if (pDelimiter == NULL) {
			printf("[Config Error](line %u) No key=value pair found in config\n", n);
			return NULL;
		}
		// index of the '='
		index = pDelimiter - line;
		strncpy(key, line, index);

		// adding null-byte to end the string
		key[index] = '\0';

		// copy value
		strcpy(value, pDelimiter + 1);

		// removing comments and \n
		value = cleanValue(value);

		// string verif
		value = stringVerify(value);
		if (value == NULL) {
			printf("[Config Error](line %u) : Malformed string\n", n);
		}

		// validate key charset
		ret = validateCharset(key, keyChars);
		if (ret != -1) {
			printf("[Config Error](line %u) : Invalid char '%c' found in key '%s'\n", n, ret, key);
			continue;
		}

		// validate value charset
		ret = validateCharset(value, valueChars);
		if (ret != -1) {
			printf("[Config Error](line %u) : Invalid char '%c' found in value '%s'\n", n, ret, value);
			continue;
		}

		if (storeParams(key, value, params, *nv) == 1) {
			printf("[Config Error](line %u) : Duplicate key found, skipping\n", n);
			continue;
		} else {
			(*nv)++;
		}

	}
	// printParams(params, *nv); // debug

	free(key);
	free(keyChars);
	free(value);
	free(valueChars);
	return params;
}

/*
 * Input : key as a string, authorized charset
 * Output : invalid char or -1 if all good
 */
char validateCharset(char* key, char* charset) {
	unsigned short len;
	len = strlen(key);

	for(int i = 0; i < len; ++i) {
		if (strchr(charset, key[i]) == NULL) {
			return key[i];
		}
	}
	return -1;
}

/* Purpose : remove '\n' and comments
 * Input : value as a string
 * Output : value as a string (cleaned)
 */
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

/* Purpose : this functions edits the value for later use
 * 			 strings and integers are appended a specific prefix
 * 			 this allows for dynamic type conversion at runtime
 */
char* stringVerify(char* value) {
	int i;

	// allocating the value + type encoding
	char* strPrefix = "s:";
	char* intPrefix = "i:";
	char* boolPrefix = "b:";
	char* newValue = malloc(sizeof(char) * (strlen(value) + 2));

	if (newValue == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}

	// encoding strings
	if (value[0] == '"') {
		strcpy(newValue, strPrefix);

		// if strings doesnt end with quote
		if (value[strlen(value) - 1] != '"') {
			free(newValue);
			return NULL;
		}

		// remove quotes
		for (i = 0; i < strlen(value) - 1; ++i) {
			value[i] = value[i+1];
		}

		value[strlen(value) - 2] = '\0'; // delete ending quote
		strcat(newValue, value);
		return newValue;
	}

	// encoding integers
	if (value[0] >= '0' && value[0] <= '9') {
		strcpy(newValue, intPrefix);
		strcat(newValue, value);
		return newValue;
	}

	// booleans
	if (strcmp(value, "true") == 0 || strcmp(value, "false") == 0) {
		strcpy(newValue, boolPrefix);
		strcat(newValue, value);
		return newValue;
	}
	return NULL;

}

/* Purpose : dynamically building 2 arrays of strings to store key/value pair
 * Input : key, value, params ptr that stores 2 arrays of string, len that represent the number of parameters
 * Output : 1 if duplicate was found, 0 if all good
 */
int storeParams(char* key, char* value, char*** params, unsigned int len) {

	for (unsigned int i = 0; i < len; ++i) {

		//params[0][i] = all the keys
		if (strcmp(params[0][i], key) == 0) {

			//duplicate found
			return 1;
		}
	}

	if (len > 1) {
		// increase by 1 each array of strings
		params[0] = allocateParam(params[0], len);
		params[1] = allocateParam(params[1], len);
	}

	// allocate the size of the string
	params[0][len] = malloc(sizeof(char) * strlen(key));
	params[1][len] = malloc(sizeof(char) * strlen(value));

	// write the string to the array
	strcpy(params[0][len], key);
	strcpy(params[1][len], value);

	return 0;
}

char** allocateParam(char** paramList, unsigned int len) {
	char** newParam = malloc(sizeof(char*) * (len + 1));

	// copying into new param
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
