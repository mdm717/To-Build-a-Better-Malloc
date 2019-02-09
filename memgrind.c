#include "mymalloc.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

static char* myblock[5000];

float average(float arr[]){
	int i;
	float sum = 0;
	for(i=0; i<100; i++)
	{
		sum = sum + arr[i];
	}
	sum = sum/100;
	return sum;
}

float grindA(){
	struct timeval start, end;
	float time[100]; 
	int i, j;
	char *ptr = NULL;
	for(i=0; i<100; i++)
	{
		gettimeofday(&start, NULL);
		for(j=0; j<150; j++)
		{
			ptr = (char*)malloc(1 * sizeof(char));
			free(ptr);
		}	
		gettimeofday(&end, NULL);
		time[i] = (end.tv_sec*1000000+end.tv_usec)-(start.tv_sec*1000000+start.tv_usec); 	
	}
	float avg = average(time);
	return avg;	
}

float grindB(){
	struct timeval start, end;
	float time[100];
	int i, j;
	for(i=0; i<100; i++)
	{
		gettimeofday(&start, NULL);
		for(j=0; j<150; j++)
		{
			myblock[j] = (char*)malloc(1*sizeof(char));
		}
		for(j=0; j<150; j++)
		{
			free(myblock[j]);
		}
		gettimeofday(&end, NULL);
		time[i] = (end.tv_sec*1000000+end.tv_usec)-(start.tv_sec*1000000+start.tv_usec);
	} 
	float avg = average(time);
	return avg;
}

float grindC(){
	struct timeval start, end;
	int i;
        float time[100];
        char* myblock[5000];
        for(i=0; i<100; i++)
        {
		gettimeofday(&start, NULL);
                int timesMalloced = 0;
                int freeindex = 0;
                int index = 0;
                int numbers = 0;
                while(timesMalloced != 150)
                {
                        int num = rand()%2;
                        if(num == 0)
                        {
                                myblock[index] = (char*)malloc(1 * sizeof(char));
                                index++;
                                numbers++;
                                timesMalloced++;
                        }
                        if(num == 1)
                        {
                                if(numbers !=  0)
                                {
                                        free(myblock[freeindex]);
                                        freeindex++;
                                        numbers--;
                                }
                        }
                }
                while(numbers != 0)
                {
                        free(myblock[freeindex]);
                        freeindex++;
                        numbers--;
                }
		gettimeofday(&end, NULL);
		time[i] = (end.tv_sec*1000000+end.tv_usec)-(start.tv_sec*1000000+start.tv_usec);
	}
	float avg = average(time);
	return avg;
}

float grindD(){
	struct timeval start, end;
	int i;
	float time[100];
        for(i=0; i<100; i++)
        {
		gettimeofday(&start, NULL);
                int timesMalloced = 0;
                int numbers = 0;
                int index = 0;
                int freeIndex = 0;
                while(timesMalloced != 150)
                {
                        int num = rand()%2;
                        int allocSize = rand()%(64+1-1)+1;
                        if(num == 0)
                        {
                                myblock[index] = (char*)malloc(allocSize * sizeof(char));
                                timesMalloced++;
                                index++;
                                numbers++;
                        }
                        if(num == 1)
                        {
                                if(numbers != 0)
                                {
                                        free(myblock[freeIndex]);
                                        freeIndex++;
                                        numbers--;
                                }
                        }
                }
                while(numbers != 0)
                {
                        free(myblock[freeIndex]);
                        freeIndex++;
                        numbers--;
                }
		gettimeofday(&end, NULL);
		time[i] = (end.tv_sec*1000000+end.tv_usec)-(start.tv_sec*1000000+start.tv_usec);
	}
	float avg = average(time);
	return avg;
}

float grindE(){
	struct timeval start, end;
	int i, j;
        char *ptr = NULL;
	float time[100];
        for(i=0; i<100; i++)
        {
		gettimeofday(&start, NULL);
                for(j=0; j<4998; j++)
                {
                        ptr = (char*)malloc(1*sizeof(char));
                        free(ptr);
                }
		gettimeofday(&end, NULL);
		time[i] = (end.tv_sec*1000000+end.tv_usec)-(start.tv_sec*1000000+start.tv_usec);
        }
	float avg = average(time);
	return avg;
}

float grindF(){
	struct timeval start, end;
	int i, j, k;
	char *temp[5000];
	float time[100];
	for(i=0; i<100; i++)
	{
		gettimeofday(&start, NULL);
		int times = rand()%(5+1-1)+1;
		int index = 0;
		int freeIndex = 0;
		int timesMalloced = 0;
		int nums = 0;
		while(timesMalloced != 150)
		{
			int random = rand()%2;
			if(random == 0)
			{
				temp[index] = (char*)malloc(times * sizeof(char));
				index++;
				nums++;
				timesMalloced++;
			}
			else if(random == 1)
			{
				if(nums != 0)
				{
					free(temp[freeIndex]);
					freeIndex++;
					nums--;
				}
			}
		}
		while(nums != 0)
		{
			free(temp[freeIndex]);
			freeIndex++;
			nums--;
		}
		gettimeofday(&end, NULL);
                time[i] = (end.tv_sec*1000000+end.tv_usec)-(start.tv_sec*1000000+start.tv_usec);
	}				
	float avg = average(time);
	return avg;
}

int main(int argc, char* argv[]){
        float TimeOfA = grindA();
        printf("Average Memory Grind Time of A: %f\n", TimeOfA);
        float TimeOfB = grindB();
        printf("Average Memory Grind Time of B: %f\n", TimeOfB);
        float TimeOfC = grindC();
        printf("Average Memory Grind Time of C: %f\n", TimeOfC);
        float TimeOfD = grindD();
        printf("Average Memory Grind Time of D: %f\n", TimeOfD);
  	float TimeOfE = grindE();
	printf("Average Memory Grind Time of E: %f\n", TimeOfE);
	float TimeOfF = grindF();
	printf("Average Memory Grind Time of F: %f\n", TimeOfF);
	return 0;
} 
