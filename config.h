#ifndef CONFIG_H
#define CONFIG_H

char validateCharset(char* key, char* charset);
char* cleanValue(char* value);
int storeParams(char* key, char* value, char*** params, unsigned int len);
char** allocateParam(char** paramList, unsigned int len);
void printParams(char*** params, unsigned int len);
char* stringVerify(char* value);
char* queryConfig(char*** params, unsigned int len, char* key);

#endif
