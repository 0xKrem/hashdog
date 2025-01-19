#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void makeCharset(const char *options, char *charset);
int checkCharValid(const char *target, const char **algo);  // Correction ici
int bruteforce(char* argCharset, char* algo, char* maxStr, char* minStr, char* target);
void generateCombinations(const char *charset, char *current, int position, int length, char *algo, char* target);
int dictAtk(char *dict, char *algo, char *target);
int sha_hash(char *str, char *hash);
int md5_hash(char *str, char *hash);

#endif // FUNCTIONS_H
