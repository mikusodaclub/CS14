#ifndef __ADJACENCYLIST_H__
#define __ADJACENCYLIST_H__

#include "Graph.h"

#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include <map>
#include <list>
using namespace std;

class AdjacencyList : public Graph {
private:
    void add_edge(list<int> adj_list[], int source, int sink);
public:
    AdjacencyList(std::string filename);
    int vertices() const;
    int edges() const;
    int distance(int i) const;
    std::string path(int i) const;
    void bfs(int);
    void dfs(int);
    void display() const;

};

#endif // __ADJACENCYLIST_H__