#include <iostream>
#include <string>
#include "Minion.h"
using namespace std;



/**********************Main Source***************************/


int main()
{
    //variables
    string name;
    float height;
    int bananas;

    /**********Load minions****************/

    cout<<"Enter information for three minions(names, height, and bananas): "<<endl;
    cin>>name>>height>>bananas;
    Minion minion1(name, height, bananas);

    cin>>name>>height>>bananas;
    Minion minion2(name, height, bananas);

    cin>>name>>height>>bananas;
    Minion minion3(name, height, bananas);
    
    /*************Find tallest minion********/
    cout<< "The tallest minion:"<<endl;
    if(minion1>minion2)
    {
        if (minion2>minion3)
        {
            cout<<minion1;
        }
        else 
        {
            if(minion1<minion3)
            {
                cout<<minion3;
            }
            else
            {
                cout<<minion1;
            }
        }
    }
    else 
    {
        if(minion2<minion3)
        {
            cout<<minion3;
        }
        else
        {
                cout<<minion2;
        }
        
    }
    cout << endl;

    //minion2 grows 2 inch
    cout<<minion2;
    cout<< "The minion grows 2 inch.\n";
    cout<< "The minion now is " <<(++(++minion2)).getHeight()<< " inch tall.\n"<<endl;

    //Minion3 grow 1 inch
    cout<<minion3;
    cout << "Before growing 1 inch the minion was " << minion3++.getHeight() << " inch tall.\n";
    cout << "After growing 1 inch the minion is " << minion3.getHeight() << " inch tall.\n" << endl;
    


   //count number of minions created 
    Minion::printMinionCount();

   
    return 0;
}

