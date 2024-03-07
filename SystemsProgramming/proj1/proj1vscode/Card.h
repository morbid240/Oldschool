#ifndef Card_H_
#define Card_H_

#include <iostream>
#include <iomanip>
using namespace std;


class Card
{
    char suit, rank;
public:
    Card();
    Card(char r, char s);
    void setCard(char r, char s);
    int getValue();
    char getRank() { return rank; }
    char getSuit() { return suit; }
    void display();
};

#endif