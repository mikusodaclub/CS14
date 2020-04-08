#include <iostream>
#include <vector>
#include <stdexcept>

using std::vector;
using std::cout;
using std::endl;

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index)
{
    if(!vals.empty())
    {
        unsigned minIndex = index;
        for(unsigned i = index; i < vals.size(); i++)
        {
            if(vals.at(i) < vals.at(minIndex))
            {
                minIndex = i;
            }
        }
        return minIndex;
    }
    return -1;
}

template<typename T>
void selection_sort(vector<T> &vals)
{
    for(unsigned i = 0; i < vals.size(); i++)
    {
        unsigned minIndex = min_index(vals, i);
        T minType = vals.at(minIndex);
        T temp = vals.at(i);
        vals.at(i) = minType;
        vals.at(minIndex) = temp;
    }
}

template <typename T>
T getElement(vector<T> vals, int index)
{
    int size = vals.size();
    if(index < 0 || index >= size)
    {
        throw std::out_of_range("Out Of Range");
    }
    else
    {
        return vals.at(index);
    }
}


vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

int main()
{
//    cout << " Testing Min Index" << endl;
//    vector<int> a = {4,3,1,5,8,4,};
//    cout << min_index(a, a.size()) << endl;
//    for(unsigned i = 0; i < a.size(); i++)
//    {
//        cout << a.at(i) << " ";
//    }
//    cout << endl;
//    selection_sort(a);
//    for(unsigned i = 0; i < a.size(); i++)
//    {
//        cout << a.at(i) << " ";
//    }
//    cout << endl;
//Part B
//        srand(time(0));
    vector<char> vals = createVector();
    char curChar;
    int index;
    int numOfRuns = 10;
    while (--numOfRuns >= 0) {
        try{
            cout << "Enter a number: " << endl;
            std::cin >> index;
            curChar = getElement(vals, index);
            cout << "Element located at " << index << ": is " << curChar << endl;
        }
        catch(const std::out_of_range& excpt)
        {
            cout << "out of range exception: " << excpt.what() << endl;
        }
    }

    return 0;
}
