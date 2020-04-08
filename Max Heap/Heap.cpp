//
// Created by hoang on 1/30/2020.
//

#include "Heap.h"

/*Initializes an empty heap.*/
Heap::Heap()
{
    numItems = 0;
}

/*Inserts a PrintJob to the heap without
violating max-heap properties.*/
void Heap::enqueue ( PrintJob* job)
{
    if(numItems < MAX_HEAP_SIZE)
    {
        arr[numItems] = job;
        int i = numItems;
        numItems++;

        while(i != 0 && (arr[getParent(i)]->getPriority() < arr[i]->getPriority()))
        {
            swap(getParent(i), i);
            i = getParent(i);
        }
    }
}

/*Removes the node with highest priority from the heap.
Follow the algorithm on priority-queue slides. */
void Heap::dequeue ( )
{
    if(numItems > 0)
    {
        PrintJob* job = arr[0];
        arr[0] = arr[numItems - 1];
        numItems--;
        delete (job);
        trickleDown(0);
    }
}

/*Returns the node with highest priority.*/
PrintJob* Heap::highest ( )
{
    if(numItems > 0)
    {
        return arr[0];
    } else
    {
        return nullptr;
    }
}

/*Prints the PrintJob with highest priority in the following format:
Priority: priority, Job Number: jobNum, Number of Pages: numPages
(Add a new line at the end.)*/
void Heap::print ( )
{
    if(numItems > 0)
    {
       cout << "Priority: " << arr[0]->getPriority() << ", Job Number: " << arr[0]->getJobNumber() << ", Number of Pages: " << arr[0]->getPages() << endl;
    }
    else
    {
        cout << "Jon Queue empty" << endl;
    }
}

/*This function is called by dequeue function
    to move the new root down the heap to the
    appropriare location.*/
void Heap::trickleDown(int i)
{
    int left = getLeft(i);
    int right = getRight(i);
    int top = i;

    if(left < numItems && arr[left]->getPriority() > arr[top]->getPriority())
    {
        top = left;
    }
    if(right < numItems && arr[right]->getPriority() > arr[top]->getPriority())
    {
        top = right;
    }
    if(i != top)
    {
        swap(i, top);
        trickleDown(top);
    }
}

int Heap::getParent(int i)
{
    return (i-1)/2;
}
int Heap::getLeft(int i)
{
    return 2*i+1;
}
int Heap::getRight(int i)
{
    return 2*i+2;
}
void Heap::swap(int i, int j)
{
    PrintJob* temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

//You can include additional private helper functions here