CC=g++
OBJS=input.o common.o  init_calc.o eval_dir.o eval_bomb.o AI.o

all: a b Simulate

a: $(OBJS) player1.cpp
	$(CC) -o ../bin/a $(OBJS) player1.cpp

b: $(OBJS) player2.cpp
	$(CC) -o ../bin/b $(OBJS) player2.cpp

Simulate:
	javac -d ../bin/ ./Simu.java

clean:
	rm -rf ../bin/* ./*.o
