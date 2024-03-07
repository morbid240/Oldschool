
#include <iostream>
#include "Minion.h"
using namespace std;

/*******************Implementation************************/
//static member definition
int Minion::minionCount;

//constructor definition
Minion::Minion(string mname, float mheight, int mbananas)
{
    Minion::name=mname;
    Minion::height=mheight;
    Minion::bananasOwned=mbananas;

    Minion::minionCount++;
}

//get function declaration
float Minion::getHeight() const
{
    return this->height;
}

//insertion operator definition
ostream &operator<<(ostream &output, const Minion &m)
{
    output<<"The minion "<<m.name<<" is "<<m.height<<" inches tall and own "<<m.bananasOwned<<" banana(s)"<<endl;
    return output;
}


//postinc overload
Minion Minion::operator++(int)
{
    Minion temp=*this;
    this->height++;
    return temp;
}

//preincrement overload 
Minion& Minion::operator++()
{
    this->height++;
    return *this;
}
//greater than operator (non-member function)
bool operator>(const Minion &m0, const Minion &m1)
{
    return m0.height>m1.height;
}

//less than operator 
bool Minion::operator<(const Minion &m) const
{
    return this-> height<m.height;
}

//static function defintiion
void Minion::printMinionCount()
{
    cout<<minionCount<<" minions created."<<endl;
}