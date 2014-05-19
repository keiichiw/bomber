## Overview

These are AI programs for a game like "Bomberman" and its simulator.
AI programs are written in C++ and simulator and visualizer are Java.

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
Java program visualizes `./data/result.txt`.
