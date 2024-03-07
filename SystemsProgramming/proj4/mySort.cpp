/*
* Malcolm Roddy
* Class (CECS 325-01)
* Proj4 - Sort Race w/ Parallel Processing
* Due Date (10/19/2022)
* I certify that this program is my own original work. I did not copy any part of this program from
* any other source. I further certify that I typed each and every line of code in this program
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <thread>
#include <iostream>
#include <unistd.h>
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
void mergesort(int arr[], int const l, int const r)
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

void *mergesort(void* ptr)
{
    Sub_Array *arg=(Sub_Array*)ptr;
    cout << "-->Entering Thread "<<arg->t_index<<endl;

    int left, right;

    left=arg->left;
    right=arg->right;
    //getting mid point
    int mid=left+(right-left)/2;
    if(left<right)
    {
        mergesort(arg->sub_Arr, left, mid);
        mergesort(arg->sub_Arr, mid+1, right);
        merge(arg->sub_Arr, left, mid, right);
    }
    cout << "<--Exiting Thread "<<arg->t_index<<endl;
    return NULL;
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
    pthread_t thread0, thread1, thread2, thread3, thread4, thread5, thread6, thread7;
    int ret, iret0, iret1, iret2, iret3, iret4, iret5, iret6, iret7;

    iret0=pthread_create(&thread0, NULL, mergesort, (void*)&argList[0]);
    iret1=pthread_create(&thread1, NULL, mergesort, (void*)&argList[1]);
    iret2=pthread_create(&thread2, NULL, mergesort, (void*)&argList[2]);
    iret3=pthread_create(&thread3, NULL, mergesort, (void*)&argList[3]);
    iret4=pthread_create(&thread4, NULL, mergesort, (void*)&argList[4]);
    iret5=pthread_create(&thread5, NULL, mergesort, (void*)&argList[5]);
    iret6=pthread_create(&thread6, NULL, mergesort, (void*)&argList[6]);
    iret7=pthread_create(&thread7, NULL, mergesort, (void*)&argList[7]);
    //Return Values
    cout<<"Thread 0 returns "<<iret0<<endl;
    cout<<"Thread 1 returns "<<iret1<<endl;
    cout<<"Thread 2 returns "<<iret2<<endl;
    cout<<"Thread 3 returns "<<iret3<<endl;
    cout<<"Thread 4 returns "<<iret4<<endl;
    cout<<"Thread 5 returns "<<iret5<<endl;
    cout<<"Thread 6 returns "<<iret6<<endl;
    cout<<"Thread 7 returns "<<iret7<<endl;
    
    //Join threads
    pthread_join( thread0, NULL);
    pthread_join( thread1, NULL); 
    pthread_join( thread2, NULL); 
    pthread_join( thread3, NULL); 
    pthread_join( thread4, NULL); 
    pthread_join( thread5, NULL); 
    pthread_join( thread6, NULL); 
    pthread_join( thread7, NULL);
    
    
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