/* main.cpp */

#include "util.h"
#include "heap.h"
#include "graph.h"

#include <iostream>
#include <string>

using namespace std;

string ofile = "";
int main(int argc, char* argv[]) {
    string example = argv[2];
    if (argc > 1) {
        ofile = argv[1];
    }
    
    // defining ints and floats 
    int a;
    int b;
    int t;
    int u;
    int v;
    float w;
    
    char c;
    int present;
    int source, s, d, destination, flag;
    int fail = 0;
    float weight;
    commands command;
    ifstream inFile;
    pNode node = NULL;
    pNode* N = NULL;
    
    // opening file
    inFile.open(ofile);
    if (inFile.is_open()) {
        inFile >> a >> b;
        N = (pNode*)calloc(a + 1, sizeof(pNode));
        for (int i = 0; i < b; i++) {
            inFile >> t >> u >> v >> w;
            node = (pNode)malloc(sizeof(NODE));
            node->v = v;
            node->w = w;
            node->next = N[u];
            N[u] = node;
            
            // if it is undirected
            if (example.compare("undirected") == 0) {
                node = (pNode)malloc(sizeof(NODE));
                node->v = u;
                node->w = w;
                node->next = N[v];
                N[v] = node;
            }
        }
        inFile.close();
    }
    while (1) {
        c = getInput(&source, &s, &d, &destination, &flag);
        command = current(c);
        // switch case
        switch (command) {
            // write
            case WRITE:
                cout << "Query: write path " << s << " " << d << endl;
                if (fail == 1) {
                    cout << "Error: no path computation done" << endl;
                    break;
                }
                // get weight
                weight = getWeight(d);
                if (solved(d) == 0 && present == 0) {
                    cout << "No " << s << "-" << d << " path has been computed." << endl;
                    break;
                }
                if (weight > 100000) {
                    cout << "No " << s << "-" << d << " path exists." << endl;
                    break;
                }
                if (d > a || s != source) {
                    cout << "Error: invalid source destination pair" << endl;
                    break;
                }
                // grey
                if (getColor(d) == gray) {
                    cout << "Path not known to be shortest: <" << s << ", ";
                }
                // black
                if (getColor(d) == black) {
                    cout << "Shortest path: <" << s << ", ";
                }
                
                getPath(d, s); cout << endl;
                printf("The path weight is: %12.4f\n", weight);
                break;
            
            // find
            case FIND:
                fail = 0;
                cout << "Query: find " << source << " " << destination << " " << flag << endl;
                if (source > a || destination == source || flag < 0 || flag > 1) {
                    cout << "Error: invalid find query" << endl;
                    fail = 1;
                    break;
                }
                freeVertex();
                    present = dijkstra(a, N, source, destination, flag);
                break;
            
            // stop
            case STOP:
                cout << "Query: stop" << endl;
                for (int i = 0; i < a; i++) {
                    free(N[i]);
                }
                free(node);
                freeVertex();
                exit(0);
                break;
                
            // none
            case NONE:
                break;
        }
    }
    return 0;
}
