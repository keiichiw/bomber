#ifndef COMMON_H
#define COMMON_H
#include <map>
#include <string>
#include "parameter.h"
using namespace std;
//Basic Info
const int MAX_H = 20;
const int MAX_W = 20;
const int NONE = 4;
const int DEADEND = 111;
const int INF = 100000;
const int dx[4]={-1,0,1,0};
const int dy[4]={0,1,0,-1};
const string dstr[5]={"UP","RIGHT","DOWN","LEFT","NONE"};
#define mp make_pair







//Point
struct P{ 
int x,y;
P(int,int);
P();
P operator +(P);
bool operator ==(P);
bool operator !=(P);
};

//Command 
struct com{
int move[2],bomb[2];
com(int, int, int, int);
com();
};

//Bomb
struct bomb{
int num, x, y, turn, pow;
P pos;
bomb(int, int, int, int, int);
};

int distf(P,P);
P next(P,int);
bool canBeKilled(P,P,int);
bool inField(P);
bool validP(P);
bool validP2(P, char [][MAX_W]);
int secondBomber(P, int,char[][MAX_W], int [][MAX_W],int[][MAX_W]);
pair<int, P> refuge(P ,char[][MAX_W],int [][MAX_W],int [][MAX_W]);

template<class X> void arrayCopy(X [][MAX_W],X [][MAX_W]);


#endif
