#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define SIZE 2000
double avg;
long array[SIZE];

void merge(long start, long mid, long finish){
	long sizeLeft = mid - start + 1;
	long sizeRight = finish - mid;
	
	long left[sizeLeft];
	long right[sizeRight];
	
	long i = 0 , j = 0 , k = start;
	
	for (int i = 0 ; i < sizeLeft ; i++ ){
		left[i] = array[i + start];
	}
		
	for (int i = 0 ; i < sizeRight ; i++){
		right[i] = array[i + mid + 1];
	}
	
	while (i < sizeLeft && j < sizeRight)
	{
		if( left[i] <= right[j] )
			array[k++] = left[i++];
		else
			array[k++] = right[j++];
		
	}
	
	while (i < sizeLeft)
	{
		array[k++] = left[i++];
	}
	
	while (j < sizeRight)
	{
		array[k++] = right[j++];
	}
}

void MergeSort(long start, long finish)
{
	long mid = start + (finish - start) / 2;
	
	if(start < finish)
	{
		MergeSort(start, mid);
		MergeSort(mid+1, finish);
		merge(start, mid, finish);
	}
}


void* Transition(void* threadID)
{
	long start = (long)threadID * 500;
	long finish = start + 499;
	long mid = start + (finish - start) / 2;
	if(start < finish)
	{
		MergeSort(start, mid);
		MergeSort(mid+1, finish);
		merge(start, mid, finish);
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
		pthread_create( &threads[i] , NULL , Transition , (void*)i );
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
	printf("\n\nPthread: Average Time Taken; MegreSort: %lf \n\n", avg);    
	return 0;
}







