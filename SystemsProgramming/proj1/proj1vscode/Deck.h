#ifndef Deck_H_
#define Deck_H_

#include "Card.h"

class Deck
{
    const static int SIZE = 52;
    Card* deck;
    int count, top;
public:
    //constructor initializes new deck, uses refreshDeck for simplicity
    Deck();
    void refreshDeck();
    //pops card from stack/deck
    Card deal();
    void shuffle();
    bool isEmpty();
    void display();
};

#endif