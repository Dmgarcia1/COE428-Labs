#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>

// Heap-related functions
void addHeap(int *heap, int value);
void max_heapify(int *heap, int index);
void printHeapXML(int *heap);
int heapDelete(int *heap, int *size);
int heapSize(int *heap);
void printNode(int *heap, int index);

#endif // HEAP_H