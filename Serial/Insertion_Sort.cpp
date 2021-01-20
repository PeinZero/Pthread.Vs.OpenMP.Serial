#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define SIZE 2000

double avg;

void Automated()
{
	int array[SIZE];
	int i;
	srand (time(NULL));
	
	for (i = 0 ; i < SIZE ; i++)
	{
		array[i] = 1 + (rand() % SIZE);
	}
	
//	printf("=========================Unsorted Array:========================= \n\n");
//	for (i = 0 ; i < 40 ; i++)
//	{
//		printf("array[%d] = %d \n", i, array[i]);
//	}
	
	clock_t start = clock();
	
	for (i  = 1 ; i < SIZE ; i++){					
		int temp = array[i];
		int j = i;
		while (j > 0 && array[j-1] > temp){              
			array[j] = array[j-1];						
			j--;
		}
		array[j] = temp;					
	}									
											
//	printf("=========================Sorted Array:========================= \n\n");
//	for (i = 0 ; i < SIZE ; i++)
//	{
//		printf("array[%d] = %d \n", i, array[i]);
//	}
	
	clock_t stop = clock();
	
	double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
//    printf("-------------------------\nTime elapsed in ms: %f\n-------------------------\n", elapsed);
	avg += elapsed;
}
int main(){
	int i;
	avg = 0;
	
	for (i = 0 ; i < 100 ; i++)
	{
		Automated();
	}
	avg /= 100;
	printf("\n\nSerial: Average Time Taken; InsertionSort:\n%lf \n\n", avg);
    
}
