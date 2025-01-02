#ifndef BACKEND_H
#define BACKEND_H

int bruteforce(char* argCharset, char* algo, char* maxStr, char* minStr, char* target);
int checkDigest(char* algo, char* password);
int checkDigestCharset(char* password);
int generateCombinations(const char *charset, char *current, int position, int length, char *algo, char* target);
int sha_hash(char *str, char *hash);
int dictAtk(char dict[255], char algo[7], char target[255]);

#endif
