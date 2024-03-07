
/*
* Malcolm Roddy
* Class (CECS 325-01)
* Proj4 - Sort Race w/ Parallel Processing
* Due Date (10/19/2022)
* I certify that this program is my own original work. I did not copy any part of this program from
* any other source. I further certify that I typed each and every line of code in this program
*/

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

bool check_sort(vector<int> v)
{
	for(int i=0;i<v.size()-1;i++){
		if(v[i+1]<v[i])
			return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
	{
		cout << "Please include input filename in param list.\n";
		cout << "Example:\n";
		cout << "     % mySortA numbers.txt \n";
		exit(EXIT_SUCCESS);
	}
	ifstream fin;
	vector<int> v;
	int n, count;
	count=0;
	//open file
	fin.open(argv[1]);
	while (fin >> n)     
	{
		v.push_back(n);  
        count++;
	}

	//output
	cout<<"Verifying "<<count<<" integers are sorted: "<<endl;
	if(check_sort(v))
		cout<<"Success. "<<endl;
	else
		cout<<"Fail. "<<endl;

        return 0;
}