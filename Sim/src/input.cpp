#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include "common.h"
#include "input.h"
using namespace std;

//Board Info
int H, W;
P my[2],op[2];
char field[MAX_H][MAX_W];
int bomb_board[MAX_H][MAX_W];
int bombP_board[MAX_H][MAX_W];
int dist[2][MAX_H][MAX_W];

//Game Info
int stonenum;
int turn,stageturn;
int MAX_TURN;
int my_id;
int bnum[2];
int centerX,centerY;

extern int predir[2];
//Initial Info
int ch_size;
vector<int> ch_pid;
vector<int> ch_id;
vector<int> ch_row;
vector<int> ch_col;
vector<int> ch_pow;
vector<int> ch_hav;				 
int bomb_size;
vector<int> bomb_cid;
vector<int> bomb_row;
vector<int> bomb_col;
vector<int> bomb_turn;
vector<int> bomb_pow;
vector<bomb> bomb_vec;

int item_size;
vector<int> item_type;
vector<int> item_row;
vector<int> item_col;
int myid[2],opid[2];
int mypow[2],myhav[2],oppow[2],ophav[2];


ifstream ifs("./data/input.txt");

void input() {
	string str;
  ifs >> turn;
	
  ifs >> MAX_TURN;
  ifs >> my_id;
  myid[0] = my_id * 2;
  myid[1] = my_id * 2 + 1;
  opid[0] = (1-my_id) * 2;
  opid[1] = (1-my_id) * 2 + 1;
  ifs >> H;
  centerX=H/2;
  ifs >> W;
  centerY=W/2;
  stonenum=0;
  for (int h = 0; h < H; h++) {
    ifs >> str;
    for (int w = 0; w < W; w++) {
      if (str[w] == '@') str[w] = '.';
      field[h][w] = str[w];
      if(field[h][w]=='+')stonenum++;
    }
  }

  ifs >> ch_size;
  ch_pid.resize(ch_size);
  ch_id.resize(ch_size);
  ch_row.resize(ch_size);
  ch_col.resize(ch_size);
  ch_pow.resize(ch_size);
  ch_hav.resize(ch_size);
  for (int i = 0; i < ch_size; i++) {
    ifs >> ch_pid[i];
    ifs >> ch_id[i];
    ifs >> ch_row[i];
    ifs >> ch_col[i];
    ifs >> ch_pow[i];
    ifs >> ch_hav[i];
  }
  for(int i=0;i<2;i++){
    mypow[i]=ch_pow[myid[i]];myhav[i]=ch_hav[myid[i]];
    oppow[i]=ch_pow[opid[i]];myhav[i]=ch_hav[opid[i]];
  }
  ifs >> bomb_size;
  bomb_cid.resize(bomb_size);
  bomb_row.resize(bomb_size);
  bomb_col.resize(bomb_size);
  bomb_turn.resize(bomb_size);
  bomb_pow.resize(bomb_size);
  bomb_vec.clear();
  bnum[0]=0;bnum[1]=0;
  for (int i = 0; i < bomb_size; i++) {
    ifs >> bomb_cid[i];
    ifs >> bomb_row[i];
    ifs >> bomb_col[i];
    ifs >> bomb_turn[i];
    ifs >> bomb_pow[i];
    bomb_vec.push_back(bomb(bomb_cid[i],bomb_row[i],bomb_col[i],bomb_turn[i],bomb_pow[i]));
    field[bomb_row[i]][bomb_col[i]] = 'o';
    if(bomb_cid[i]==myid[0]){
      bnum[0]++;
    }else if(bomb_cid[i]==myid[1]){
      bnum[1]++;
    }
  }
  ifs >> item_size;
  item_type.resize(item_size);
  item_row.resize(item_size);
  item_col.resize(item_size);
  for (int i = 0; i < item_size; i++) {
    ifs >> str;
    item_type[i] = (str[0] == 'N' ? 0 : 1);
    ifs >> item_row[i];
    ifs >> item_col[i];
  }
  
  my[0]=P(ch_row[myid[0]],ch_col[myid[0]]);
  my[1]=P(ch_row[myid[1]],ch_col[myid[1]]);
  op[0]=P(ch_row[opid[0]],ch_col[opid[0]]);
  op[1]=P(ch_row[opid[1]],ch_col[opid[1]]);
  ifs >> str;  // "END"
  return;
}
