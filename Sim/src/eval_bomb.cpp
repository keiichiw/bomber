#include <vector>
#include "common.h"
#include "eval_bomb.h"
using namespace std;

extern int H, W;
extern int centerX,centerY;
extern int bnum[2];
extern char field[MAX_H][MAX_W];
extern P my[2],op[2];
extern int mypow[2],myhav[2],oppow[2],ophav[2];
extern vector<bomb> bomb_vec;
extern int bomb_board[MAX_H][MAX_W];
extern int bombP_board[MAX_H][MAX_W];

int dontSetABomb(P p){
  for(int i=0;i<(int)bomb_vec.size();i++){
    if(distf(p,bomb_vec[i].pos)<3)return true;
  }
  return false;
}

bool enclosedByWalls(P p){
  int cnt=0,cnt2=0;
  for(int i=0;i<4;i++){
    P n=next(p,i);
    if(field[n.x][n.y]=='#'||field[n.x][n.y]=='+')cnt++;
    if(field[n.x][n.y]=='+')cnt2++;
  }
  return cnt==3||cnt2>=2;
}

bool nearEnemy(P prev,P p){
  for(int i=0;i<2;i++){
    if(canBeKilled(p,op[i],NEAR_ENEMY))return true;
  }
  return false;
}

template<class X> void arrayCopy(X from[][MAX_W],X to[][MAX_W]){
  for(int i=0;i<H;i++)for(int j=0;j<W;j++)to[i][j]=from[i][j];
}


int shouldSetABomb(int id,P prev,P p){
  if(bnum[id]>=myhav[id])return 0;
  int t[2];
  t[0]=INF;t[1]=INF;
  char f1[MAX_H][MAX_W];int b1[MAX_H][MAX_W],bp1[MAX_H][MAX_W];
  for(int i=0;i<2;i++){
    if(bomb_board[op[i].x][op[i].y]<MAGIC_SAFE){
      arrayCopy(field,f1);arrayCopy(bomb_board,b1);arrayCopy(bombP_board,bp1);
      pair<int,P> tp=refuge(op[i],f1,b1,bp1);
      if(canBeKilled(tp.second,p,mypow[id])&&tp.first<=20){
        t[i]=tp.first;
      }
    }
  }
  if(min(t[0],t[1])<=20){
    return min(t[0],t[1]);
  }
  if(enclosedByWalls(p))return 5;
  if(nearEnemy(prev,p))return 5;
  return 0;
}
