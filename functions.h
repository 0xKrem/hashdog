// attacks
int dictAtk(char dict[255], char algo[7], char target[255]);
int bruteforce(char* charset, char* algo, unsigned int maxLength, unsigned int minLength);

// crypto utilitary
int checkDigest(char* algo, char* password);
int checkDigestCharset(char* password);
int sha_hash(char *str, char *hash);

// parsing
int argParser(int argc, char** argv, char args[], char* values[], unsigned short nbFlag);
char*** configParser(FILE* config, unsigned int* nv);

// parsing utilitaries
void printParams(char*** params, unsigned int len);
char* queryConfig(char*** params, unsigned int len, char* key);
char** argVal(char c, char args[], char ** argValues);

// macros
#define RESET "\x1b[0m"
#define BOLD "\x1b[1m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
