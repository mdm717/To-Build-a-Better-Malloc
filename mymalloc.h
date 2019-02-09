#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define malloc(x) mymalloc(x, __FILE__, __LINE__) 
#define free(x) myfree(x, __FILE__, __LINE__)

typedef enum {FALSE, TRUE} boolean;
void initialize(char* myblock);
boolean checkSpace(char* myblock, size_t size);
boolean myfree(void* ptr, char* file, int line);
void* details(size_t size, char* index);
char* findSpace(char* myBlock, unsigned short size);
void defrag(char* myBlock);
size_t validateInput(size_t size);
void* mymalloc(size_t size, char* fname, int line);
