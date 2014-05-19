#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include "common.h"
#include "input.h"
#include "AI.h"
using namespace std;

ofstream ofs("./Sim/temp/comm1.txt");


void output(int move1,int magic1,int move2,int magic2){
  if(0<=move1&&move1<4){
    ofs<<dstr[move1];
  }else{
    ofs<<"NONE";
  }
  if(magic1!=0){
    ofs<<" MAGIC "<<max(5,magic1);
  }
  ofs<<endl;
  if(0<=move2&&move2<4){
    ofs<<dstr[move2];
  }else{
    ofs<<"NONE";
  }
  if(magic2!=0){
    ofs<<" MAGIC "<<max(5,magic2);
  }
  ofs<<endl;
	ofs.flush();
  return;
}


int main() {
  srand(0);
	input();
  vector<int> v = think();
	output(v[0],v[1],v[2],v[3]);
	return 0;
}



