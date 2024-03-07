/*
Malcolm Roddy
Systems Programming
08/28/2022
This program executes the first 20 elements of the fibonacci seqeunce
*/

#include <iostream>
using namespace std;

int fibo(int n)
{
    if ( n == 1 || n == 0)
    {
        return 1;
    }
    else
        return fibo(n-1) + fibo(n-2); //recursion
}

int main()
{
    for(int i=1;i<=20;i++)
        cout<<i<<":"<<fibo(i)<<endl;
    return 0;
}