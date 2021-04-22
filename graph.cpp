/* graph.cpp */

#include "graph.h"
#include "heap.h"

#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>

using namespace std;

// definining variables
int path = 0;
int arr[100];
int solve[100];
int numCount = 0;
VERTEX* ver = NULL;

// color
int getColor(int vertex) {
    return ver[vertex].color;
}

// dijkstra
int dijkstra(int n, pNode* p, int s, int t, int flag) {
    pNode node = NULL;
    ver = (VERTEX*)calloc(n + 1, sizeof(VERTEX));
    for (int i = 1; i <= n; i++) {
        ver[i].color = white;
        ver[i].distance = std::numeric_limits<float>::max();
        ver[i].pi = 0;
        ver[i].position = 0;
    }
    ver[s].color = gray;
    ver[s].distance = 0;
    HEAP* heap = (HEAP*)calloc(1, sizeof(HEAP));
    heap->size = 0;
    heap->capacity = n;
    heap->H = (pElement*)calloc(n + 1, sizeof(pElement));
    heap->H[0] = (pElement)malloc(sizeof(ELEMENT));
    heap->H[0]->key = 1000;
    heap->H[0]->vertex = 1000;
    insert(heap, ver[s].distance, s, ver);
    if (flag == 1) {
        printf("Insert vertex %d, key=%12.4f\n", s, ver[s].distance);
        solve[numCount] = s;
        numCount++;
    }
    while (heap->size != 0) {
        int v = extractMin(heap, ver);
        if (flag == 1) {
            printf("Delete vertex %d, key=%12.4f\n", v, ver[v].distance);
        }
        ver[v].color = black;
        if (v == t) {
            free(heap);
            return 0;
        }
        node = p[v];
        while (node) {
            if (ver[node->v].color == white) {
                ver[node->v].pi = v;
                ver[node->v].distance = ver[v].distance + node->w;
                ver[node->v].color = gray;
                insert(heap, ver[node->v].distance, node->v, ver);
                if (flag == 1) {
                    printf("Insert vertex %d, key=%12.4f\n", node->v, ver[node->v].distance);
                    solve[numCount] = node->v;
                    numCount++;
                }
            }
            else if (ver[node->v].distance > (ver[v].distance + node->w)) {
                float oldDistance;
                oldDistance = ver[node->v].distance;
                ver[node->v].distance = ver[v].distance + node->w;
                ver[node->v].pi = v;
                decreaseKey(heap, ver[node->v].position, ver[node->v].distance, ver);
                if (flag == 1) {
                    printf("Decrease key of vertex %d, from %12.4f to %12.4f\n", node->v, oldDistance, ver[node->v].distance);
                }
            }
            node = node->next;
        }
    }
    free(heap);
    return 1;
}

int solved(int vertex) {
    for (int i = 0; i < numCount; i++) {
        if (solve[i] == vertex) {
            return 1;
        }
    }
    return 0;
    numCount = 0;
}

float getWeight(int vertex) {
    return ver[vertex].distance;
}

void getPath(int t, int s) {
    int pie = ver[t].pi;
    if (t != s) {
        path++;
        arr[path] = t;
        getPath(pie, s);
    }
    else {
        for (int i = path; i > 0; i--) {
            if (i == 1) {
                cout << arr[i] << ">";
            }
            else {
                cout << arr[i] << ", ";
            }
        }
        path = 0;
    }
}

void readGraph(string file) {
    ifstream inFile;
    // defining variables
    int a;
    int b;
    int c;
    int u;
    int v;
    int w;
    pNode node;
    pNode* p;
    inFile.open(file);
    if (inFile.is_open()) {
        inFile >> a >> b;
        //initializeGraph(n);
        p = (pNode*)calloc(a + 1, sizeof(pNode));
        for (int i = 0; i < b; i++) {
            inFile >> c >> u >> v >> w;
            node = (pNode)malloc(sizeof(NODE));
            node->v = v;
            node->w = w;
            node->next = p[u];
            p[u] = node;
        }
        inFile.close();
    }
}

void freeVertex() {
    freeV(ver);
}
