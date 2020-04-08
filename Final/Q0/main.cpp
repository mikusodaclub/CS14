
#include <iostream>
#include <fstream>

using namespace std;

#include "AdjacenceyList.h"

int main() {
    AdjacencyList al("input");

    al.display();
    cout << "Performing BFS..." << endl;
    al.bfs(0);
    for (unsigned i = 0;i < al.vertices();++i) {
        cout << "Path: " << al.path(i) << " at a distance of " << al.distance(i) << endl;
    }
    cout << endl;

    cout << "Performing DFS..." << endl;
    al.dfs(0);
    for (unsigned i = 0;i < al.vertices();++i) {
        cout << "Path: " << al.path(i) << " at a distance of " << al.distance(i) << endl;
    }
    cout << endl;

    return 0;
}