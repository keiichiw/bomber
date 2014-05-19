import java.io.*;
import java.awt.*;
import javax.swing.*;
class Field{
	public int H,W;
	public String[] map;
	public String turnNum,endStr;
	public Field(int h,int w,String file,int turn){
		try{
			H=h;W=w;
			map=new String[H];
			BufferedReader reader=new BufferedReader(new FileReader(file));
			for(int i=0;i<(2+H)*turn;i++)reader.readLine();
			turnNum=reader.readLine();
			for(int i=0;i<H;i++){
				map[i]=reader.readLine();
			}
			endStr=reader.readLine();
			
			reader.close();
		}catch(Exception e){
			e.printStackTrace();
		}
	}
	public void print() {
		for(int i=0;i<H;i++){
			System.out.println(map[i]);
		}
	}
}
class VisFrame extends JFrame{
	public static final int EXTRA_W=60,EXTRA_H=60,CELL_SIZE=40;
    public int F_H,F_W,C_H,C_W,W,H;
    public static String fn;
    Field f;
	public VisFrame(int w,int h,String fname){
		fn=fname;this.W=w;this.H=h;
		F_H=CELL_SIZE*this.H+EXTRA_H*2;
		F_W=CELL_SIZE*this.W+EXTRA_W*2;
		C_W=F_W/2;C_H=F_H/2;
        this.setSize(F_W,F_H);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        MyPanel panel = new MyPanel();
        this.add(panel,BorderLayout.CENTER);
        this.setVisible(true);
    }
	class MyPanel extends JPanel implements Runnable{
		MyPanel(){
			Thread th = new Thread(this);
			th.start();
		}
		public void paintComponent(Graphics g){
			g.setColor(Color.WHITE);
			g.fillRect(0, 0,F_W,F_H);
			g.setColor(new Color(231,225,143));
			g.fillRect(EXTRA_W, EXTRA_H,f.W*CELL_SIZE,f.H*CELL_SIZE);
			g.setColor(Color.BLACK);
			g.setFont(new Font("TimesRoman",Font.ITALIC,30));
			g.drawString(String.valueOf(f.turnNum),30,30);
			for(int i=0;i<f.H;i++){
				for(int j=0;j<f.W;j++){
					switch(f.map[i].charAt(j)){
					case '#':
						g.setColor(Color.BLACK);
						g.fillRect(EXTRA_W+j*CELL_SIZE, EXTRA_H+i*CELL_SIZE,CELL_SIZE,CELL_SIZE);
						break;
					case '+':
						g.setColor(Color.GRAY);
						g.fillRect(EXTRA_W+j*CELL_SIZE, EXTRA_H+i*CELL_SIZE,CELL_SIZE,CELL_SIZE);
						break;
					case 'A':
					case 'B':
						g.setColor(Color.RED);
						g.fillOval(EXTRA_W+j*CELL_SIZE, EXTRA_H+i*CELL_SIZE,CELL_SIZE,CELL_SIZE);
						break;
					case 'M':
					case 'N':
						g.setColor(Color.BLUE);
						g.fillOval(EXTRA_W+j*CELL_SIZE, EXTRA_H+i*CELL_SIZE,CELL_SIZE,CELL_SIZE);
						break;
					case '@':
						g.setColor(Color.YELLOW);
						g.fillRect(EXTRA_W+j*CELL_SIZE, EXTRA_H+i*CELL_SIZE,CELL_SIZE,CELL_SIZE);
						break;
					case '*':
						g.setColor(Color.YELLOW);
						g.fillRect(EXTRA_W+j*CELL_SIZE, EXTRA_H+i*CELL_SIZE,CELL_SIZE,CELL_SIZE);
						g.setColor(Color.BLACK);
						g.drawLine(EXTRA_W+j*CELL_SIZE, EXTRA_H+i*CELL_SIZE,EXTRA_W+(j+1)*CELL_SIZE, EXTRA_H+(i+1)*CELL_SIZE);
						g.drawLine(EXTRA_W+(j+1)*CELL_SIZE, EXTRA_H+i*CELL_SIZE,EXTRA_W+j*CELL_SIZE, EXTRA_H+(i+1)*CELL_SIZE);
						break;
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
						g.setColor(Color.BLACK);
						g.fillOval(EXTRA_W+j*CELL_SIZE, EXTRA_H+i*CELL_SIZE,CELL_SIZE,CELL_SIZE);
						g.setColor(Color.WHITE);
						g.drawString(String.valueOf(f.map[i].charAt(j)), (int)(EXTRA_W+j*CELL_SIZE+CELL_SIZE*0.5), (int)(EXTRA_H+i*CELL_SIZE+CELL_SIZE*0.5));
						break;
					default:
					}
				}
			}
			
		}
		public void run(){
			int a=0,t=cntTurnNum();
			try{
				f=new Field(H,W,fn,0);
				repaint();
				Thread.sleep(2000);
				while(true){
					f=new Field(H,W,fn,a);
					repaint();
					if((a+1)%t!=0)a=(a+1)%t;
					Thread.sleep(500);
				}
			}catch(Exception e){
				e.printStackTrace();	
			}
		}
	}
	public int cntTurnNum() {
		int num=0;
		try{
			BufferedReader reader=new BufferedReader(new FileReader(fn));
			while(reader.readLine()!=null){
				num++;
			}
			num/=this.H+2;
			reader.close();
		}catch(Exception e){
			e.printStackTrace();
		}
		return num;
	}
}


public class Vis{
	public static int W=15,H=13;
	public static String fname="./data/result.txt";
	public static void main(String[] args) {
		new VisFrame(W,H,fname);
  }	
}
