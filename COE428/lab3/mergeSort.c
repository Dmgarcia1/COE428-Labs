#include "mySort.h"

void merge(int arr[],int a1, int b1, int a2, int b2)
{
	int temp[MAX_SIZE_N_TO_SORT]; 
	int a,b,c;
	a = a1;
	b = a2;
	c = 0;
	
	while(a <= b1 && b <= b2) 
	{
		if(myCompare(arr[a], arr[b]) < 0){
			temp[c++] = arr[a++];
		}
		else{
			temp[c++] = arr[b++];		
    }
	}	
	while(a <= b1){
		myCopy(&arr[a++], &temp[c++]);
	}
	while(b <= b2){
		myCopy(&arr[b++], &temp[c++]);
	}
		
	for(a = a1, c = 0; a <= b2; a++, c++){
	mySwap(&arr[a], &temp[c]);
	}
}

void mySort(int array[], unsigned int first, unsigned int last)
{ 
    if(first < last)
    {
       int mid = (first + last)/2;
       mySort(array, first, mid);
	   mySort(array, mid+1, last);
	   merge(array, first, mid, mid + 1, last);
    }
}



