//
// Created by hoang on 3/8/2020.
//

#include "Jug.h"

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA)
{
    this->Ca = Ca;
    this->Cb = Cb;
    this->N = N;
    this->cfA = cfA;
    this->cfB = cfB;
    this->ceA = ceA;
    this->ceB = ceB;
    this->cpAB = cpAB;
    this->cpBA = cpBA;
}

Jug::~Jug()
{
    //imma do nothing :)
}
//solve is used to check input and find the solution if one exists
//returns -1 if invalid inputs. solution set to empty string.
//returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
//returns 1 if solution is found and stores solution steps in solution string.
int Jug::solve(string &solution)
{
    if(Ca < 1 || Cb < 1 || Cb > 1000 || Ca > Cb || N > Cb || N < 0 || cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpBA < 0 || cpAB < 0)
    {
        solution = "";
        return -1;
    }

    Vertex empty(0,0);
    vertecies.push_back(empty);
    process.push(0);
    graph();

    string succ;
    succ = dijkstra();
    if(succ.empty())
    {
        return 0;
    }
    while(!traverse.empty())
    {
        solution += (traverse.top() + '\n');
        traverse.pop();
    }
    solution += succ;
    return 1;
}

void Jug::graph()
{
    while(!process.empty())
    {
        bool found = false;
        unsigned curr = process.top();
        process.pop();

        for(unsigned i = 0; i < visited.size(); ++i)
        {
            if(curr == visited.at(i))
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            visited.push_back(curr);
            process.push(fillA(curr));
            process.push(fillB(curr));
            process.push(emptyA(curr));
            process.push(emptyB(curr));
            process.push(pourAB(curr));
            process.push(pourBA(curr));
        }
    }
}

unsigned Jug::fillA(unsigned curr)
{
    unsigned dex;
    bool found = false;
    Vertex neighbor(Ca, vertecies.at(curr).amt2);

    for(unsigned i = 0; i < vertecies.size(); ++i)
    {
        if(vertecies.at(i).amt1 == neighbor.amt1 && vertecies.at(i).amt2 == neighbor.amt2)
        {
            dex = i;
            found = true;
            break;
        }
    }

    pair<unsigned, string> pair;

    if(found)
    {
        pair = make_pair(dex, "fill A");
    } else
    {
        vertecies.push_back(neighbor);
        pair = make_pair(vertecies.size()-1, "fill A");
    }
    vertecies.at(curr).neighbors.push_back(pair);
    return vertecies.at(curr).neighbors.back().first;
}

unsigned Jug::fillB(unsigned curr)
{
    unsigned dex;
    bool found = false;
    Vertex neighbor(vertecies.at(curr).amt1, Cb);

    for(unsigned i = 0; i < vertecies.size(); ++i)
    {
        if(vertecies.at(i).amt1 == neighbor.amt1 && vertecies.at(i).amt2 == neighbor.amt2)
        {
            dex = i;
            found = true;
            break;
        }
    }

    pair<unsigned, string> pair;

    if(found)
    {
        pair = make_pair(dex, "fill B");
    } else
    {
        vertecies.push_back(neighbor);
        pair = make_pair(vertecies.size()-1, "fill B");
    }
    vertecies.at(curr).neighbors.push_back(pair);
    return vertecies.at(curr).neighbors.back().first;
}

unsigned Jug::emptyA(unsigned curr)
{
    unsigned dex;
    bool found = false;
    Vertex neighbor(0, vertecies.at(curr).amt2);

    for(unsigned i = 0; i < vertecies.size(); ++i)
    {
        if(vertecies.at(i).amt1 == 0 && vertecies.at(i).amt2 == neighbor.amt2)
        {
            dex = i;
            found = true;
            break;
        }
    }

    pair<unsigned, string> pair;

    if(found)
    {
        pair = make_pair(dex, "empty A");
    } else
    {
        vertecies.push_back(neighbor);
        pair = make_pair(vertecies.size()-1, "empty A");
    }
    vertecies.at(curr).neighbors.push_back(pair);
    return vertecies.at(curr).neighbors.back().first;
}

unsigned Jug::emptyB(unsigned curr)
{
    unsigned dex;
    bool found = false;
    Vertex neighbor(vertecies.at(curr).amt1, 0);

    for(unsigned i = 0; i < vertecies.size(); ++i)
    {
        if(vertecies.at(i).amt1 == neighbor.amt1 && vertecies.at(i).amt2 == 0)
        {
            dex = i;
            found = true;
            break;
        }
    }

    pair<unsigned, string> pair;

    if(found)
    {
        pair = make_pair(dex, "empty B");
    } else
    {
        vertecies.push_back(neighbor);
        pair = make_pair(vertecies.size()-1, "empty B");
    }
    vertecies.at(curr).neighbors.push_back(pair);
    return vertecies.at(curr).neighbors.back().first;
}

unsigned Jug::pourAB(unsigned curr)
{
    unsigned dex;
    bool found = false;
    int neighA = vertecies.at(curr).amt1;
    int neighB = vertecies.at(curr).amt2;

    while(neighA > 0 && neighB < Cb)
    {
        neighA--;
        neighB++;
    }

    Vertex neigh(neighA, neighB);

    for(unsigned i = 0; i < vertecies.size(); ++i)
    {
        if(vertecies.at(i).amt1 == neigh.amt1 && vertecies.at(i).amt2 == neigh.amt2)
        {
           dex = i;
           found = true;
           break;
        }
    }

    pair<unsigned, string> pair;

    if(found)
    {
        pair = make_pair(dex, "pour A B");
    } else
    {
        vertecies.push_back(neigh);
        pair = make_pair(vertecies.size()-1, "pour A B");
    }
    vertecies.at(curr).neighbors.push_back(pair);
    return vertecies.at(curr).neighbors.back().first;
}

unsigned Jug::pourBA(unsigned curr)
{
    unsigned dex;
    bool found = false;
    int neighA = vertecies.at(curr).amt1;
    int neighB = vertecies.at(curr).amt2;

    while(neighA < Ca && neighB > 0)
    {
        neighA++;
        neighB--;
    }

    Vertex neigh(neighA, neighB);

    for(unsigned i = 0; i < vertecies.size(); ++i)
    {
        if(vertecies.at(i).amt1 == neigh.amt1 && vertecies.at(i).amt2 == neigh.amt2)
        {
            dex = i;
            found = true;
            break;
        }
    }

    pair<unsigned, string> pair;

    if(found)
    {
        pair = make_pair(dex, "pour B A");
    } else
    {
        vertecies.push_back(neigh);
        pair = make_pair(vertecies.size()-1, "pour B A");
    }
    vertecies.at(curr).neighbors.push_back(pair);
    return vertecies.at(curr).neighbors.back().first;
}

int Jug::getCost(string val) const
{
    if(val == "fill A")
    {
        return cfA;
    } else if (val == "fill B")
    {
        return cfB;
    } else if (val == "empty A")
    {
        return ceA;
    } else if (val == "empty B")
    {
        return ceB;
    } else if (val == "pour A B")
    {
        return cpAB;
    } else
    {
        return cpBA;
    }
}

string Jug::dijkstra()
{
    for(unsigned i = 0; i < vertecies.size(); ++i)
    {
        if(vertecies.at(i).amt1 == 0 && vertecies.at(i).amt2 == N)
        {
            break;
        } else if(i == vertecies.size()-1)
        {
            return "";
        }
    }

    vector<Vertex*> unvisited;
    unsigned dex = 0;
    for(unsigned i = 0; i < vertecies.size(); ++i)
    {
        Vertex* p = &vertecies.at(i);
        unvisited.push_back(p);
    }
    unvisited.at(0)->distance = 0;
    while(!unvisited.empty())
    {
        unsigned min = 0;
        for(unsigned i = 0; i < unvisited.size(); ++i)
        {
            if(unvisited.at(i)->distance < unvisited.at(min)->distance)
            {
                min = i;
            }
        }
        for(unsigned i = 0; i < vertecies.size(); ++i)
        {
            if(vertecies.at(i).amt1 == unvisited.at(min)->amt1 && vertecies.at(i).amt2 == unvisited.at(min)->amt2)
            {
                dex = i;
            }
        }
        for(unsigned i = 0; i < unvisited.at(min)->neighbors.size(); ++i)
        {
            unsigned alt = unvisited.at(min)->distance + getCost(unvisited.at(min)->neighbors.at(i).second);

            if(vertecies.at(unvisited.at(min)->neighbors.at(i).first).distance > alt)
            {
                vertecies.at(unvisited.at(min)->neighbors.at(i).first).distance = alt;
                vertecies.at(unvisited.at(min)->neighbors.at(i).first).prev = dex;
            }
        }
        unvisited.erase(unvisited.begin() + min);
    }
    for(unsigned i = 0; i < vertecies.size(); ++i)
    {
        if(vertecies.at(i).amt1 == 0 && vertecies.at(i).amt2 == N)
        {
            dex = i;
            break;
        }
    }
    unsigned shortest = vertecies.at(dex).distance;
    while(vertecies.at(dex).prev != -1)
    {
        for(unsigned i = 0; i < vertecies.at(vertecies.at(dex).prev).neighbors.size(); ++i)
        {
            if(vertecies.at(vertecies.at(dex).prev).neighbors.at(i).first == dex)
            {
                traverse.push(vertecies.at(vertecies.at(dex).prev).neighbors.at(i).second);
                break;
            }
        }
        dex = vertecies.at(dex).prev;
    }
    stringstream  ss;
    ss << shortest;

    return "success " + ss.str();
}