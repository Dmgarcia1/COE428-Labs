#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
extern int pop2();
extern void push2(int);
extern int isEmpty2();

int main(int argc, char * argv[])
{
  int value;
  int heap[100];
  int index=0;

  initHeap(&heap);
  while (scanf("%d\n", &value) != EOF) {
    fprintf(stderr, "READING INPUT: %d\n", value);
  	
	addHeap(&heap, value);
	index++;
	
	}

	//build heap
	for(int i=index/2-1; i>=0; i++){
	max_heapify(heap,i);
	}
	
    printHeapXML(&heap);

	print();

	heapDelete(&heap);
	
	
  exit(0);
}	
