#ifndef EVALD_H
#define EVALD_H
bool correctDir(P,int,int);
bool canRefuge(P,int,int,P);
bool canRefuge(P,int,int,P,char[][MAX_W],int[][MAX_W],int[][MAX_W]);
bool approachEnemy(P,int);
bool isDangerous(P);
int evalDirection(P,int,int);
#endif
