/* heap.cpp */

#include "heap.h"

#include <iostream>
#include <limits>

using namespace std;
pElement element;

// parent
int parent(int i) {
    return (i / 2);
}
// left
int left(int i) {
    return (2 * i);
}
// right
int right(int i) {
    return ((2 * i) + 1);
}

int decreaseKey(HEAP* heap, int position, float newKey, pVertex ver) {
    pElement temp;
    if (position < 1 || newKey > heap->H[position]->key || position > heap->size ) {
        return 1;
    }
    heap->H[position]->key = newKey;
    while ((position > 1) && (heap->H[parent(position)]->key >= heap->H[position]->key)) {
        temp = heap->H[position];
        heap->H[position] = heap->H[parent(position)];
        heap->H[parent(position)] = temp;
        ver[heap->H[position]->vertex].position = parent(position);
        ver[heap->H[parent(position)]->vertex].position = position;
        position = parent(position);
    }
    return 0;
}

int extractMin(HEAP* heap, pVertex V) {
    int minimum;
    if (heap->size < 1) {
        cout << "Error: heap empty" << endl;
        return 0;
    }
    else {
        minimum = heap->H[1]->vertex;
        heap->H[1]->vertex = heap->H[heap->size]->vertex;
        heap->H[1]->key = heap->H[heap->size]->key;
        V[heap->H[1]->vertex].position = V[heap->H[heap->size]->vertex].position;
        heap->size--;
        minHeapify(heap, 1, V);
        return minimum;
    }
}

int getPi(int vertex, VERTEX* V) {
    return V[vertex].pi;
}

void insert(HEAP* heap, float key, int value, pVertex V) {
    element = (pElement)malloc(sizeof(ELEMENT));
    element->vertex = value;
    element->key = key;
    heap->size++;
    heap->H[heap->size] = element;
    int i = heap->size - 1;
    decreaseKey(heap, i + 1, key, V);
}

void minHeapify(HEAP* heap, int i, pVertex V) {
    int l = left(i);
    int r = right(i);
    int smallest, temp;
    if ((l <= heap->size) && (heap->H[l]->key < heap->H[i]->key)) {
        smallest = l;
    }
    else {
        smallest = i;
    }
    if ((r <= heap->size) && (heap->H[r]->key < heap->H[smallest]->key)) {
        smallest = r;
    }
    if (smallest != i) {
        temp = heap->H[i]->key;
        heap->H[i]->key = heap->H[smallest]->key;
        heap->H[smallest]->key = temp;
        V[heap->H[i]->vertex].position = smallest;
        V[heap->H[smallest]->vertex].position = i;
        minHeapify(heap, smallest, V);
    }
}

void goingUp(HEAP* heap, int pos) {
}

void printHeap(HEAP* H) {
    cout << "capacity=" << H->capacity << ", size=" << H->size << endl;
    for (int i = 1; i <= H->size; i++) {
        if (i == (H->size)) {
            cout << "key[" << H->H[i]->vertex << "]= " << H->H[i]->key << endl;
        }
        else {
            cout << "key[" << H->H[i]->vertex << "]= " << H->H[i]->key << ", " << endl;
        }
    }
}

VERTEX* getGraph(VERTEX* V) {
    return V;
}

void freeV(VERTEX* V) {
    free(V);
}

void freeE() {
    free(element);
}
