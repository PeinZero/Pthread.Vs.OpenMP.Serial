#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define SIZE 2000

double avg;

void merge(int *left , int *right , int *arr , int llen , int rlen ){
	int i=0,j=0,k=0;
	while (i< llen && j < rlen){
		if (left[i] < right[j] ){
			arr[k] = left[i];
			i++;
		}
		else{
			arr[k] = right[j];
			j++;
		}
		k++;
	}
	while (i < llen){
		arr[k] = left[i];
		i++;
		k++;
	}
	while (j < rlen){
		arr[k] = right[j];
		j++;
		k++;
	}
}

void mergesort(int *arr , int n){
	
	if (n < 2){
		return;
	}
	else{
		int mid  = n /2;
		int left[mid];
		int right[n - mid];
		
		for (int i = 0 ; i < mid ; i++ ){
			left[i] = arr[i];
		}
		
		for (int i = mid ; i < n ; i++){
			right[i-mid] = arr[i];
		}
			
		mergesort(left , mid);
		mergesort(right, n - mid);
		merge(left,right,arr, mid , n-mid );
		
	}
}

void Automated()
{
	int array[SIZE];
	int i;
	srand (time(NULL));
	for (i = 0 ; i < SIZE ; i++)
	{
		array[i] = 1 + (rand() % SIZE);
	}
	clock_t start = clock();
	
//	printf("=========================Unsorted Array:========================= \n\n");
//	for (i = 0 ; i < 40 ; i++)
//	{
//		printf("array[%d] = %d \n", i, array[i]);
//	}
//	
	mergesort(array, SIZE);
	
	
//	printf("=========================Sorted Array:========================= \n\n");
//	for (i = 0 ; i < SIZE ; i++)
//	{
//		printf("array[%d] = %d \n", i, array[i]);
//		
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
	printf("\n\nSerial: Average Time Taken; MergeSort:\n%lf \n\n", avg);
}


