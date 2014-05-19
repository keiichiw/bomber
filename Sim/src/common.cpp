#include <cmath>
#include <string>
#include <queue>
#include <cstdlib>
#include "common.h"
#include "parameter.h"
using namespace std;

const P dirP[5]={P(-1,0),P(0,1),P(1,0),P(0,-1),P(0,0)};
extern int H, W;
extern P my[2],op[2];
extern char field[MAX_H][MAX_W];

P::P(int a,int b){x=a;y=b;}
P::P(){x=0;y=0;}
P P::operator+(P obj){return P(this->x+obj.x,this->y+obj.y);}
bool P::operator ==(P obj){return (this->x==obj.x&&this->y==obj.y);}
bool P::operator !=(P obj){return !(this->x==obj.x&&this->y==obj.y);}


com::com(int a,int b,int c,int d){
	move[0]=a;move[1]=c;bomb[0]=b;bomb[1]=d;
}
com::com(){}

bomb::bomb(int a0,int a,int b,int c,int d){
	num = a0;x=a;y=b;turn=c;pow=d;
	pos=P(x,y);
}


int distf(P a,P b){
  return abs(a.x-b.x)+abs(a.y-b.y);
}

P next(P p,int i){return p+dirP[i];}
bool canBeKilled(P pos,P bomb,int power){
  if(pos==bomb)return true;
  if(pos.x!=bomb.x&&pos.y!=bomb.y)return false;
  if(distf(pos,bomb)>power)return false;
  if(pos.x==bomb.x){
    for(int i=min(pos.y,bomb.y)+1;i<max(pos.y,bomb.y);i++){
      if(field[pos.x][i]=='#'||field[pos.x][i]=='+')return false;
    }
  }else{
    for(int i=min(pos.x,bomb.x)+1;i<max(pos.x,bomb.x);i++){
      if(field[i][pos.y]=='#'||field[i][pos.y]=='+')return false;
    }
  }
  return true;
}
bool inField(P a){
  return 0<a.x&&a.x<H-1&&0<a.y&&a.y<W-1;
}

bool validP2(P a, char fld[][MAX_W]){
  return inField(a)&&fld[a.x][a.y]=='.';
}
bool validP(P a){return validP2(a, field);}

int secondBomber(P pos,int d,char fld[][MAX_W],int bomb[][MAX_W],int bombP[][MAX_W]){
  for(int i=0;i<H;i++){
    int x=i,y=pos.y;
    if(inField(P(x,y))&&bombP[x][y]>=abs(x-pos.x)&&bomb[x][y]>d)return bomb[x][y];
  }
  for(int i=0;i<W;i++){
    int x=pos.x,y=i;
    if(inField(P(x,y))&&bombP[x][y]>=abs(y-pos.y)&&bomb[x][y]>d)return bomb[x][y];
  }
  return 0;
}
pair<int, P> refuge(P pos,char fld[][MAX_W],int bomb[][MAX_W],int bombP[][MAX_W]){
  queue<pair<P,int> > que;
  queue<int> dirq;
  int r=rand()%4;
  for(int i=0;i<4;i++){
    int t=(i+r)%4;
    if(validP2(next(pos,t), fld)){
      que.push(make_pair(next(pos,t),0));
      dirq.push(t);
    }
  }
  que.push(make_pair(pos,0));
  dirq.push(NONE);
  int cnt=0;
  while(!que.empty()&&cnt<1000){
    cnt++;
    P p=que.front().first;
    int d=que.front().second;
    int fd=dirq.front();
    que.pop();dirq.pop();
    if(d==bomb[p.x][p.y])continue;
    if((d>bomb[p.x][p.y] && secondBomber(p,d,fld,bomb,bombP)<d+MAGIC_SAFE))continue;
    if(bomb[p.x][p.y]>=MAGIC_SAFE||(d>bomb[p.x][p.y] && secondBomber(p,d,fld,bomb,bombP)>=d+MAGIC_SAFE)){
      return mp(fd, p);
    }
    int r=rand()%5;
    for(int i=0;i<5;i++){
      int t=(r+i)%5;
      if(t==4){
        que.push(make_pair(p,d+1));
        dirq.push(fd);
      }else if(validP2(next(p,t), fld)){
        que.push(make_pair(next(p,t),d+1));
        dirq.push(fd);
      }
    }
  }
  return mp(DEADEND, P(-1,-1));
}





