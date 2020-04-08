#include "HashTable.h"
#include "WordEntry.h"

/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable (int s) {
    hashTable = new list<WordEntry>[s];
    size = s;
}


/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to
*  ensure array index doesn't go out of bounds
*/
int HashTable::computeHash(const string &s) {
    //DOnt do it like this next time.
    unsigned hash = 0;
    for(char i : s)
    {
        hash += i;
    }
    return hash % size;
}


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
void HashTable::put(const string &s, int score) {
    //find the index and adds it to the index of the first element in the array hence the pointer to the first element which is hashTable
    list<WordEntry>* dataIndex = hashTable + computeHash(s);
    if(contains(s))
    {
        list<WordEntry>::iterator it = dataIndex->begin();
        while(true)
        {
            if(it->getWord() == s)
            {
                it->addNewAppearance(score);
                return;
            }
            it++;
        }
    } else
    {
        //set makes a new object and puts it in its spot if its not in there.
        WordEntry data(s, score);
        dataIndex->push_back(data);
    }
}

/* getAverage
*  input: string word
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/

double HashTable::getAverage(const string &s) {
    if(contains(s))
    {
        list<WordEntry>* dataIndex = hashTable + computeHash(s);
        list<WordEntry>::iterator it = dataIndex->begin();
        while(true)
        {
            if(it->getWord() == s)
            {
                return it->getAverage();
            }
            it++;
        }
    }
    return 2.0;
}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(const string &s) {
    // starts at the begining of the array and moves it to where the hash number puts it at.
    list<WordEntry>* dataIndex = hashTable + computeHash(s);
    //if the list at the array index is not empty then go through the list to see is its in the list.
    if(!(dataIndex->empty()))
    {
        //sets to beginning of the list
        list<WordEntry>::iterator it = dataIndex->begin();
        while(it != dataIndex->end())
        {
            if(it->getWord() == s)
            {
                return true;
            }
            it++;
        }
    }
    return false;
}
