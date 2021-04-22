/* heap.h */

#ifndef heap_h
#define heap_h

#include <limits>
#include <iostream>

typedef struct Tag_Element {
    int vertex;
    float key;
} ELEMENT;
typedef ELEMENT* pElement;

typedef struct Tag_Heap {
    int size;
    int capacity;
    pElement* H;
} HEAP;

enum color { white, gray, black };
typedef struct Vertex {
    int pi;
    int color;
    int position;
    float distance;
} VERTEX;
typedef VERTEX* pVertex;

int parent(int i), left(int i), right(int i);

int decreaseKey(HEAP* heap, int position, float newKey, pVertex ver);
int extractMin(HEAP* heap, pVertex V);
int getPi(int vertex, VERTEX* V);

void insert(HEAP* heap, float key, int value, pVertex ver);
void minHeapify(HEAP* heap, int i, pVertex ver);
void goingUp(HEAP* heap, int position);
void printHeap(HEAP* H);

VERTEX* getGraph(VERTEX* ver);
float getWeight(int vertex);
void freeV(VERTEX* ver);
void freeE();

#endif /* heap_h */
