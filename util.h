//
//  util.h
//  Project3
//
//  Created by Nguyen Truong Duy Khang on 4/15/21.
//

#ifndef util_h
#define util_h
#include <vector>
#include "graph.h"
#include "heap.h"
int dijkstra_SP(Graph G,HEAP* heap,int s, int t);
vector<int> findRoute(Graph G, int s, int t);
void printPathWeight(Graph G, int t);
vector<string>split_string(string input);
void printPath(vector<int> route);
#endif /* util_h */
