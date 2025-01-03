#include <string.h>
#include <stdio.h>
/*
 * Input : hashing algorithm and target hash
 * Output: Either  or 0
 */
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

/*
 * Input : target string
 * Output: Either invalid character or 0
 */
int checkDigestCharset(char* password) {

	const char *hashCharset = "0123456789abcdefABCDEF";
	const unsigned short lenHashCharset = 22;
	unsigned short lenTarget = strlen(password);

	// loop over the target
	for (unsigned short i = 0; i < lenTarget; ++i) {
		char isValid = 0;

		// loop over the allowed charset
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
