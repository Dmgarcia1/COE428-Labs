#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "heap.h"
#include "intStack.h"

int main(int argc, char *argv[])
{
    int value;
    int heap[101]; // Heap array (heap[0] stores the size, so we need 101 elements for 100 values)

    // Initialize the heap
    heap[0] = 0; // Set the initial size of the heap to 0

    // Read input values and add them to the heap
    printf("Enter integers to add to the heap (-1 to stop):\n");
    while (scanf("%d", &value) != EOF) {
	
		if(value == -1){
			printf("input -1, stopping input\n");
			break; // Stop reading if -1 is encountered
			
		}
        printf("READING INPUT: %d\n", value);
        addHeap(heap, value);
    }
    // Print the heap size
    printf("\nHeap size: %d\n", heapSize(heap));

    // Print the heap in XML format
    printf("\nHeap in XML format:\n");
    printHeapXML(heap);

	printf("DEBUG: Clearing stack...\n");

    // Initialize the stack
    while (!isEmpty2()) {
        pop2(); // Clear the stack if it contains any leftover data
    }

    // Delete items from the heap, print them, and push them onto the stack
    printf("\nDeleted items (sorted descending):\n");
    while (heapSize(heap) > 0) {
        int deletedValue = heapDelete(heap, &heap[0]); // Delete the root of the heap
        printf("%d\n", deletedValue);
        push2(deletedValue); // Push the deleted value onto the stack
    }

    // Pop items from the stack and print them
    printf("\nPopped items (sorted ascending):\n");
    while (!isEmpty2()) {
        printf("%d\n", pop2());
    }

    return 0;
}