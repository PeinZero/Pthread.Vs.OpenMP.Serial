#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define SIZE 2000
double avg;

void BubbleSort(int *array, int length)
{
	int i, j , temp = 0;
	for ( i = 0 ; i < length ; i++ )
	{
		for (j = i ; j < length ; j++)
		{
			if (array[j] < array[i])
			{
				temp = array[j];
				array[j] = array[i];
				array[i] = temp;
			}
		}
	}
}

void Automated()
{
	int i;
	
	srand (time(NULL));
	int array[SIZE];
	for (i = 0 ; i < SIZE ; i++)
	{
		array[i] = 1 + (rand() % SIZE);
	}
	
//	printf("=========================Unsorted Array:========================= \n\n");
//	for (i = 0 ; i < 2000 ; i++)
//	{
//		printf("array[%d] = %d \n", i, array[i]);
//	}
	
	clock_t start = clock();
	BubbleSort(array, SIZE);
//	
//	printf("Sorted Array: \n\n");
//	for (i = 0 ; i < 2000 ; i++)
//	{
//		printf("array[%d] = %d \n", i, array[i]);
//	}
//	
	
	clock_t stop = clock();
	
	double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
	avg += elapsed;

}
int main()
{
	int i;
	avg = 0;
	
	for (i = 0 ; i < 100 ; i++)
	{
		Automated();
	}
	avg /= 100;
	printf("\n\nSerial: Average Time Taken; BubbleSorts:\n%lf \n\n", avg);
    
}


