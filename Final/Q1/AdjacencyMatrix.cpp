//
// Created by hoang on 3/18/2020.
//
#include <vector>
#include "AdjacencyMatrix.h"
bool AdjacencyMatrix::emptty() const
{
    return  V.size() == 0;
}
void AdjacencyMatrix::visitVector(vector<string>& color, int x)
{
    color.at(x) = "GREY";//O(1)
    for(int i = 0; i < V.at(x).size(); ++i)//O(n) due to num of verticies
    {
        if(color.at(i) == "WHITE" && V.at(x).at(i) == 1)//O(1)
        {
            _previous.at(i) = x;//O(1)
            color.at(i) = "GREY";//O(1)
            _distances.at(i) = _distances.at(x) +1;//O(1)
            visitVector(color, i);//O(n)
        }
    }
    color.at(x) = "BLACK";
}

AdjacencyMatrix::AdjacencyMatrix(std::string filename)
{
    ifstream fin(filename);
    if(!fin)
    {
        cerr << "Input file not found." << endl;
        exit(1);
    }
    int numVertex;
    fin >> numVertex;
    V = vector<vector<int>>(numVertex, vector<int>(numVertex, 0));
    _previous = vector<int>(numVertex, INT_MAX);
    _distances = vector<int>(numVertex, INT_MAX);
    int source, sink;
    while(fin >> source >> sink)
    {
        V.at(source).at(sink) = 1;
    }

}

int AdjacencyMatrix::vertices() const
{
   if(!emptty())
   {
       return V.size();
   }
   return 0;
}

int AdjacencyMatrix::edges() const
{
    if(!emptty())
    {
        int con = 0;
        for(unsigned i = 0; i < V.size(); ++i)
        {
            for(unsigned j = 0; j < V.size(); ++j)
            {
                if(V.at(i).at(j) != 0)
                {
                    ++con;
                }
            }
        }
        return con;
    }
    return 0;
}

int AdjacencyMatrix::distance(int i) const
{
    return _distances.at(i);
}

std::string AdjacencyMatrix::path(int i) const
{
    stack<int> Vertexes;
    int curr = i;
    while(curr != -1)
    {
        Vertexes.push(curr);
        curr = _previous.at(curr);
    }
    string path = "{";
    while(!Vertexes.empty())
    {
        int num = Vertexes.top();
        Vertexes.pop();
        path += to_string(num);
        bool notlastone = true;
        if(Vertexes.empty())
        {
            notlastone = false;
        }
        if(notlastone)
        {
            path += "->";
        }
    }
    path += "}";
    return path;

}
//RUNTIME : O(n^2)
//COMPLEXITY O(n)
void AdjacencyMatrix::bfs(int start)
{
    queue<int> que;//O(1)
    vector<string> colors = vector<string>(vertices(), "WHITE");//O(n)
    _distances = vector<int>(vertices(), INT_MAX);//O(n)
    _previous = vector<int>(vertices(), -1);//O(n)
    _distances.at(start) = 0;//O(1)
    _previous.at(start) = -1;//O(1)
    colors.at(start) = "GREY";//O(1)
    que.push(start);//O(1)

    while(!que.empty())//O(n)
    {
        int curr = que.front();//O(1)
        que.pop();//O(1)
        for(unsigned i = 0; i < V.at(curr).size(); ++i)//O(n)
        {
            if(colors.at(i) == "WHITE" && V.at(curr).at(i) == 1)//O(1)
            {
                _distances.at(i) = _distances.at(curr) + 1;//O(1)
                _previous.at(i) = curr;//O(1)
                colors.at(i) = "GREY";//O(1)
                que.push(i);//O(1)
            }
        }
        colors.at(curr) = "BLACK";//O(1)
    }
}

//RUNTIME : O(n^2)
//COMPLEXITY O(n)
void AdjacencyMatrix::dfs(int start)
{
    vector<string> colors = vector<string>(vertices(), "WHITE");//O(n)
    _distances = vector<int>(vertices(), INT_MAX);//O(n)
    _previous = vector<int>(vertices(), -1);//O(n)

    colors.at(start) = "GREY";//O(1)
    _previous.at(start) = -1;//O(1)
    _distances.at(start) = 0;//O(1)
    visitVector(colors, start);//O(n^2)
}

void AdjacencyMatrix::display() const
{
    bool first = true;
    cout << "{";
    for(unsigned i = 0; i < V.size(); ++i)
    {
        for(unsigned j = 0; j < V.size(); ++j)
        {
            if(V.at(i).at(j) == 1)
            {
                if(!first)
                {
                    cout << ", ";
                }
                cout << "(" << i << "->" << j << ")";
                first = false;
                cout << endl;
            }
        }
    }
    cout << "}" << endl;
}

