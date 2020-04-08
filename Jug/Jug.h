//
// Created by hoang on 3/8/2020.
//

#ifndef JUG_JUG_H
#define JUG_JUG_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

class Vertex
{
    friend class Jug;
public:
    Vertex(int amtA,int amtB)
    {
        prev = -1;
        distance = INT_MAX;
        unvisited = false;
        amt1 = amtA;
        amt2 = amtB;
    }
private:
    int amt1;
    int amt2;
    int prev;
    unsigned distance;
    bool unvisited;
    vector<pair<unsigned, string >> neighbors;
};

class Jug {
public:
    Jug(int,int,int,int,int,int,int,int,int);
    ~Jug();
    //solve is used to check input and find the solution if one exists
    //returns -1 if invalid inputs. solution set to empty string.
    //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
    //returns 1 if solution is found and stores solution steps in solution string.
    int solve(string &solution);
private:
    //anything else you need
    int Ca;
    int Cb;
    int N;
    int cfA;
    int cfB;
    int ceA;
    int ceB;
    int cpAB;
    int cpBA;
    stack<unsigned> process;
    vector<unsigned> visited;
    vector<Vertex> vertecies;
    stack<string> traverse;
    void graph();
    unsigned fillA(unsigned);
    unsigned fillB(unsigned);
    unsigned emptyA(unsigned);
    unsigned emptyB(unsigned);
    unsigned pourAB(unsigned);
    unsigned pourBA(unsigned);
    int getCost(string) const;
    string dijkstra();
};

#endif //JUG_JUG_H
