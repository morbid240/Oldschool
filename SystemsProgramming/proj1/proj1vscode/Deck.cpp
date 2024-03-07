#include "Deck.h"

Deck::Deck()
{
    deck = new Card[SIZE];
    count = 0;
    top = 0;
    refreshDeck();
}
void Deck::refreshDeck()
{
    const char rank[13] = { 'A', 2, 3, 4, 5, 6, 7, 8, 9, 'T', 'J', 'Q', 'K' };
    const char suit[4] = { 6,3,4,5 }; //numbers in char make suit signs
    count = top = 0;
    for (int i = 3; i >=0; i--)
    {
        for (int j = 12; j >=0; j--)
        {
            //push into stack
            deck[top++] = Card(rank[j], suit[i]);
            count++;
        }
    }
}
//takes card from top of deck
Card Deck::deal()
{
    if (!isEmpty()) {
        count--;
        return deck[--top];
    }
}
void Deck::shuffle()
{
    srand(time(NULL));

    for (int i = 0; i < SIZE; i++)
    {
        //create new index for swap
        int j = rand() % SIZE;
        //swap
        Card temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}
bool Deck::isEmpty()
{
    return top == 0;
}
void Deck::display()
{
    if (isEmpty()) {
        cout << "Error, deck empty!" << endl;
        return;
    }
    //iterate all 52 cards
    for (int i = top-1; i>=0; i--) {
        //13 columns
        if (i % 13 == 0){
            deck[i].display();
            cout << endl;
        }
        else
            deck[i].display();
    }
}