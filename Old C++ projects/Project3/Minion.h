#ifndef Minion_H
#define Minion_H

#include <string>
using namespace std;


/**********************Header**************************/
class Minion
{
    //output overload 
    friend ostream &operator<<(ostream &output, const Minion &a);
    //non-member function for greater than
    friend bool operator>(const Minion&, const Minion&);
    //class members
    string name;
    float height;
    int bananasOwned;
    static int minionCount;

public:
    //constructor 
    Minion(string name, float height, int bananasOwned);

    //<operator overload (member function)
    bool operator<(const Minion& a) const; 
    
    //get function
    float getHeight() const;

    //postinc overload 
    Minion operator++(int);
    //preinc overload
    Minion &operator++();

    //static function
    static void printMinionCount();

};




#endif