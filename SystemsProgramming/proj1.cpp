/*
* Malcolm Roddy
* SClass (CECS 325-01)
* Proj 1 Fibonacci Solitaire
* Due Date(9/19/2022)
* I certify that this program is my own original work. I did not copy any part of this program from
* any other source. I further certify that I typed each and every line of code in this program
*/
#include<math.h>
#include <iostream>
#include <iomanip>
using namespace std;

// A utility function that returns true if x is perfect square
bool isFibo(int);

class Card
{
    char suit, rank;
public:
    //constructors
    Card()
    {
        suit = 'z';
        rank = 'z';
    }
    Card(char r, char s)
    {
        setCard(r, s);
    }
    void setCard(char r, char s)
    {
        rank = r;
        suit = s;
    }
    //getters and setters
    int getValue()
    {
        //character T represents 10
        if (rank == 'J' || rank == 'Q' || rank == 'K' || rank == 'T')
            return 10;
        else if (rank == 'A')
            return 1;
        else
            return static_cast<int>(rank);
    }
    char getRank()
    {
        return rank;
    }
    char getSuit()
    {
        return suit;
    }
    //output
    void display()
    {
        //display rank
        if (getRank() == 'T') {
            cout << setfill(' ') << setw(2) << "10";
        }
        else if (rank == 'J' || rank == 'Q' || rank == 'K' || rank == 'A')
        {
            cout << setfill(' ') << setw(2) << getRank();
        }
        else {
            cout << setfill(' ') << setw(2) << static_cast<int>(getRank());
        }
        cout << getSuit() << ", ";
    }
};

class Deck
{
    const static int SIZE = 51;
    Card* deck;
    int count, top;
public:
    //constructor initializes new deck, uses refreshDeck for simplicity
    Deck()
    {
        deck = new Card[SIZE];
        refreshDeck();
    }
    void refreshDeck()
    {
        const char rank[13] = { 'A', 2, 3, 4, 5, 6, 7, 8, 9, 'T', 'J', 'Q', 'K' };
        const char suit[4] = { 'S', 'H', 'D', 'C' };
        top = 0;
        for (int i = 3; i >= 0; i--)
        {
            for (int j = 12; j >= 0; j--)
            {
                //push into stack
                deck[top++] = Card(rank[j], suit[i]);
            }
        }
    }
    //pops card from stack/deck
    Card deal()
    {
        if (isEmpty()) {
            cout << "Error, deck is empty!" << endl;
        }
        else {
            return deck[--top];
        }
    }
    //if top==0, deck empty
    //if top==23, 28 cards left +1
    //x=rand()%(51-23+1)
    //28+top
    void shuffle()
    {
        srand(time(NULL));
        for (int i = 0; i < top; i++)
        {
            //create new index for swap
            //r= rand()%(max-min+1)+min
            int j = (rand() % (SIZE - i + 1)) + i;
            //swap
            Card temp = deck[i];
            deck[i] = deck[j];
            deck[j] = temp;
        }
    }
    bool isEmpty()
    {
        return top == 0;
    }
    void display()
    {
        if (isEmpty()) {
            cout << "Error, deck empty!" << endl;
            return;
        }
        //iterate all 52 cards
        for (int i = top - 1; i >= 0; i--) {
            //make 13 columns
            if (i % 13 == 0) {
                deck[i].display();
                cout << endl;
            }
            else
                deck[i].display();
        }
    }
};
//driver
int main()
{
    Deck myDeck;
    Card myCard;
    int ch = 0;

    cout << "Welcome to Fibonacci Solitaire!\n\n";
    cout << "/************MENU***********\n";
    cout << "1) New Deck\n";
    cout << "2) Display Deck\n";
    cout << "3) Shuffle Deck\n";
    cout << "4) Play Solitaire\n";
    cout << "5) Exit\n";
    cout << "/****************************/\n\n";

    do {
        cout << "\nChoice: ";
        cin >> ch;
        switch (ch) {
        case 1:
            cout << "New deck created" << endl;
            myDeck.refreshDeck();
            break;
        case 2:
            myDeck.display();
            break;
        case 3:
            cout << "Deck shuffled" << endl;
            myDeck.shuffle();
            break;
        case 4:
            //doesnt play if deck is already played/empty
            if (myDeck.isEmpty()) {
                cout << "Error! Deck empty. Enter 1 for new deck" << endl;
            }
            else
            {
                int piles, sum;
                sum = piles = 0;
                Card card;
                cout << "\nPlaying Fibonacci Solitaire !!!\n\n";
                while (!myDeck.isEmpty())
                {
                    card = myDeck.deal();// 1) take top card and display
                    card.display();
                    sum += card.getValue();// 2) add to sum
                    if (isFibo(sum)) //if sum is fibo, discard and start over
                    {
                        cout << " Fibo:" << sum << endl;
                        piles++;
                        sum = 0; //reset
                    }
                }
                //check if winner after deck is emptied
                if (sum == 0) {
                    cout << "\nWinner in " << piles << " piles!" << endl;
                }
                else {
                    cout << "\nLast hand value: " << sum << endl;
                    cout << "Loser in " << piles << " piles!" << endl;
                }
            }
            break;
        case 5: cout << "Exit" << endl;
            break;
        default: cout << "Invalid choice" << endl;
        }
    } while (ch != 5);
    return 0;
}
//utility function to figure out fibonacci number
bool isFibo(int x)
{
    //0 and 1 always true
    if (x == 0 || x == 1)
        return true;
    //check by fibo equation 5*n*n +4 or 5*n*n -4
    int num1 = 5 * x * x + 4;
    int num2 = 5 * x * x - 4;

    int squared1 = sqrt(num1);
    int squared2 = sqrt(num2);
    //compare squared numbers for perfect square
    if (squared1 * squared1 == num1 || squared2 * squared2 == num2)
        return true;
    else
        return false;
}