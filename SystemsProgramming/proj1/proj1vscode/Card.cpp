#include "Card.h"

//constructors
Card::Card() 
{
    suit = rank = NULL;
}
Card::Card(char r, char s) 
{
    setCard(r, s);
}
//getters and setters
int Card::getValue()
{
    //character T represents 10
    if (rank == 'J' || rank == 'Q' || rank == 'K' || rank == 'T')
        return 10;
    else if (rank == 'A')
        return 1;
    else
        return static_cast<int>(rank);
}
void Card::setCard(char r, char s)
{
    rank = r;
    suit = s;
}
//output
void Card::display()
{
    //display rank
    if (getRank() == 'T'){
        cout << setfill(' ') << setw(2)<< "10";
    }
    else if (rank == 'J' || rank == 'Q' || rank == 'K' || rank=='A')
    {
        cout << setfill(' ') << setw(2) << getRank();
    }
    else {
        cout << setfill(' ') << setw(2) << static_cast<int>(getRank());
    } 
    cout << getSuit() << ", ";
}