## Overview

These are AI program for a game like "Bomberman" and its simulator.
AI is written in C++ and the others are in Java.

I refered to the rule of [CODE VS 3.0](https://codevs.jp/ "codevs"), a game-AI contest.


## How to run


### Compile

```
make
```

### Simulate
```
./simulate.sh 
```
At this step, battle of `./Sim/src/player1.cpp` and `./Sim/src/player2.cpp` is simulated and the result is written on `./data/result.txt`.

### Visualize

```
./visualize.sh
```
Then, Java program visualizes `./data/result.txt`.
