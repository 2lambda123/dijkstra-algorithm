/* graph.h */
#ifndef graph_h
#define graph_h

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// struct for node
typedef struct Node {
    int v;
    float w;
    Node* next;
} NODE;
typedef NODE* pNode;

// struct for vertex
typedef struct Vert {
    int pi;
    int color;
    float distance;
} VERT;
typedef VERT* pVert;

int dijkstra(int n, pNode* p, int s, int t, int flag);
int getColor(int vertex);
int solved(int vertex);

float getWeight(int vertex);

void getPath(int t, int s);
void readGraph(string file);
void freeVertex();

#endif /* graph_h */

