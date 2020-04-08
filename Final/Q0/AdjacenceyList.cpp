//
// Created by hoang on 3/18/2020.
//

#include "AdjacenceyList.h"

using namespace std;

AdjacencyList::AdjacencyList(std::string filename)
{
    ifstream fin(filename);
    if(!fin)
    {
        cerr << "Input file not found." << endl;
        exit(1);
    }
    int numVertex;
    fin >> numVertex;
    list<int> adjList[numVertex];
    int source, sink;
    while(fin >> source >> sink)
    {
        add_edge(adjList, source, sink);
    }
//    for(int i = 0; i<3; i++) {
//        cout << i << "--->";
//        list<int> :: iterator it;
//        for(it = adjList[i].begin(); it != adjList[i].end(); ++it) {
//            cout << *it << " ";
//        }
//        cout << endl;
//    }
    fin.close();
}

void AdjacencyList::add_edge(list<int> adj_list[], int source, int sink)
{
    adj_list[source].push_back(sink);
}
//
//int vertices() const;
//int edges() const;
//int distance(int i) const;
//std::string path(int i) const;
//void bfs(int);
//void dfs(int);
//void display() const;
