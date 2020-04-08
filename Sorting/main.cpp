#include <iostream>
#include <ctime>

using namespace std;

const int NUMBERS_SIZE = 50000;

int genRandInt(int low, int high) {
    return low + rand() % (high - low + 1);
}
void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

void Quicksort_midpoint(int[], int, int);
int Partition(int[], int ,int );
void Quicksort_medianOfThree(int[],int,int);
int partitionMedian(int[],int,int);
int medianof3(int, int, int);
void InsertionSort(int[], int);

int main() {
   int num1[NUMBERS_SIZE];
   int num2[NUMBERS_SIZE];
   int num3[NUMBERS_SIZE];
   fillArrays(num1, num2, num3);
    const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds

    clock_t Start = clock();
    Quicksort_midpoint(num1, 0, NUMBERS_SIZE);
    Quicksort_medianOfThree(num2, 0, NUMBERS_SIZE);
    InsertionSort(num3, NUMBERS_SIZE);
//call sort function here
    clock_t End = clock();
    int elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Elapsed Time: " <<  elapsedTime << endl;
}

void Quicksort_midpoint(int numbers[], int i, int k)
{
    int j = 0;
    //if one or zero elements is already sorted.
    if(i >= k)
    {
        return;
    }
    //partitiion the array. Value j is location os last element in low partition.
    j = Partition(numbers, i, k);
    //recursivley sort/
    Quicksort_midpoint(numbers, i , j);
    Quicksort_midpoint(numbers,j+1, k);
}

int Partition(int numbers[], int i,int k)
{
    //initaialize variables

    //pick middle value as pivot
    int midpoint = (i+k)/2;
    int pivot = numbers[midpoint];

    int l = i;
    int h = k;

    bool done = false;
    while(!done)
    {
        // increment l while numbers[l] < pivot
        while(numbers[l] < pivot)
        {
            ++l;
        }
        //decrement h while pivot < numbers[h]
        while(pivot < numbers[h])
        {
            --h;
        }
        //if zero or one item remaining all nums are partitioned. return h.
        if(l >= h)
        {
            done = true;
        } else
        {
            //swap nums[l] and nums[h], update l and h
            int temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;

            ++l;
            --h;
        }
    }
    return h;
}


void Quicksort_medianOfThree(int numbers[], int i, int k)
{
    int j = 0;
    //if one or zero elements is already sorted.
    if(i >= k)
    {
        return;
    }
    //partitiion the array. Value j is location os last element in low partition.
    j = partitionMedian(numbers, i, k);
    //recursivley sort/
    Quicksort_midpoint(numbers, i , j);
    Quicksort_midpoint(numbers,j+1, k);
}

int partitionMedian(int numbers[],int i, int k)
{
    //initaialize variables

    //pick middle value as pivot
    int midpoint = medianof3(i, k, (i+k)/2);
    int pivot = numbers[midpoint];

    int l = i;
    int h = k;

    bool done = false;
    while(!done)
    {
        // increment l while numbers[l] < pivot
        while(numbers[l] < pivot)
        {
            ++l;
        }
        //decrement h while pivot < numbers[h]
        while(pivot < numbers[h])
        {
            --h;
        }
        //if zero or one item remaining all nums are partitioned. return h.
        if(l >= h)
        {
            done = true;
        } else
        {
            //swap nums[l] and nums[h], update l and h
            int temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;

            ++l;
            --h;
        }
    }
    return h;
}

int medianof3(int a, int b, int c)
{
    if(a < c)
    {
        if(b < a)
        {
            return a;
        } else if (c < b)
        {
            return c;
        } else
        {
            return b;
        }
    } else if (b < c)
    {
        return c;
    } else if (a < b)
    {
        return a;
    } else
    {
        return b;
    }
}

void InsertionSort(int numbers[], int numbersSize)
{
    int i = 0;
    int j = 0;
    int temp = 0; //temp to swap

    for(i = 1; i < numbersSize; ++i)
    {
        j = i;
        //insert numbers[i] into sorted part
        //stopping once numbers[i] in correct postion
        while(j > 0 && numbers[j] < numbers[j-1])
        {
            //swap
            temp = numbers[j];
            numbers[j] = numbers[j-1];
            numbers[j-1] = temp;
            --j;
        }
    }
}