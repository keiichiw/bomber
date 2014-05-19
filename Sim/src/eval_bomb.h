#ifndef EVALB_H
#define EVALB_H
int dontSetABomb(P);
bool enclosedByWalls(P);
bool nearEnemy(P,P);
int shouldSetABomb(int,P,P);
template<class X> void arrayCopy(X [][MAX_W],X [][MAX_W]);
#endif
