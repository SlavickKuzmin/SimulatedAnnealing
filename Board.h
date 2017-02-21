//
// Created by slavickkuzmin on 9/21/16.
//

#ifndef SIMULATED_ANNEALING_BOARD_H
#define SIMULATED_ANNEALING_BOARD_H

#include <iostream>
#include <random>
#include <cmath>

/* structure for position queen on chess board */
struct Pos {
    int x;
    int y;
};

class Board {
public:
    /* constructor */
    Board(int x = 8);
    /* Returns the number of intersections of all the queens on the board */
    int analyse();
    /* Displays the chessboard to the console, 0 - cell, 1 - Queen */
    void print();
    /* The initial placement of N queens on a chess board */
    void randomPlacement();
    /* The number of intersections of the queen at position {x, y} with other queens */
    int getIntersection(const int &x,const int &y);
    /* Returns the position of the queen who stands in the worst position, ie it has the greatest number of intersections */
    Pos getBadPos();
    /* Selects a new random position for the queen who stands on a bad position */
    void setNewPos(Pos p);
    /* Save board in temp array */
    void saveBoard();
    /* restore old board to current */
    void restoreBoard();
    //================================
    /* This is a random number engine class that generates pseudo-random numbers */
    std::default_random_engine *random_engine;
    /* Produces random integer values i, uniformly distributed on the closed interval [a, b] */
    std::uniform_int_distribution<int> *UID;
    /* Produces random float values i, uniformly distributed on the closed interval [a, b] */
    std::uniform_real_distribution<double> *prob;
    /* destructor */
    ~Board();
private:
    /* сhess board*/
    char *aBoard;
    /* temp array for chess board*/
    char *tmp;
    /* size of chess board and amount queens*/
    int size;
};

#endif //SIMULATED_ANNEALING_BOARD_H
