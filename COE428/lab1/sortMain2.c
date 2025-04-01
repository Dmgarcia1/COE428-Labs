#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
 int data[100000]; /* Array of ints to sort */
 int nDataItems; /* number of actual items in the array */ 
 int i; 
 int j=1;
 

 /* Test data */
 nDataItems = 4;
 data[0] = 100;
 data[1] = 35;
 data[2] = 30;
 data[3] = 80;

	if(argc > 1){
		
		for (int j = 0; j<nDataItems; j++){
		data[j] = atoi(argv[j+1]);
		}
	}

	for(int i = 1; i < nDataItems; i++) {
	int key = data[i];
	int j = i-1;
	while(j>=0 && data[j] > key){
			data[j+1] = data[j];
			j = j-1;
			}
 		data[j+1] = key;
 }

 /* Check that the data array is sorted. */
 for(i = 0; i < nDataItems-1; i++) {
 if (data[i] > data[i+1]) {
 fprintf(stderr, "Sort error: data[%d] (= %d)"
 " should be <= data[%d] (= %d)- -aborting\n",
 i, data[i], i+1, data[i+1]);
 exit(1);
 }
 } 

 /* Print sorted array to stdout */
 for(i = 0; i < nDataItems; i++) {
 printf("%d\n", data[i]);
 }

 exit(0);
}
