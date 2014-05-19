import java.util.ArrayList;
import java.util.Scanner;
import java.io.*;
class P{
    public int x,y;
    public P(int a,int b){
        x=a;y=b;
    }
}
class Data{
    final int MAX_H=20;
    final int MAX_W=20;
    final int[] dx={-1,0,1,0};
    final int[] dy={0,1,0,-1};
    static int turn;
    static int MAX_TURN;
    int my_id;
    static int H,W;
    static char[][] field=new char[20][20];

    static int ch_size;
    static int[] ch_pid;
    static int[] ch_id;
    static int[] ch_row;
    static int[] ch_col;
    static int[] ch_pow;
    static int[] ch_hav;

    static int magic_size;
    static int[] magic_cid;
    static int[] magic_row;
    static int[] magic_col;
    static int[] magic_turn;
    static int[] magic_pow;
    static int item_size;
    static int[] item_type;
    static int[] item_row;
    static int[] item_col;
    int[][] dist=new int[MAX_H][MAX_W];
    int[][] attack=new int[MAX_H][MAX_W];
    public Data(){};
    public void update(){
        File file=new File("./data/input.txt");
        try{
            Scanner scanner=new Scanner(file);
            char[] str;
            if(!scanner.hasNext())System.out.println("asfdsaf");
            turn=scanner.nextInt();
            MAX_TURN=scanner.nextInt();
            my_id=scanner.nextInt();
            H=scanner.nextInt();
            W=scanner.nextInt();
            for(int h=0;h<H;h++){
                str=scanner.next().toCharArray();
                for(int w=0;w<W;w++){
                    if(str[w] == '@'){
                        str[w]='.';
                    }
                    field[h][w]=str[w];
                }
            }

            ch_size=scanner.nextInt();
            ch_pid=new int[ch_size];
            ch_id=new int[ch_size];
            ch_row=new int[ch_size];
            ch_col=new int[ch_size];
            ch_pow=new int[ch_size];
            ch_hav=new int[ch_size];

            for(int i=0;i<ch_size;i++){
                ch_pid[i]=scanner.nextInt();
                ch_id[i]=scanner.nextInt();
                ch_row[i]=scanner.nextInt();
                ch_col[i]=scanner.nextInt();
                ch_pow[i]=scanner.nextInt();
                ch_hav[i]=scanner.nextInt();
            }

            magic_size=scanner.nextInt();
            magic_cid=new int[magic_size];
            magic_row=new int[magic_size];
            magic_col=new int[magic_size];
            magic_turn=new int[magic_size];
            magic_pow=new int[magic_size];
            for(int i=0;i<magic_size;i++){
                magic_cid[i]=scanner.nextInt();
                magic_row[i]=scanner.nextInt();
                magic_col[i]=scanner.nextInt();
                magic_turn[i]=scanner.nextInt();
                magic_pow[i]=scanner.nextInt();
                field[magic_row[i]][magic_col[i]]='o';
            }

            item_size=scanner.nextInt();
            item_type=new int[item_size];
            item_row=new int[item_size];
            item_col=new int[item_size];
            for(int i=0;i<item_size;i++){
                str=scanner.next().toCharArray();
                item_type[i]=(str[0] == 'N' ? 0 : 1);
                item_row[i]=scanner.nextInt();
                item_col[i]=scanner.nextInt();
            }
            scanner.close();
        }catch(FileNotFoundException e){
            System.err.println("ERROR: File is not found!!!");
            e.printStackTrace();
        }
    }
    public void writeToFile(){
        File file=new File("./data/input.txt");
        try{
            PrintWriter pw=new PrintWriter(new BufferedWriter(new FileWriter(file)));
            pw.println(turn);//System.out.println(turn);
            pw.println(MAX_TURN);
            pw.println(0);
            pw.println(H);
            pw.println(W);
            for(int h=0;h<H;h++){
                for(int w=0;w<W;w++){
                    pw.print(field[h][w]);
                }
                pw.println("");
            }
            pw.println(ch_size);
            for(int i=0;i<ch_size;i++){
                pw.println(ch_pid[i]);
                pw.println(ch_id[i]);
                pw.println(ch_row[i]);
                pw.println(ch_col[i]);
                pw.println(ch_pow[i]);
                pw.println(ch_hav[i]);
            }
            pw.println(magic_size);
            for(int i=0;i<magic_size;i++){
                pw.println(magic_cid[i]);
                pw.println(magic_row[i]);
                pw.println(magic_col[i]);
                pw.println(magic_turn[i]);
                pw.println(magic_pow[i]);
            }
            pw.println(item_size);
            for(int i=0;i<item_size;i++){
                if(item_type[i]==0){
                    pw.println("NUMBER_UP");
                }else{
                    pw.println("POWER_UP");
                }
                pw.println(item_row[i]);
                pw.println(item_col[i]);
            }
            pw.println("END");
            pw.close();
        }catch(IOException e){
            System.err.println("ERROR: IOException!!!");
            e.printStackTrace();
        }
    }
    
    public P next(P p,int i){
        return new P(p.x+dx[i],p.y+dy[i]);
    }
    public boolean inField(P p){
        return 0<=p.x&&p.x<H&&0<=p.y&&p.y<W;
    }
    public  void rec_calc_bomb(P b,int tn,char fild[][],int bomb[][],int bombP[][]){
        for(int dir=0;dir<4;dir++){
            int cnt=0;
            P p=next(b,dir);
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
    static int[][] bomb_board =new int[20][20];
    static int[][] bombP_board =new int[20][20];
    static int[] bomb_vec;
    final int INF=100000;
    public int min(int a,int b){return(a<b)?a:b;}
    
    public void calc_bomb(){
        for(int i=0;i<H;i++){
            for(int j=0;j<W;j++){
                bomb_board[i][j]=INF;
                bombP_board[i][j]=0;
            }
        }
        for(int i=0;i<magic_size;i++){
            int x=magic_row[i],y=magic_col[i],aturn=magic_turn[i],pow=magic_pow[i];
            int t=min(bomb_board[x][y],aturn);
            bomb_board[x][y]=t;
            bombP_board[x][y]=pow;
            field[x][y]='o';
            rec_calc_bomb(new P(x,y),t,field,bomb_board,bombP_board);
        }
        return;
    }
    public void ComWork(File file,int num){
        try{
            BufferedReader scanner;
            scanner=new BufferedReader(new FileReader((file)));
            for(int i=num;i<num+2;i++){
                String str=scanner.readLine();
                if(str=="")break;
                int ix=0;
                switch(str.charAt(0)){
                case 'U':
                    ix=0;
                    break;
                case 'R':
                    ix=1;
                    break;
                case 'D':
                    ix=2;
                    break;
                case 'L':
                    ix=3;
                    break;
                default:
                    ix=-1;
                }
                if(ix!=-1&&inField(next(new P(ch_row[i],ch_col[i]),ix))){
                    if(field[ch_row[i]+dx[ix]][ch_col[i]+dy[ix]]=='.'){
                        ch_row[i]+=dx[ix];ch_col[i]+=dy[ix];
                    }
                }
                if(str.contains("M")){
                    int x=ch_row[i],y=ch_col[i];
                    int t=min(bomb_board[x][y],5);
                    bomb_board[x][y]=t;
                    // System.out.println(bomb_board[x][y]);
                    bombP_board[x][y]=ch_pow[i];
                    field[x][y]='o';
                    rec_calc_bomb(new P(x,y),t,field,bomb_board,bombP_board);
                }
            }
            scanner.close();
        }catch(IOException e){
            e.printStackTrace();
        }
    }
    public void readCom(){
			  File file=new File("./Sim/temp/comm1.txt");
        File file2=new File("./Sim/temp/comm2.txt");
        ComWork(file,0);
        ComWork(file2,2);
        return;
    }
    public boolean check(){
        turn++;
        boolean ret=false;
        for(int i=0;i<4;i++){
            if(bomb_board[ch_row[i]][ch_col[i]]==0){
                if(i<2){
                    System.out.println("Player1 Dead!");
                }else{
                    System.out.println("Player2 Dead!");
                }
                field[ch_row[i]][ch_col[i]]='*';
                ret=true;
            }
        }
        ArrayList<Integer> id=new ArrayList<Integer>();
        ArrayList<Integer> row=new ArrayList<Integer>();
        ArrayList<Integer> col=new ArrayList<Integer>();
        ArrayList<Integer> turn=new ArrayList<Integer>();
        ArrayList<Integer> pow=new ArrayList<Integer>();
        for(int i=0;i<H;i++){
            for(int j=0;j<W;j++){
                if(field[i][j]=='@'){
                    field[i][j]='.';
                }
                if(field[i][j]=='o'){
                    if(bomb_board[i][j]>0){
                        id.add(0);
                        row.add(i);col.add(j);
                        turn.add((bomb_board[i][j]-1));
                        pow.add(bombP_board[i][j]);
                    }else{
                        field[i][j]='@';
                        bomb_board[i][j]=INF;
                        bombP_board[i][j]=0;
                    }
                }else if(bomb_board[i][j]==0&&field[i][j]!='*'){
                    field[i][j]='@';
                    bomb_board[i][j]=INF;
                    bombP_board[i][j]=0;
                }else if(bomb_board[i][j]<10){
                    bomb_board[i][j]-=1;
                }

            }
        }
        magic_size=id.size();
        magic_cid=new int[magic_size];
        magic_row=new int[magic_size];
        magic_col=new int[magic_size];
        magic_turn=new int[magic_size];
        magic_pow=new int[magic_size];
        for(int i=0;i<magic_size;i++){
            magic_cid[i]=id.get(i);
            magic_row[i]=row.get(i);
            magic_col[i]=col.get(i);
            magic_turn[i]=turn.get(i);
            magic_pow[i]=pow.get(i);
        }
        ArrayList<Integer> type=new ArrayList<Integer>();
        row.clear();
        col.clear();
        for(int i=0;i<4;i++){
            for(int j=0;j<item_size;j++){
                if(item_row[j]==ch_row[i]&&item_col[j]==ch_col[i]){
                    if(item_type[j]==1){
                        ch_pow[i]+=1;
                    }else{
                        ch_hav[i]+=1;
                    }
                }else{
                    type.add(item_type[i]);
                    row.add(item_row[i]);
                    col.add(item_col[i]);
                }
            }
        }
        item_size=type.size();
        item_type=new int[item_size];
        item_row=new int[item_size];
        item_col=new int[item_size];
        for(int i=0;i<item_size;i++){
            item_type[i]=type.get(i);
            item_row[i]=row.get(i);
            item_col[i]=col.get(i);
        }
        return ret;
    }
    public static void writeResult(){
        File file=new File("./data/result.txt");
        try{
            PrintWriter pw=new PrintWriter(new BufferedWriter(new FileWriter(file,true)));
            //System.out.println(file);
            pw.print("turn");
            pw.println(turn);//System.out.println(turn);
            for(int i=0;i<H;i++){
                for(int j=0;j<W;j++){
                    if(field[i][j]=='*'){
                        pw.print('*');
                    }else if(ch_row[0]==i&&ch_col[0]==j){
                        pw.print('A');
                    }else if(ch_row[1]==i&&ch_col[1]==j){
                        pw.print('B');
                    }else if(ch_row[2]==i&&ch_col[2]==j){
                        pw.print('M');
                    }else if(ch_row[3]==i&&ch_col[3]==j){
                        pw.print('N');
                    }else{
                        if(field[i][j]=='o'){
                            pw.print(bomb_board[i][j]);
                        }else{
                            pw.print(field[i][j]);
                        }
                    }
                }
                pw.println("");
            }
            pw.println("--------------------------------------");
            pw.close();
        }catch(IOException e){
            System.out.println("asdfsafd");
            e.printStackTrace();
        }
    }
    public boolean run(){
        boolean a=false;
        calc_bomb();
        readCom();
        a=check();
        writeToFile();
        writeResult();
        return a;
    }
}

public class Simu{
    public static Process solution;
    public static void numChange(){
        try{
            File file=new File("./data/input.txt");
            BufferedReader scanner;
            scanner=new BufferedReader(new FileReader((file)));
            ArrayList<String> strs=new ArrayList<String>();
            String str;
            str=scanner.readLine();
            while(str.charAt(0)!='E'){
                strs.add(str);
                str=scanner.readLine();
            }
            strs.add(str);
            scanner.close();

            strs.set(2,"1"); 
            File file2=new File("./data/input.txt");
            file2.delete();
            FileWriter fw = new FileWriter(file2);
            for(int i=0;i<strs.size();i++){
                fw.write(strs.get(i));
                fw.write("\n");
            }
            fw.close();
        }catch(Exception e){
            e.printStackTrace();
        }
    }
    public static void main(String[] args){
        try{
            int i=0;
            Data data=new Data();
            for(i=0;i<200;i++){
                Process p=Runtime.getRuntime().exec("./Sim/bin/a");
                int ret=p.waitFor();
                p.destroy();
                numChange();
                p=Runtime.getRuntime().exec("./Sim/bin/b");
                ret=p.waitFor();
                p.destroy();
                data.update();
                if(data.run()){
                    System.out.println("END!!!");
                    break;
                }
            }
        }catch(Exception e){
            System.err.println("ERROR in main");
            e.printStackTrace();
        }
    }
}
