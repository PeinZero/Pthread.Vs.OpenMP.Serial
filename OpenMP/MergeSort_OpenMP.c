#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#define SIZE 2000

int array[SIZE];
double avg;

void merge(int start, int mid, int finish){
	int sizeLeft = mid - start + 1;
	int sizeRight = finish - mid;
	
	int left[sizeLeft];
	int right[sizeRight];
	
	int i = 0 , j = 0 , k = start;
	
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

void MergeSort(int start, int finish)
{
	int mid = start + (finish - start) / 2;
	
	if(start < finish)
	{
		MergeSort(start, mid);
		MergeSort(mid+1, finish);
		merge(start, mid, finish);
	}
}


void* Transition(int threadID)
{
	int start = threadID * 500;
	int finish = start + 499;
	int mid = start + (finish - start) / 2;
	if(start < finish)
	{
		MergeSort(start, mid);
		MergeSort(mid+1, finish);
		merge(start, mid, finish);
	}	
}

void Automated()
{
	int i;

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
	
//	printf("==============================Unsorted Array==============================\n\n");
//	for (i = 0 ; i < SIZE ; i++)
//	{
//		printf("array[%d] ==> %d \n", i, array[i]);
//	}
	
	
	
	#pragma omp parallel
	{
		omp_set_num_threads(4);
		int total_threads = omp_get_num_threads();
//		printf("--------Total Threads: %d--------\n\n", total_threads);
		int segment = SIZE/total_threads;
		#pragma omp for
		for(i = 0; i < total_threads; i++){
			Transition(i);
		}
	}
	
	
 
	printf("===============================Sorted Array==============================\n\n");
	for (i = 0 ; i < SIZE ; i++){
		printf("array[%d] ==> %d \n", i, array[i]);
	}
	
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
	printf("\n\nOPenMP: Average Time Taken; MergeSort: %lf \n\n", avg);    
	return 0;
}
