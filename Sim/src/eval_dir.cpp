#include <cmath>
#include "common.h"
#include "init_calc.h"
#include "eval_dir.h"
using namespace std;

//Game Info
extern int stonenum;
extern int H, W;
extern int centerX,centerY;
extern char field[MAX_H][MAX_W];

//Board Info
extern int bomb_board[MAX_H][MAX_W];
extern int bombP_board[MAX_H][MAX_W];
extern int dist[2][MAX_H][MAX_W];

extern P my[2],op[2];


bool correctDir(P now,int dir,int id){
  int x=now.x,y=now.y;
  if(abs(centerX-x)+abs(centerY-y)<6)return true;
  if(id%2==0){
    if(x<centerX&&y<centerY){
      if(dir==1)return true;
    }else if(x<centerX){
      if(dir==2)return true;
    }else if(centerX<=x&&centerY<=y){
      if(dir==3)return true;
    }else{
      if(dir==0)return true;
    }
  }else{
    if(x<centerX&&y<centerY){
      if(dir==2)return true;
    }else if(x<centerX){
      if(dir==3)return true;
    }else if(centerX<=x&&centerY<=y){
      if(dir==0)return true;
    }else{
      if(dir==1)return true;
    }
  }
  return false;
}

bool canRefuge(P pos,int turnnum,int pow,P mypos){
  char vfield[MAX_H][MAX_W];
  int vbomb[MAX_H][MAX_W],vbombP[MAX_H][MAX_W];
  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++){
      vfield[i][j]=field[i][j];
      vbomb[i][j]=bomb_board[i][j]-1;
      vbombP[i][j]=bombP_board[i][j];
    }
  }
  vfield[pos.x][pos.y]='o';
  vbomb[pos.x][pos.y]=min(vbomb[pos.x][pos.y],turnnum);
  vbombP[pos.x][pos.y]=pow;
  rec_calc_bomb(pos,vbomb[pos.x][pos.y],vfield,vbomb,vbombP);
  return refuge(mypos,vfield,vbomb,vbombP).first!=DEADEND;
}

bool canRefuge(P pos,int turnnum,int pow,P mypos,char f[][MAX_W],int b[][MAX_W],int bp[][MAX_W]){
  char vfield[MAX_H][MAX_W];
  int vbomb[MAX_H][MAX_W],vbombP[MAX_H][MAX_W];
  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++){
      vfield[i][j]=f[i][j];
      vbomb[i][j]=b[i][j]-1;
      vbombP[i][j]=bp[i][j];
    }
  }
  vfield[pos.x][pos.y]='o';
  vbomb[pos.x][pos.y]=min(vbomb[pos.x][pos.y],turnnum);
  vbombP[pos.x][pos.y]=pow;
  rec_calc_bomb(pos,vbomb[pos.x][pos.y],vfield,vbomb,vbombP);
  return refuge(mypos,vfield,vbomb,vbombP).first!=DEADEND;
}

bool approachEnemy(P now,int dir){
  P nex=next(now,dir);
  if(stonenum==0&&distf(op[0],now)>distf(op[0],nex))return true;
  if(stonenum>0&&min(distf(op[0],now),distf(op[1],now))>min(distf(op[0],nex),distf(op[1],nex)))return true;
  return false;
}

bool isDangerous(P pos){
  return bomb_board[pos.x][pos.y]<=MAGIC_SAFE;
}


int evalDirection(P now,int dir,int id){
	P nex=next(now,dir);
  int ret=1;
	if(!validP(nex))return -100;
  if(field[nex.x][nex.y]!='.')return -100;
  if(stonenum==0&&distf(my[(id+1)%2],now)<distf(my[(id+1)%2],nex))ret+=10;
  if(correctDir(now,dir,id))ret+=CORRECT_DIR;
  if(isDangerous(nex))return -100;
  char f1[MAX_H][MAX_W];int b1[MAX_H][MAX_W],bp1[MAX_H][MAX_W];
  for(int i=0;i<2;i++){
    if(bomb_board[op[i].x][op[i].y]<MAGIC_SAFE){
      for(int i1=0;i1<H;i1++){
        for(int j1=0;j1<W;j1++){
          f1[i1][j1]=field[i1][j1];
          b1[i1][j1]=bomb_board[i1][j1];
          bp1[i1][j1]=bombP_board[i1][j1];
        }
      }
      P tp=refuge(op[i],f1,b1,bp1).second;
      if(!inField(tp))continue;
      if(distf(tp,now)>distf(tp,nex))ret+=100;
    }else{
      if(approachEnemy(now,dir))ret+=TO_Enemy/2;
    }
  }
  return ret;
}
