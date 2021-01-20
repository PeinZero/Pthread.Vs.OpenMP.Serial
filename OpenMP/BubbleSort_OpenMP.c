#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#define SIZE 2000

long array[SIZE];
double avg;

void BubbleSort(int start, int end){
	long temp = 0;

	for (long i = start ; i < end ; i++ )
	{
		for (long j = start ; j < end ; j++)
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
	long i;

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
//		array[i] = i + (rand() % 10);
	}
	clock_t start = clock();
	
//	printf("==============================Unsorted Array==============================\n\n");
//	for (i = 0 ; i < SIZE ; i++)
//	{
//		printf("array[%ld] ==> %ld \n", i, array[i]);
//	}
	
	#pragma omp parallel
	{
		omp_set_num_threads(4);
		int total_threads = omp_get_num_threads();
		int segment = SIZE/total_threads;
//		printf("--------Total Threads: %d--------\n\n", total_threads);
		#pragma omp for
		for(i = 0; i < total_threads; i++){
			BubbleSort(i*segment, i*segment+segment);
		}
	}

//	printf("==============================Sorted Array==============================\n\n");
//	for (i = 0 ; i < SIZE ; i++){
//		printf("array[%ld] ==> %ld \n", i, array[i]);
//	}
	
	
	clock_t stop = clock();
	
	double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
//    printf("-------------------------\nTime elapsed in ms: %lf\n-------------------------\n", elapsed);
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
	printf("\n\nOPenMP: Average Time Taken; BubbleSorts: %lf \n\n", avg);
	return 0;
}

