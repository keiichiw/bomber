#include <vector>
#include <algorithm>
#include "common.h"
#include "init_calc.h"
using namespace std;
extern int H, W;
extern char field[MAX_H][MAX_W];
extern vector<bomb> bomb_vec;
extern int myid[2],opid[2];
extern P my[2],op[2];
extern int mypow[2],myhav[2],oppow[2],ophav[2];
extern int bomb_board[MAX_H][MAX_W];
extern int bombP_board[MAX_H][MAX_W];
extern int dist[2][MAX_H][MAX_W];


void map_dfs(P p,int d,int id, int dist[][MAX_H][MAX_W], char field[][MAX_W]){
  if(dist[id][p.x][p.y]>d&&(field[p.x][p.y]=='.'||d==0)){
    dist[id][p.x][p.y]=d;
    for(int i=0;i<4;i++){
      map_dfs(next(p,i),d+1,id, dist, field);
    }
  }
  return;
}

void calc_map(int id, P my, int dist[][MAX_H][MAX_W], char field[][MAX_W]){
  for(int i=0;i<MAX_H;i++){
    for(int j=0;j<MAX_W;j++)dist[id][i][j]=INF;
  }
  map_dfs(my, 0,id, dist, field);
  return;
}

void rec_calc_bomb(P b,int tn,char fild[][MAX_W],int bomb[][MAX_W],int bombP[][MAX_W]){
  for(int dir=0;dir<4;dir++){
    int cnt=0;
    P p=next(P(b.x,b.y),dir);
    while(inField(p)&&cnt<bombP[b.x][b.y]){
      if(fild[p.x][p.y]=='#')break;
      if(tn<bomb[p.x][p.y]){
        bomb[p.x][p.y]=tn;
        if(bombP[p.x][p.y]>0){
          rec_calc_bomb(p,tn,fild,bomb,bombP);
        }
      }
      if(fild[p.x][p.y]=='+')break;
      p=next(p,dir);
      cnt++;
    }
  }
}


inline bool operator< (const bomb & a, const bomb & b){
	return  a.turn < b.turn;
}
void calc_bomb(){
  sort(bomb_vec.begin(),bomb_vec.end());
  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++){
      bomb_board[i][j]=INF;
      bombP_board[i][j]=0;
    }
  }
  for(int i=0;i<(int)bomb_vec.size();i++){
    bomb b=bomb_vec[i];
    int t=min(bomb_board[b.x][b.y],b.turn);
    bomb_board[b.x][b.y]=min(bomb_board[b.x][b.y],t);
    bombP_board[b.x][b.y]=b.pow;
    field[b.x][b.y]='o';
    rec_calc_bomb(P(b.x,b.y),bomb_board[b.x][b.y],field,bomb_board,bombP_board);
  }
  return;
}

void initial_calc(){
  calc_map(0, my[0], dist, field);
  calc_map(1, my[1], dist, field);
  calc_bomb();
}
