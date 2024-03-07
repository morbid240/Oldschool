/**************
Malcolm Roddy
CS37 
Project 1
*************/

#include <iostream> 
#include <string>
using namespace std;

struct userAccount
{
   //struct to store user information
   string username;
   string citizenship;
   int age;
   float user_balance;
};

int main()
{

   //variable declation
   int numb;
   struct userAccount accts[20];

   float balanceSum = 0.0;
   float highestBalance = 0.0;
   float averageBalance =0.0;
   int usersFromSwiss=0;
   int i=0;
   bool younger;

   //load struct
   cout<<"Please enter information to database in the format of <username> <nationality> <age> <account_balance>, seperated each user by a newline: "<<endl;

   while(cin>> accts[i].username >> accts[i].citizenship >> accts[i].age >> accts[i].user_balance)
   {
         //find highest account balance 
         if(accts[i].user_balance>highestBalance)
         {
            highestBalance=accts[i].user_balance;
         }
         
         //users from Swiss 
         if(accts[i].citizenship== "Swiss")
         {
            usersFromSwiss++;
         }

         //users under 21
         if (accts[i].age<21)
         {
            younger=1;
         }

      balanceSum+=accts[i].user_balance;
      i++;
   }

   //average account balance
   int userCount = i;
   averageBalance=balanceSum/userCount;


   //output
   cout<<"\nQ: What is the highest account balance among all users? "<<endl;
   cout<<"A: $"<< highestBalance <<endl;

   cout<<"\nQ: What's the average account balance of all users?"<<endl;
   cout<<"A: $" <<averageBalance<<endl;

   cout<<"\nQ: How many users come from Swiss?"<<endl;
   cout<<"A: " <<usersFromSwiss<<endl;

   cout<<"\nQ: Do we have any user younger than 21?"<<endl;
      if (younger == 1)
      {
         cout<<"A: Yes";
      }
         else 
         {
            cout<<"A: No";
         }

   return 0;
}




