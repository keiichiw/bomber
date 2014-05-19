#ifndef INITCALC_H
#define INITCALC_H
//Initialize
void map_dfs(P, int, int, int [][MAX_H][MAX_W], char[][MAX_W]);
void calc_map(int, P, int[][MAX_H][MAX_W], char[][MAX_W]);
void rec_calc_bomb(P,int,char[][MAX_W],int[][MAX_W],int[][MAX_W]);
void calc_item();
void calc_bomb();
void initial_calc();
#endif
