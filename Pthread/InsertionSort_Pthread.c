#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define SIZE 2000
long array[SIZE];
double avg;

void* InsertionSort(void* threadID)
{
	long temp;
	long i;
	long tiD = (long)threadID;
	long start, finish;
	start = tiD * 500;
	finish = start + 500;
	
	
	for ( i  = start ; i < finish ; i++){					
		temp = array[i];
		long j = i;
		while (j > 0 && array[j-1] > temp){              
			array[j] = array[j-1];
			j--;
		}
		array[j] = temp;
	}
}
void Automated()
{
	long i;
	pthread_t threads[4];
	srand (time(NULL));
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
		pthread_create( &threads[i] , NULL , InsertionSort , (void*)i );
	}
	
	for (long i = 0 ; i < 4 ; i++)
	{
		pthread_join( threads[i] , NULL );
	}
	
	printf("Sorted Array: \n");
	for (long i = 0 ; i < SIZE ; i++)
	{
		printf("array[%ld] ==> %ld \n", i, array[i]);
	}
	
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
	printf("\n\nPthread: Average Time Taken; InsertionSort: %lf \n\n", avg);
	return 0;
}







