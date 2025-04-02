/**
 *  The functions in this module implement a Heapdata structure
 *  of integers.
 */


/**
 * heapDelete() removes the biggest integer in the heap and returns it.
 *
 */
#include <stdio.h>
extern int pop2();
extern void push2(int);
extern int isEmpty2();

#define MAX_HEAP_SIZE 100

// Define a Max-Heap structure
typedef struct {
    int heap[MAX_HEAP_SIZE];
    int size;
} MaxHeap;

// Initialize the heap
void initHeap(MaxHeap* h) {
    h->size = 0;
}

void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
	
}
void max_heapify(MaxHeap *h, int index){
	int left = 2 * index + 1;  // Left child index
    int right = 2 * index + 2; // Right child index
    int largest = index;

	// If left child is larger than root
    if (left < h->size && h->heap[left] > h->heap[largest]) {
        largest = left;
    }

    // If right child is larger than the largest so far
    if (right < h->size && h->heap[right] > h->heap[largest]) {
        largest = right;
    }

    // If the largest is not root, swap and heapify the affected subtree
    if (largest != index) {
        swap(&h->heap[index], &h->heap[largest]);
        max_heapify(h, largest);
    }
}

int heapDelete(MaxHeap*h)
{
    if (h->size <= 0) {
       printf("Heap is empty!\n");
       return -1; // Return -1 if the heap is empty
    }

    // Get the root element (max element) and place into stack
    int root = h->heap[0];
	pop();
	printf("%d", h->heap[h->size]);

    // Move the last element to the root
    h->heap[0] = h->heap[h->size - 1];
    h->size--;

    // Max-heapify the root element to restore the heap property
    max_heapify(h, 0);

    return root;
}

/**
 *  addHeap(thing2add) adds the "thing2add" to the Heap.
 *
 */
void addHeap(MaxHeap*h, int thing2add)
{
	if (h->size >= MAX_HEAP_SIZE) {
        printf("Heap is full!\n");
        return;
    }
    // Insert the new element at the end of the heap
    int index = h->size++;
    h->heap[index] = thing2add;
	push(thing2add);

    // Bubble up the new element to restore the heap property
    while (index > 0 && h->heap[(index - 1) / 2] < h->heap[index]) {
        swap(&h->heap[index], &h->heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

/**
 * heapSize() returns the number of items in the Heap.
 *
 */
//heap size is 
int heapSize(MaxHeap*h)
{
	return h->size;
}

void printHeapXML(MaxHeap *h){
	
	printf("<heap>\n");

	for(int i=0; i< h->size; i++){
		
		printf("<node id=\"%d\"></node>\n", h->heap[i]);
	}

}


