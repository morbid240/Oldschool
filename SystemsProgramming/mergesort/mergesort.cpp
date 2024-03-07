
#include <iostream>
#include<fstream>

using namespace std;

void display(int arr[], int SIZE)
{
    for (int i = 0; i < SIZE; i++)
        cout << arr[i] << endl;
    cout << endl;
}

void merge(int arr[], int const l, int const m, int const r)
{
    //init subarrays
    int const sizeleft = m -l + 1;
    int const sizeright = r - m;
    int leftindex = 0, rightindex = 0, k = l;

    //create subarrays then copy elements
    int *leftarr= new int[sizeleft];
    int *rightarr= new int[sizeright];

    for (int i = 0; i < sizeleft; i++)
        leftarr[i] = arr[l + i];
    for (int j = 0; j < sizeright; j++)
        rightarr[j] = arr[m + 1 + j];

    //compare left and right subarrays
    while (leftindex < sizeleft && rightindex < sizeright)
    {
        if (leftarr[leftindex] <= rightarr[rightindex])
            arr[k++] = leftarr[leftindex++];
        else 
            arr[k++] = rightarr[rightindex++];
    }
    //copy left subarray
    while (leftindex < sizeleft)
        arr[k++] = leftarr[leftindex++];
    //copy right subarray
    while (rightindex < sizeright)
        arr[k++] = rightarr[rightindex++];
    //delete temp
    delete[] leftarr;
    delete[] rightarr;
}
void mergesort(int arr[], int const l, int const r)
{
    if (l < r)
    {
        int mid = (l + r) / 2;
        mergesort(arr, l, mid); //left subarray
        mergesort(arr, mid+1, r);//right subarray
        merge(arr, l, mid, r);
    }
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        cout << "Please include input filename and output filename in param list.\n";
        cout << "Example:\n";
        cout << "     % mySortA numbers.txt mySorted.txt\n";
        exit(EXIT_SUCCESS);
    }


    const int MAX = 1000000;
    ofstream fout;
    ifstream fin;
    int n;

    int v[MAX];
    int count = 0;

    fin.open(argv[1]);
    while (fin >> n)
    {
        v[count++] = n;	// insert a number into the arary and increase the index
    }

    mergesort(v, 0, count-1);	// call the merge sort function

    fout.open(argv[2], ios::out | ios::trunc);
    for (int i = 0; i < count; i++)
        fout << v[i] << endl;


    fout.close();
    fin.close();
    return 0;
}



/*
const int SIZE = 10;
int arr[SIZE];
for (int i = 0; i < SIZE; i++)
    arr[i]=rand() % 100;
display(arr, SIZE);

cout << "****MERGED****" << endl;
mergesort(arr, 0, SIZE - 1);
display(arr, SIZE);
*/