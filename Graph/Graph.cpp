//
// Created by hoang on 3/8/2020.
//
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include "Graph.h"

using namespace std;

Graph::Graph()
{

}

Graph::Graph(ifstream& fin)
{
    map<string, int> graph;
    int numNode;
    int numEdge;
    string tempVal;

    fin >> numNode >> numEdge;

    for(int i = 0; i < numNode; ++i)
    {
        fin >> tempVal;
        Vertex tempVertex;
        tempVertex.label = tempVal;
        vertices.push_back(tempVertex);
        graph[tempVal] = i;
    }

    string val1;
    string val2;
    int cost;
    int index;

    for(int i = 0; i < numEdge; ++i)
    {
        fin >> val1 >> val2 >> cost;
        index = graph[val1];
        pair<int, int> p(graph[val2], cost);//what is this
        vertices.at(index).neighbors.push_back(p);
    }
}

Graph::~Graph()
{
    while(vertices.size() != 0)
    {
        vertices.pop_back();
    }
}

void Graph::output_graph(const string & filename)
{
    ofstream fout(filename.c_str());
    if(!fout.is_open())
    {
        cout << "Error Opening: " << filename << endl;
        return;
    }
    fout << "digraph G {" << endl;
    for(unsigned i = 0; i < vertices.size(); ++i)
    {
        if(vertices.at(i).distance != INT_MAX)
        {
            fout << vertices.at(i).label << "[Label = \"" << vertices.at(i).label << ", " << vertices.at(i).distance << "\"]" << endl;
        }
        if(!vertices.at(i).neighbors.empty())
        {
            list<pair<int, int>> :: iterator it = vertices.at(i).neighbors.begin();
            while(it != vertices.at(i).neighbors.end())
            {
                if(vertices.at(i).distance != INT_MAX)
                {
                    fout << vertices.at(i).label << " -> " << vertices.at(it->first).label << endl;
                }
                it++;
            }
        }
    }
    fout << "}";
    fout.close();
    string jpgFile = filename.substr(0, filename.size()-4) + ".jpg";
    string command = "dot -tpng " + filename + " -o " + jpgFile;
    system(command.c_str());
}

void Graph::bfs()
{
    map<string, unsigned> graph;
    for(unsigned i = 0; i < vertices.size(); ++i)
    {
        vertices.at(i).color = "WHITE";
        vertices.at(i).distance = INT_MAX;
        vertices.at(i).prev = 0;
        graph[vertices.at(i).label] = i;
    }
    vertices.at(0).color = "GRAY";
    vertices.at(0).distance = 0;
    queue<Vertex> q;

    q.push(vertices.at(0));
    Vertex curr;

    while (!q.empty())
    {
        curr = q.front();
        q.pop();
        list<pair<int,int>> :: iterator it = curr.neighbors.begin();
        while(it != curr.neighbors.end())
        {
            if(vertices.at(it->first).color == "WHITE")
            {
                vertices.at(it->first).color = "GRAY";
                vertices.at(it->first).distance = curr.distance + it->second;
                vertices.at(it->first).prev = &vertices.at(graph[curr.label]);
                q.push(vertices.at(it->first));
            }
            ++it;
        }
    }
}

int Graph::distance(const string &key) const
{
    for(unsigned i = 0; i < vertices.size(); ++i)
    {
        if(vertices.at(i).label == key)
        {
            return vertices.at(i).distance;
        }
    }
    return -1;
}

string Graph::previous(const string &key) const
{
    for(unsigned i = 0; i < vertices.size(); ++i)
    {
        if(vertices.at(i).label == key)
        {
            if(vertices.at(i).prev)
            {
                return vertices.at(i).prev->label;
            }
        }
    }
    return "";
}
//#include "Graph.h"
//#include <unordered_map>
//#include <map>
//#include <vector>
//#include <list>
//#include <queue>
//#include <fstream>
//#include <iostream>
//#include <cstdlib>
//#include <cstdio>
//#include <climits>
//
//using namespace std;
//
//Graph::Graph(){
//
//}
//
//Graph::Graph(ifstream& fin){
//    int nodes = 0;
//    int edges = 0;
//    int weight = 0;
//    string title = "";
//    string neighbor = "";
//
//    fin >> nodes;
//    fin >> edges;
//    fin.ignore();
//
//    for(int i = 0; i < nodes; ++i){
//        Vertex temp;
//        string s = "";
//        getline(fin, s);
//        temp.label = s;
//        vertices.push_back(temp);
//    }
//
//    while(fin >> title){
//        int in_degree = 0;
//        int neighborIndex = 0;
//
//        fin >> neighbor;
//        fin >> weight;
//        for(unsigned int i = 0; i < vertices.size(); ++i){
//            Vertex curr = vertices.at(i);
//            if(title == curr.label){
//                in_degree = i;
//            }
//            if(neighbor == curr.label){
//                neighborIndex = i;
//            }
//        }
//        vertices.at(in_degree).neighbors.push_back(make_pair(neighborIndex, weight));
//    }
//}
//
//Graph::~Graph(){
//    while(vertices.size() != 0){
//        vertices.pop_back();
//    }
//}
//
//void Graph::output_graph(const string& output_file){
//    ofstream fon(output_file);
//
//    if(!(fon.is_open())){
//        cout << "Error opening outfile." << endl;
//        return;
//    }
//
//    fon << "digraph G {" << endl;
//
//    for(unsigned int i = 0; i < vertices.size(); ++i){
//        Vertex curr = vertices.at(i);
//        if(curr.distance != INT_MAX){
//            fon << curr.label << "[label = \"" << curr.label << ", "
//                << curr.distance << "\"]" << endl;
//
//            list<pair<int, int> > ::iterator j;
//            for(j = curr.neighbors.begin(); j != curr.neighbors.end(); ++j){
//                fon << curr.label << " -> " << vertices.at(j->first).label << endl;
//            }
//        }
//    }
//
//    fon << "}";
//    fon.close();
//    string sCommand = "dot -T jpg " + output_file + " -o pic.jpg";
//    system(sCommand.c_str());
//}
//
//void Graph::bfs(){
//    queue<Vertex*> vQueue;
//    vertices.at(0).distance = 0;
//    vQueue.push(&vertices.at(0));
//
//    while(!(vQueue.empty())){
//        Vertex* curr = vQueue.front();
//        vQueue.pop();
//        curr->color = "GRAY";
//
//        list<pair<int, int> > ::iterator i;
//        for(i = curr->neighbors.begin(); i != curr->neighbors.end(); ++i){
//            if(vertices.at(i->first).color == "WHITE"){
//                vertices.at(i->first).color = "GRAY";
//                vertices.at(i->first).prev = curr;
//                vertices.at(i->first).distance = curr->distance + ;
//                vQueue.push(&vertices.at(i->first));
//            }
//        }
//        curr->color = "BLACK";
//    }
//
//}