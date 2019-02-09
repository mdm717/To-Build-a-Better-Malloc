#include "mymalloc.h"
static char myblock[5000];

boolean empty = TRUE;

//Initalizes memory array to 0
void initialize(char* array){
	int i;
	for(i=0; i<5000; i++)
	{
		array[i] = '0';
	}
	*(short*)array = 4998;
	empty = FALSE;
}

//Stores metadata for malloc
void* details(size_t size, char* index){
	unsigned short total = *(unsigned short*) index;
	if(total > size){
		unsigned short* left = (unsigned short*) (index+2+size*sizeof(char));
		*left = total - (size+2);
	}
	*(unsigned short*)index = size+1;
	return (void*) index;
}

//Checks memory array to make sure there is enough free space to accomodate the requested amount of memory
boolean checkSpace(char* myblock, size_t size){
	unsigned short i = 0;
	unsigned short metaData = 0;
	while(i<5000)
	{
		metaData = *(unsigned short*)myblock;
		if((metaData%2)==0 && (metaData>=size))
		{
			return TRUE;
		}
		else
		{
			unsigned short increment = metaData - (metaData%2) + 2;
			myblock += increment*sizeof(char);
			i += increment*sizeof(char);
		}
	}
	return FALSE;
}

//Returns pointer to adequate block of memory
char *findSpace(char* myBlock, unsigned short size){
	unsigned short i = 0;
	unsigned short metaData = 0;
	while(i<5000){
		metaData = *(unsigned short*)myBlock;
		if((metaData%2==0) && (metaData>=size)){
			return myBlock;
		}
		else{
			unsigned short inc = metaData - (metaData%2) + 2;
			myBlock = myBlock + inc*sizeof(char);
			i = i + inc;
		}
	}
	return NULL;
}

//Goes through memory array to find adjacent blocks of free memory, combining them into one block			
void defrag(char* myBlock){
	unsigned short i = 0;
	unsigned short* home = (unsigned short*)myBlock;
	unsigned short* probe = (unsigned short*)myBlock;
	while(i<5000)
	{
		while(i<5000 && *home%2 == 1)
		{
			i += 2+*home;
			home = home + (1+*home)/2;
			probe = probe + (1+*probe)/2;
		}
		probe += (2+*probe)/2;
		while(i<5000 && (*probe)%2 == 0)
		{
			*home += 2+*probe;
			i = i+2+*probe;
			probe = probe + (2+*probe)/2;
		}
		if(*(probe)%2 == 1)
		{
			home = probe;
		}
	}
}

//Checks to make sure the size of memory requested is less than the size of the memory array
size_t validateInput(size_t size){
	if(size <= 0 || size > 4998)
	{
		printf("Invalid request, cannot allocate\n");
		return 0;
	}
	return (size + size%2);
}

//Allocates requested amount of memory for the user
void* mymalloc(size_t size, char* fname, int line){ 
	if(empty)
	{
		initialize(myblock);
	}
	size = validateInput(size);
	char* Meta;
	if(size = 0)
	{
		return 0;
	}
	if(checkSpace(myblock, size))
	{
		Meta = findSpace(myblock, size);
	}
	else
	{
		defrag(myblock);
		Meta = findSpace(myblock, size);
	}
	if(Meta == NULL)
	{
		printf("Not enough memory - allocation denied\n");
		return 0;
	}
	void* test = details(size, Meta);
	return test+2;	
}

//Uses pointer to memory to match amount of allocated space requested to be freed and frees it,
//returning true if successful. Returns false if unacceptable amount is requested.
boolean myfree(void * target, char* file, int line){
	if(empty)
	{
		initialize(myblock);
	}
	void* tarFree = target - 2;
	void* ptr = (void*)myblock;
	unsigned short dist = 0;
	while(tarFree != ptr && dist < 5000)
	{
		dist = dist + 2 + *(unsigned short*)ptr - (*(unsigned short*)ptr)%2;
		ptr = ptr + *(unsigned short*)ptr + 2 - (*(unsigned short*)ptr)%2;
	}
	if(tarFree == ptr)
	{
		if((*(unsigned short*)ptr)%2 == 1)
		{
			*(unsigned short*)ptr -=  1;
			return TRUE;
		}
	}
	printf("Error: invalid address, cannot be freed\n");
	return FALSE;	
}
	
	
	
