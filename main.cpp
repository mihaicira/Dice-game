#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<iomanip>
using namespace std;

/**< DICE GAME - RULES AND GAMEPLAY
- Each player has to choose, when his turn comes, between "hold" and "roll".
Hold means you stay that round and give the dice to the other player. Roll
means that you roll the dice. Each time the player rolls the dice, the number
he rolls will be added at the player's sum. If a player has rolled
number 1, then the player's sum resets to 1 and the dice is given to the
other player. Winning means reaching a sum of 50. */

int player[3]; /// player[1] & player[2]
int counter=0; /// random function
int starter,nr;/// who stars
int Sp1,Sp2; /// each player's sum
int number=0; ///rolled number
string answer; int answ; ///answers


struct gamer{
string name;
bool win = false;
}p[3];


int random()
{
    /**< generates a random number between 1 and 6*/
    int v[100];
    for(int i=0;i<100;i++) v[i]=rand();

    nr = v[counter]%10;

    if(nr==0 || nr>6){
        counter++;
        random();
    }

    return nr;
}

void minimalize(string &answer)
{
    /**< makes the strings itself being a one without capitals */
    for(int i=0;i<answer.size();i++)
        if(answer[i]<95 && answer[i]>64) answer[i]+=32;
}

void clasament()
{
    /**< writes out the stats */
    system("cls");
    cout<<setw(20)<<p[1].name<<setw(10)<<"|"<<setw(10)<<p[2].name<<endl;
    cout<<setw(20)<<setw(30)<<"|"<<endl;
    cout<<setw(20)<<Sp1<<setw(10)<<"|"<<setw(10)<<Sp2<<endl;
}

int gameplay(int p1, int p2)
{
    clasament(); /// stage 1: stats
    cout<<endl;

    if(p1==1)   /// stage 2: shows the current player
    cout<<"Current player: "<<p1<<" - "<<p[1].name<<endl;
    if(p2==1)
    cout<<"Current player: "<<p1<<" - "<<p[2].name<<endl;

    if(number==0) cout<<"Last lucky number: none"<<endl; /// stage 3: shows the last random number generated
    else cout<<"Last lucky number: "<<number<<endl;
    do{
        cout<<"Hold or Roll?";cin>>answer; /// stage 4: the player choses between "hold" or "roll"
        minimalize(answer);
    }
    while(answer!="hold" && answer!="roll" && answer!="1" && answer!="2");

    if(answer=="hold" || answer=="1") ///stage 4': if "hold" is chosen, then call the function with inversed parameters.
    {
        gameplay(p2,p1);
    }

    else if(answer=="roll" || answer=="2") /// stage 5: otherwise:
    {
        number = random(); ///equal a number with a random one

        cout<<"Lucky number: "<<number<<endl;

        if(number==1 && p1 == 1) {Sp1 = 1; gameplay(p2,p1);} ///if the random number is 1, reset the player's sum and recall the function with inversed parameters
        if(number==1 && p2 == 1) {Sp2 = 1; gameplay(p2,p1);}

        if(number!=1 && p1 == 1) Sp1 += number; ///if it's not, check who's the playing player and add the sum
        if(number!=1 && p2 == 1) Sp2 += number;


        if(Sp1>=50)
        {
            p[1].win = true;
            return 0; ///if you get to the end, return 0 and go to int main (player 1 wins)
        }

        if(Sp2>=50)
        {
            p[2].win = true;
            return 0; ///if you get to the end, return 0 and go to int main (player 2 wins)
        }

        gameplay(p1,p2); ///stage 6: recall the function with the same parameters until the players choses "hold" or dices on 1
    }


}

int number_verify(string a)
{   /**< makes sure that there is no numbers in the string "a" (for names) */
    int k;
    for(char i='0';i<='9';i++)
    {   k = a.find(i);
        if(k!=string::npos) return 0;
    }

    return 1;
}

int main()
{
    system("TITLE Dice game");


    do{
        cout<<"Player 1: ";cin>>p[1].name;
    }
    while(number_verify(p[1].name)==0);

    do{
        cout<<"Player 2: ";cin>>p[2].name;
    }
    while(number_verify(p[2].name)==0 || p[2].name == p[1].name);

    ///makes the names not to be with capitals, so they will be easier to check in the following instructions
    minimalize(p[1].name);
    minimalize(p[2].name);

    ///gives each player a number, so that in the function game-play it'll be known which is who
    player[1] = 1;
    player[2] = 2;

    do{
    cout<<"Who starts?";cout<<endl;cin>>answer;
    minimalize(answer);
    }
    while(answer!="1" && answer!="2" && answer!="one" && answer!="two" && answer!=p[1].name && answer!=p[2].name);

    if(answer=="1" || answer=="one" || answer==p[1].name) starter = 1;
    if(answer=="2" || answer=="two" || answer==p[2].name) starter = 2;

    ///backwards, it makes the first letter of each name to be a capital, so they'll appear nice in the stats
    p[1].name[0] -= 32;
    p[2].name[0] -= 32;

    ///if first one starts, then call function in order (1,2), otherwise, (2,1)
    if(starter==1) gameplay(player[1],player[2]);
    else gameplay(player[2],player[1]);

    ///show up the final stats.
    clasament();

    cout<<endl;

    cout<<"Last lucky number: "<<number<<endl;

    if(p[1].win==true) cout<<p[1].name<<" wins!"<<endl;
    if(p[2].win==true) cout<<p[2].name<<" wins!"<<endl;

    return 0;
}


