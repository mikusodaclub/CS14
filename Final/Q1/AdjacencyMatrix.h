#ifndef __ADJACENCYMATRIX_H__
#define __ADJACENCYMATRIX_H__

#include "Graph.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stack>
#include <climits>
#include <queue>

using namespace std;

class AdjacencyMatrix : public Graph {
private:
    vector<vector<int>> V;
    bool emptty() const;
    void visitVector(vector<string>&, int);
public:
    AdjacencyMatrix(std::string filename);

    int vertices() const;
    int edges() const;
    int distance(int i) const;
    std::string path(int i) const;
    void bfs(int);
    void dfs(int);
    void display() const;

};

#endif // __ADJACENCYMATRIX_H__
