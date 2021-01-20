#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define SIZE 2000
long array[SIZE];
double avg;

void* BubbleSort(void* threadID)
{
	long tiD = (long)threadID;
	long temp = 0;
	long start, finish;
	start = tiD * 500;
	finish = start + 500;
	
	for (long i = start ; i < finish ; i++ )
	{
		for (long j = start ; j < finish ; j++)
		{
			if (array[j] > array[i])
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
	pthread_t threads[4];
	srand (time(NULL));
	long i;
	for (i = 0 ; i < SIZE ; i++)
	{
		if (i < 500)
		{
			array[i] = 1 + (rand() % 500);
		}
		else if (i < 1000)
		{
			array[i] = 501 + (rand() % 500);
		}
		else if (i < 1500)
		{
			array[i] = 1001 + (rand() % 500);
		}
		else if (i < 2000)
		{
			array[i] = 1501 + (rand() % 500);
		}
	}
	clock_t start = clock();
	
//	printf("UnSorted Array: \n");
//	for (long i = 0 ; i < SIZE ; i++)
//	{
//		printf("array[%ld] ==> %ld \n", i, array[i]);
//	}
	
	
	for (long i = 0 ; i < 4 ; i++)
	{
		pthread_create( &threads[i] , NULL , BubbleSort , (void*)i );
	}
	
	for (long i = 0 ; i < 4 ; i++)
	{
		pthread_join( threads[i] , NULL );
	}
	
//	printf("Sorted Array: \n");
//	for (long i = 0 ; i < SIZE ; i++)
//	{
//		printf("array[%ld] ==> %ld \n", i, array[i]);
//	}
	
	clock_t stop = clock();
	
	double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
//    printf("-------------------------\nTime elapsed in ms: %f\n-------------------------\n", elapsed);
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
	printf("\n\nPthread: Average Time Taken; BubbleSort: %lf \n\n", avg);    
	return 0;
    
}

