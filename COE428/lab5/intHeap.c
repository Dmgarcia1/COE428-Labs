/**
 *  The functions in this module implement a Heapdata structure
 *  of integers.
 */


/**
 * heapDelete() removes the biggest integer in the heap and returns it.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"


// Add an element to the heap
void addHeap(int *heap, int value)
{
    int index = heap[0] + 1; // heap[0] stores the size of the heap
    heap[index] = value;     // Add the value to the next available position
    heap[0] = index;         // Update the size of the heap

    // Bubble up to maintain the max-heap property
    int current = index;
    while (current > 1 && heap[current] > heap[current / 2]) {
        // Swap with the parent
        int temp = heap[current];
        heap[current] = heap[current / 2];
        heap[current / 2] = temp;

        current /= 2;
    }
}

// Max-heapify a subtree rooted at index `i`
void max_heapify(int *heap, int i) {
    int size = heap[0]; // heap[0] stores the size of the heap
    int largest = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (left <= size && heap[left] > heap[largest]) {
        largest = left;
    }
    if (right <= size && heap[right] > heap[largest]) {
        largest = right;
    }

    if (largest != i) {
        // Swap and recursively heapify
        int temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;

        max_heapify(heap, largest);
    }
}
void printNode(int *heap, int index) {
    if (index > heap[0]) return;

    printf("<node id=\"%d\">", heap[index]);
    printNode(heap, 2 * index);     // Left child
    printNode(heap, 2 * index + 1); // Right child
    printf("</node>");
}
// Print the heap as XML
void printHeapXML(int *heap) {

    if (heap[0] == 0) {
        printf("<heap></heap>\n"); // Empty heap
        return;
    }

    printf("<node id=\"%d\">", heap[1]); // Root node
    printNode(heap, 2);                 // Left child
    printNode(heap, 3);                 // Right child
    printf("</node>\n");
}

// Delete the root (maximum value) from the heap
int heapDelete(int *heap, int *size) {
    if (*size == 0) {
        fprintf(stderr, "Heap underflow\n");
        return -1;
    }

    int maxValue = heap[1]; // Root value
    heap[1] = heap[*size];  // Move the last element to the root
    (*size)--;              // Decrease the size of the heap
    heap[0] = *size;        // Update the size in heap[0]

    // Restore the max-heap property
    max_heapify(heap, 1);

    return maxValue;
}

/**
 * heapSize() returns the number of items in the Heap.
 *
 */

int heapSize(int*heap)
{
	return heap[0];
}

