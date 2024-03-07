#include <iostream> 
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

//pass by value function prototypes
float total_damage(int bot_power[], int numb_bots, float boss_power);
//pass by reference function prototypes
void load_dva(float &defenseMatrixPower, float matrixPowerRequired);
void load_dva(int &micromissles, float misslePowerRequired);
//template
template <typename T>
T missle_power(T power);

int main()
{
/**************************Read Combat Information***************************/

//read combat file name
cout<<"Enter filename"<<endl;
string combatFilename;
cin >> combatFilename;

//bool is used to skip D.Va report if file failed to open
bool filesuccess=0;

ifstream combatFile(combatFilename);
if (!combatFile.is_open())
{
   cout<<"file failed to open"<< endl;
   filesuccess=1;
}

//bots load
int botsCount;
int bot_power[10];
combatFile>> botsCount;

int i;
for (i=0; i<botsCount; i++)
{
    combatFile>>bot_power[i];
}

//boss load
float boss_power;
combatFile>>boss_power;

//load default defense matrix power and missle power
int microMissiles;
float defenseMatrixPower;

combatFile>>microMissiles;
combatFile>>defenseMatrixPower;

combatFile.close();

/*********************Calculate Power needed****************************/
float matrixPowerRequired = total_damage(bot_power, botsCount, boss_power);

//calculate missle power needed from bots
float misslePowerRequired=0.0;

for (i=0; i<botsCount; i++)
{
    misslePowerRequired+=missle_power(bot_power[i]);
}

//from boss
misslePowerRequired+=missle_power(boss_power);




/****************************Load D.Va********************************/
//defense
if (matrixPowerRequired>defenseMatrixPower)
{
    load_dva(defenseMatrixPower, matrixPowerRequired);
}
//missles
load_dva(microMissiles, misslePowerRequired);



/***************************File Report********************************/
if(filesuccess!=1)
{
cout << "D.Va's Combat Report" << endl;
cout << "Combat with " << botsCount <<" Enemy bots"<<endl;
cout << "Loaded mech with " << microMissiles << " micromissiles and the defense matrix power "<<defenseMatrixPower<<"."<<endl;
cout << "Ready for combat!";
}

return 0;
}

//functions for calculation
float total_damage(int *bot_power, int numb_bots, float boss_power)
{
    int i;
    float sum=0;
    for (i=0; i<numb_bots; i++)
    {
        sum+=bot_power[i]; 
    }
    sum+=boss_power;

    return sum;
}

template <typename T>
T missle_power(T power)
{
    return power*3;
}

//functions for loading D.Va

void load_dva(float &defenseMatrixPower, float matrixPowerRequired)
{
    defenseMatrixPower=matrixPowerRequired;   
}

void load_dva(int &micromissles, float missilePowerRequired)
{

    missilePowerRequired=missilePowerRequired/100;
    ceil(missilePowerRequired);
    if(missilePowerRequired>micromissles)
    {
        micromissles=missilePowerRequired;
    }

}





