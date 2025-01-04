// attacks
int dictAtk(char dict[255], char algo[7], char target[255]);
int bruteforce(char* argCharset, char* algo, char* maxStr, char* minStr, char* target);

// crypto utilitary
int checkDigest(char* algo, char* password);
int checkDigestCharset(char* password);
int sha_hash(char *str, char *hash);

// 'arguments.c'
int argParser(int argc, char** argv, char args[], char* values[], unsigned short nbFlag);
int argValidate(char args[], char** argValues);
char** argVal(char c, char args[], char ** argValues);
int fallbackToConfig(char args[], char** argValues, char*** params, unsigned int nv);

// 'config.c'
char*** configParser(FILE* config, unsigned int* nv);
void printParams(char*** params, unsigned int len);
void* queryConfig(char*** params, unsigned int len, char* key);

// macros
#define RESET "\x1b[0m"
#define BOLD "\x1b[1m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
