#include <cstdlib>
#include <vector>
#include <iostream>
#include "common.h"
#include "eval_dir.h"
#include "init_calc.h"
#include "eval_bomb.h"
#include "AI.h"
using namespace std;

//Game Info
extern int H, W;
extern char field[MAX_H][MAX_W];
extern int ch_size;
extern vector<int> ch_row;
extern vector<int> ch_col;
extern vector<int> ch_pow;

extern vector<bomb> bomb_vec;

extern int myid[2],opid[2];
extern P my[2],op[2];

//Now Board
extern int bomb_board[MAX_H][MAX_W];
extern int bombP_board[MAX_H][MAX_W];




vector<int> think(){
  int dir[2]={NONE,NONE},bomb[2];
  bomb[0]=0;bomb[1]=0;
  P now[2]={P(ch_row[myid[0]],ch_col[myid[0]]),P(ch_row[myid[1]],ch_col[myid[1]])};
  int pt[2]={0};
  initial_calc();//Initialize
  //decide direction
  for(int t=0;t<2;t++){
    if(isDangerous(my[t])){
      dir[t]=refuge(my[t],field,bomb_board,bombP_board).first;
    }else{
      if(dir[t]<4)continue;;
      int r=rand()%4;
      for(int s=0;s<4;s++){
        int i=(s+r)%4;
        int temp=evalDirection(now[t],i,0);
        if(temp>pt[t]){
          pt[t]=temp;dir[t]=i;
        }
      }
      if(pt[t]==0)dir[t]=4;
    }
  }
	
  //move
  for(int t=0;t<2;t++){
    my[t]=next(now[t],dir[t]);
  }

  //decide whether put bomb
  for(int t=0;t<2;t++){
    if(dontSetABomb(my[t]))continue;
    int temp=shouldSetABomb(t,now[t],my[t]);
    if(temp>0){//put bomb
      char f1[MAX_H][MAX_W],f2[MAX_H][MAX_W];
      int b1[MAX_H][MAX_W],bp1[MAX_H][MAX_W];
      int b2[MAX_H][MAX_W],bp2[MAX_H][MAX_W];
      int bflg=1;
      int dr[2];
			
      for(dr[0]=0;bflg==1&&dr[0]<5;dr[0]++){
        for(dr[1]=0;bflg==1&&dr[1]<5;dr[1]++){
          arrayCopy(field,f1);arrayCopy(bomb_board,b1);arrayCopy(bombP_board,bp1);
          for(int q=0;q<2;q++){
            if(dr[q]==4)continue;
            P nex=next(op[q],dr[q]);
            if(!validP2(nex, f1))continue;
            f1[nex.x][nex.y]='o';
            b1[nex.x][nex.y]=min(5,b1[nex.x][nex.y]);
            bp1[nex.x][nex.y]=max(bp1[nex.x][nex.y],ch_pow[opid[q]]);
            rec_calc_bomb(nex,b1[nex.x][nex.y],f1,b1,bp1);
          }
          arrayCopy(f1,f2);arrayCopy(b1,b2);arrayCopy(bp1,bp2);
          if(!canRefuge(my[t],max(5,temp),ch_pow[myid[t]],my[t],f1,b1,bp1))bflg=0;
          if(!canRefuge(my[t],max(5,temp),ch_pow[myid[(t+1)%2]],my[(t+1)%2],f2,b2,bp2))bflg=0;
        }
      }

      bomb[t]=temp;
      field[my[t].x][my[t].y]='o';
      bomb_board[my[t].x][my[t].y]=min(temp,bomb_board[my[t].x][my[t].y]);
      bombP_board[my[t].x][my[t].y]=ch_pow[myid[t]];
      rec_calc_bomb(my[t],bomb_board[my[t].x][my[t].y],field,bomb_board,bombP_board);

      
    }
  }
	
	vector<int> ret;
	ret.push_back(dir[0]);
	ret.push_back(bomb[0]);
	ret.push_back(dir[1]);
	ret.push_back(bomb[1]);

	return ret;
}
