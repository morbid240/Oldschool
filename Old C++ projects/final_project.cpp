using namespace std;
#include <iostream>
#include <string>
#include <iomanip>

//exception class 
class Exception
{
public:
    Exception(string s) : message()
    {
        message="Invalid input [" + s + "].";
    };
    void reason(){cout<<message<<endl;}

private:
    string message;
};

class DeliveryOrder
{
    string name;
    int month, day, year;
    string phone;
    float miles;
    static int OrderCount;
    
public:
    float balance;
    static float const taxRate;
    static float const deliveryRate;

    float getBalance() const;
    static int getOrderCount();

    DeliveryOrder(string n, int m, int d, int y, string pnumb, float miles);
    ~DeliveryOrder();
    void printReceipt() const;

    //pure virtual function
    virtual float VIPdiscount() const=0;
};
//deliveryOrder static members init
const float DeliveryOrder::taxRate=0.0887;
const float DeliveryOrder::deliveryRate=1.5;
int DeliveryOrder::OrderCount;


DeliveryOrder::DeliveryOrder(string n, int m, int d, int y, string pnumb, float dmiles)
{
    name=n;
    month=m;
    day=d;
    year=y;
    phone=pnumb;
    miles=dmiles;

    balance=0;
    OrderCount++;
}

DeliveryOrder::~DeliveryOrder()
{
    cout<<"DeliveryOrder destroyed\n";
}

void DeliveryOrder::printReceipt() const
{
    cout << "Order Detail:" << "\n";
    cout << "\t" << name << "\n";
    cout << "\tDate: " << month << "/" << day << "/" << year << "\n";
    cout << "\tPhone: " << phone << "\n";
    cout << "\tTotal Balance: $" << balance << endl;
}

float DeliveryOrder::getBalance() const
{
    return balance * (1 + taxRate) + miles * deliveryRate;
}

int DeliveryOrder::getOrderCount()
{
    return OrderCount;
}
/***************************Boba Order******************************/
class BobaOrder: public DeliveryOrder
{
    string shopName;
    int drinksCount;
public:
    BobaOrder(string n, int m, int d, int y, string pnumb, float dmiles, string sname);
    ~BobaOrder();
    void printReceipt() const;
    void addDrink(string drinkName, bool boba, int count);
    float VIPdiscount() const;
};

//virtual function override
float BobaOrder::VIPdiscount()const
{
    if(drinksCount>10){return 0.85;}
    else if(drinksCount>5){return 0.9;}
    else if(drinksCount>2){return 0.95;}
    else{return 1;}
}
//constructor
BobaOrder::BobaOrder(string n, int m, int d, int y, string pnumb, float dmiles, string sname)
            :DeliveryOrder(n, m, d, y, pnumb, dmiles)
{
    shopName=sname;
    drinksCount=0;
}
//destructor
BobaOrder::~BobaOrder()
{
    cout<<"BobaOrderDestroyed.\n";
}
//receipt
void BobaOrder::printReceipt() const
{
    DeliveryOrder::printReceipt();
    cout << "\tOrdered Drinks: " << drinksCount << endl;
}
//adding a drink
void BobaOrder::addDrink(string drinkName, bool boba=1, int count=1)
{
    if(boba==1)
    {
        
        if(drinkName=="Matcha Lemonade")
        {
            balance+=(5.5+1)*count;
            drinksCount+=count;
        }
        
        else if(drinkName=="Brown Sugar Oolong Tea")
        {
            balance+=(5+1)*count;
            drinksCount+=count;
        }
        
        else if(drinkName=="Lemon Green Tea")
        {
            balance+=(5.25+1)*count;
            drinksCount+=count;
        }
        else 
        {
            throw Exception(drinkName);
        }
        
        
        
    }
    else if(boba==0)
    {
        
        if(drinkName=="Matcha Lemonade")
        {
            balance+=(5.5)*count;
            drinksCount+=count;
    
        }
        
        else if(drinkName=="Brown Sugar Oolong Tea")
        {
            balance+=(5)*count;
            drinksCount+=count;
 
        }
        
        else if(drinkName=="Lemon Green Tea")
        {
            balance+=(5.25)*count;
            drinksCount+=count;
        }
        else
        {
            throw Exception(drinkName);
        }
        
    }
}

/***************************Food Order********************************/
class FoodOrder: public DeliveryOrder
{
string restaurantName;
int foodCount;
public:
    FoodOrder(string n, int m, int d, int y, string pnumb, float dmiles, string rname);
    ~FoodOrder();
    void printReceipt() const;
    void addFood(string foodName, int side, bool soup);
    float VIPdiscount() const;
};

FoodOrder::FoodOrder(string n, int m, int d, int y, string pnumb, float dmiles, string rname)
        :DeliveryOrder( n, m, d, y, pnumb, dmiles)
{
    restaurantName=rname;
    foodCount=0;
}

FoodOrder::~FoodOrder()
{
    cout<<"Food Order Destroyed\n";
}

void FoodOrder::printReceipt() const
{
    DeliveryOrder::printReceipt();
    cout << "\tOrdered Foods: " << foodCount << endl;
}

void FoodOrder::addFood(string foodName, int side=0, bool soup=0)
{
    if(soup==1)
    {
        if(foodName=="Bone-in Ribeye")
        {
            balance+=32+(side*1)+0.5;
            foodCount++;
           
        }
        else if(foodName=="Rack of Lamb")
        {
            balance+=28+(side*1)+0.5;
            foodCount++;
        }
        else if(foodName=="Grilled Salmon")
        {
            balance+=24+(side*1)+0.5;
            foodCount++;
            
        }
        else if(foodName=="Beyond Meat Burger")
        {
            balance+=22+(side*1)+0.5;
            foodCount++;
        }
        else 
        {
            throw Exception(foodName);
        }
    }
    else if(soup==0)
    {
        
        if(foodName=="Bone-in Ribeye")
        {
            balance+=32+(side*1);
            foodCount++;
           
        }
        
        else if(foodName=="Rack of Lamb")
        {
            balance+=28+(side*1);
            foodCount++;
           
        }
        
        else if(foodName=="Grilled Salmon")
        {
            balance+=24+(side*1);
            foodCount++;
        }

        else if(foodName=="Beyond Meat Burger")
        {
            balance+=22+(side*1);
            foodCount++;
        }
        else 
        {
            throw Exception(foodName);
        }
        
    }
}

float FoodOrder::VIPdiscount()const
{
    if(balance>50){return 0.85;}
    else if(balance>30){return 0.9;}
    else if(balance>20){return 0.95;}
    else{return 1;}
}

/****************************Account************************************/
class Account
{
string username;
string status;
public:
    Account(string n, string s);
    ~Account();
    string getStatus()const;
};

Account::Account(string n, string s="")
{
    status=s;
    username=n;
}

Account::~Account()
{
    cout<<"Account removed.\n";
}

string Account::getStatus()const
{
    return status;
}

/***********************Discount Function***********************/
float applyDiscount(DeliveryOrder*ptr, const Account& ref)
{
    string userstatus=ref.getStatus();
    float totbalance=ptr->getBalance();

    if(userstatus=="Owner"){return (0.1*totbalance);}
    else if(userstatus=="VIP"){return (ptr->VIPdiscount())*totbalance;}
    else if(userstatus==""){return totbalance;}
}

int main()
{
cout<<setprecision(5);
Account bacc("Bob");
Account kacc("Kevin", "VIP");
Account sacc("Stuart", "Owner");

/****************Kevin Placing Order*********************/
    cout<<"Kevin placing order.\n";
    BobaOrder k("Kevin", 3, 2, 2021, "123-456-0000", 10.4, "Bar Pa Tea");

try{
    k.addDrink("Matcha Lemonade");
    k.addDrink("Lemon Green Tea", 0);
    k.addDrink("Brown Sugar Oolong Tea", 0, 2);
    k.addDrink("Iron Goddess");
}
catch(Exception&e)
{
    e.reason();
    cout<<"Not serving requested drinks. Drink order ignored.\n\n";
}
//kevin regular price output
    k.printReceipt();
    cout<<"Balance: $"<<k.getBalance()<<"\n";
//kevin discount output
    DeliveryOrder* kPtr;
    kPtr= &k;

    Account& kref = kacc;
    cout<<"Discounted Balance: $"<<applyDiscount(kPtr, kref)<<"\n\n\n";

/******************Stuart Placing Order********************/
    cout<<"Stuart placing order.\n";
    FoodOrder s("Stuart", 3, 2, 2021, "123-456-1111", 25.5, "Trauts Steak House");
try{
    s.addFood("Bone-in Ribeye", 2, 1);
    s.addFood("Grilled Salmon", 1, 0);
    s.addFood("Beyond Meat Burger", 3, 1);
}

catch(Exception&e){
    e.reason();
    cout<<"Not serving requested food. Food order ignored.\n\n";
}
//stuart output
    s.printReceipt();
    cout<<"Balance: $"<<s.getBalance()<<"\n";

    DeliveryOrder* sPtr;
    sPtr= &s;

    Account& sref = sacc;
    cout<<"Discounted Balance: $"<<applyDiscount(sPtr, sref)<<"\n\n\n";


/*********************Bob Placing Order*********************/
    cout<<"Bob decided to log in to his account and see whether he can afford ordering the same order as Stuart.\n";

//bob output
    s.printReceipt();
    cout<<"Balance: $"<<s.getBalance()<<"\n";
//discount bob output
    DeliveryOrder* bPtr;
    bPtr= &s;

    Account& bref = bacc;
    cout<<"Discounted Balance: $"<<applyDiscount(sPtr, bref)<<"\n";
    cout<<"Bob upset, cancelling order :(\n\n";

//final output
    cout<<"Total order placed: "<<DeliveryOrder::getOrderCount()<<"\n\n";

    return 0;
}