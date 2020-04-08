//
// Created by hoang on 3/18/2020.
//

#include "IntSet.h"
IntSet::IntSet()
{
    // Default capacity is 1
    _capacity = 1;
    _table = new setRecord[1];
}

 IntSet::IntSet(int n)
{
    // Set the capacity to n
    _capacity = n;
    _table = new setRecord[n];
}

//IntSet::IntSet(const IntSet &cpy)
//{
////    if(empty())
////    {
////        return;
////    } else
////    {
////    for(unsigned i = cpy; i < cpy.size(); ++i)
////    {
////        insert(cpy)
////    }
////    }
//}


void IntSet::insert(int i)
{
    _comparisons = _comparisonNext;
    double changeCap = _capacity*0.67;
    double nSize = _size+1;
    if(nSize > changeCap)
    {
        _comparisonNext++;
        rehash(_capacity*3);
    }
    int index = (i)%_capacity;
    bool found = true;
    while(found)
    {
        if(_table[index].status != Occupied)
        {
            found = false;
            _comparisonNext++;
        } else if (_table[index].value == i)
        {
            return;
        } else
        {
            index =(index+1)%_capacity;
        }
        _comparisonNext++;
    }
    _table[index].value = i;
    _table[index].status = Occupied;
    _size++;
    return;
//    while(bucketsProbed < _capacity)
//    {
//        if(count(i) == 0)
//        {
//            if(_size > _capacity*0.67)
//            {
//                rehash(_capacity*3);
//            }
//                (_table+bucket)->value = i;
//                _size++;
//            return;
//        }
//        bucket = (bucket+1) % _capacity;
//        ++bucketsProbed;
//    }
}// Insert the element into the set

void IntSet::erase(int i)
{
    _comparisons = _comparisonNext;
    int index = (i)%_capacity;
    bool found = true;
    while(found)
    {
        if(_table[index].status == Occupied)
        {
            if(_table[index].value == i)
            {
                found = false;
            }
            _comparisonNext++;
        } else if (_table[index].status == Empty_since_start)
        {
            return;
        } else
        {
            index = (index+1)%_capacity;
            _comparisonNext++;
        }
        _comparisonNext++;
    }
    _table[index].value = -1;
    _table[index].status = Empty;
    _size--;
//    int bucket = hash(i);
//    int bucketsProbed = 0;
//    while(((_table+bucket)->status != Empty_since_start) && (bucketsProbed < _capacity))
//    {
//        if((count(i) == 1) && (_table+bucket)->value == i)
//        {
//            (_table+bucket)->status = Empty;
//            return;
//        }
//        bucket = (bucket+1) % _capacity;
//        ++bucketsProbed;
//    }
}// Erase the element from the set if it exists

void IntSet::rehash(size_t newSize)
{
    _comparisons = _comparisonNext;
    setRecord* _temp = new setRecord[newSize];
    int changeCap = _capacity;
    int nCap = newSize;
    int val;
    int index;
    for(int i = 0; i< changeCap; ++i)
    {
        if(_table[i].status == Occupied)
        {
            val = _table[i].value;
            index = val%nCap;
            bool Found = true;
            while(Found){
                if(_temp[index].status != Occupied)
                {
                    Found = false;
                    _comparisonNext++;
                }
                else{
                    index = (index+1)%nCap;
                    _comparisonNext++;
                }
                _comparisonNext++;
            }
            _temp[index].value = val;
            _temp[index].status = Occupied;
            _comparisonNext++;
        }
    }
    delete[] _table;
    _capacity = nCap;
    _table = _temp;
}

int IntSet::comparisons()
{
    return _comparisons;
}// Returns the number of camparisons from the last operation performed

size_t IntSet::size() const
{
    return _size;
}

size_t IntSet::capacity() const
{
    // Returns the capacity
    return _capacity;
}

bool IntSet::empty() const
{
    return _size == 0;
}

int IntSet::count(int key) {
    _comparisons = _comparisonNext;
   int bucket = (key%_capacity);
   bool found = true;
   while(found)
   {
       if(_table[bucket].value == key)
       {
           found = false;
       } else if(_table[bucket].status == Empty_since_start)
       {
           _comparisonNext++;
           return 0;
       }
       bucket = (bucket+1)%_capacity;
       _comparisonNext++;
   }
return 1;
// Returns 1 if the key passed in exists in the set and 0 otherwise.
}

//int probe(int) const
//{
//
//}

int IntSet::hash(int i, int) const
{
    return i%_capacity;
}

//int hash_map(int) const
//{
//
//}
//
//int compression_map(int) const
//{
//
//}