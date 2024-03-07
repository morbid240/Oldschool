/*
* Malcolm Roddy
* Class (CECS 325-01)
* Proj5 - Sort Race w/ Parallel Processing and thread class
* Due Date (10/24/2022)
* I certify that this program is my own original work. I did not copy any part of this program from
* any other source. I further certify that I typed each and every line of code in this program
*/

#include <thread>
#include <iostream>
#include <fstream>
using namespace std;

struct Sub_Array
{
    int* sub_Arr; //pointer to main array
    int left;
    int right;
    int t_index; //index within thread arglist
};
void merge(int arr[], int l, int m, int r)
{
    //init subarrays
    int sizeleft = m -l + 1;
    int sizeright = r - m;
    /*int k assigned to left index of subarray
    to indicate starting point within main array
    */
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
void mergesort(int arr[], int l, int r)
{
    if (l < r)
    {
        int mid = (l + r) / 2;
        //left subarray
        mergesort(arr, l, mid); 
        //right subarray
        mergesort(arr, mid+1, r);
        merge(arr, l, mid, r);
    }
}

void sortThread(Sub_Array obj)
{
    mergesort(obj.sub_Arr, obj.left, obj.right);
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
    ofstream fout;
    ifstream fin;
    const int MAX = 1000000;
    int n;
    int v[MAX];
    int count = 0;
    fin.open(argv[1]);
    while (fin >> n)
    {
        v[count++] = n;	
    }
    fin.close();
    /********DIVIDE ARRAY************/
    int sub_length = MAX / 8; //subarrays are 125,000 
    int start_index = 0; //starting index of subarrays 
    Sub_Array argList[8];
    for (int i = 0; i < 8; i++)
    {
        argList[i].sub_Arr=v; //sub_Arr always v
        argList[i].t_index=i; //arglist index
        argList[i].left = start_index;
        argList[i].right = start_index + sub_length - 1;
        //iterate through array to get sub array index
        start_index+=sub_length;
    }
    /********CREATE THREADS********/
    thread thread0(sortThread, argList[0]);
    thread thread1(sortThread, argList[1]);
    thread thread2(sortThread, argList[2]);
    thread thread3(sortThread, argList[3]);
    thread thread4(sortThread, argList[4]);
    thread thread5(sortThread, argList[5]);
    thread thread6(sortThread, argList[6]);
    thread thread7(sortThread, argList[7]);

    /**********JOIN THREADS*********/
    thread0.join();
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    thread6.join();
    thread7.join();
    
    //merge adjacent subsections 
    merge(argList[0].sub_Arr, argList[0].left, argList[1].left-1, argList[1].right);
    merge(argList[0].sub_Arr, argList[0].left, argList[2].left-1, argList[2].right);
    merge(argList[0].sub_Arr, argList[0].left, argList[3].left-1, argList[3].right);
    merge(argList[0].sub_Arr, argList[0].left, argList[4].left-1, argList[4].right);
    //merge supersections
    merge(argList[0].sub_Arr, argList[0].left, argList[5].left-1, argList[5].right); 
    merge(argList[0].sub_Arr, argList[0].left, argList[6].left-1, argList[6].right);
    //merge final section
    merge(argList[0].sub_Arr, argList[0].left, argList[7].left-1, argList[7].right);
    /*****OUTPUT*******/
    fout.open(argv[2], ios::out | ios::trunc);
    for (int i = 0; i < MAX; i++)
        fout << v[i] << endl;
    fout.close();
    return 0;
}