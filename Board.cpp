//
// Created by slavickkuzmin on 9/21/16.
//

#include "Board.h"

// if compiler GCC then define constants for color output in the Linux operating system
#ifdef __GNUC__
#define KNRM  "\x1B[0m" // normal color
#define KRED  "\x1B[31m" // red color
#endif

Board::Board(int x/* = 8*/) {
    /* array initialization */
        aBoard = new char[x];
        tmp = new char[x];
    /* end */
    size = x; // calculate board size for example 8*8=64 -> size
    /* init Board for start */
    for(int i = 0; i < x; i++)
            aBoard[i] = -1;
    /* end */
    /* initialization random engine */
    random_engine = new std::default_random_engine;//or random_engine = new std::default_random_engine((std::random_device())() );
    UID = new std::uniform_int_distribution<int>(0, x-1);
    prob = new std::uniform_real_distribution<double>(0,1);
    /* end */
}

Board::~Board() {
    /* free aBoard[x][y] memory */
    delete [] aBoard;
    delete [] tmp;
    /* end */
    delete UID;
    delete prob;
    delete random_engine;
}

/* Returns the number of intersections of all the queens on the board */
int Board::analyse() {
    int intersection = 0;
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
        {
            if((aBoard[i] == aBoard[j]) && i != j) intersection++;
            if((std::abs(aBoard[i]-aBoard[j]) == std::abs(i-j)) && (i != j)) intersection++;
        }
    return intersection;
}
/* Displays the chessboard to the console, 0 - cell, 1 - Queen */
void Board::print() {
    std::cout << "Print board: \n";
    std::string h_dot(static_cast<unsigned int>((size*2)+2), '_');
    std::cout << h_dot << std::endl;

    for (int i = 0; i < size; i++) {
        std::cout << "|";
        for(int j = 0; j < size; j++)
        {
#ifdef __GNUC__ //if compiler is GCC print queen in red color
            if(aBoard[i] == j) std::cout << KRED << "1 " << KNRM;
#else           //else print queen in default console color
            if(aBoard[i] == j) std::cout << "1 ";
#endif
            else std::cout << "0 ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << h_dot << std::endl;
}
/* The initial placement of N queens on a chess board */
void Board::randomPlacement() {
    char tmp;
    int i,j;
    for (int i = 0; i < size; i++)
        aBoard[i] = static_cast<char>(i);
    for (int i = 0; i < size; i++)
    {
        i = (*UID)(*random_engine); //or may be UID->operator()(*random_engine)
        j = (*UID)(*random_engine); //also may be rand() % size
        while (i == j) i = (*UID)(*random_engine);//rand() % size;
        tmp = aBoard[i];
        aBoard[i] = aBoard[j];
        aBoard[j] = tmp;
    }
}
/* The number of intersections of the queen at position {x, y} with other queens */
int Board::getIntersection(const int &x,const int &y) {
    int intersection = 0;
    for(int j = 0; j < size; j++)
    {
        if((aBoard[x] == aBoard[j]) && x != j) intersection++;
        if((std::abs(aBoard[x]-aBoard[j]) == std::abs(x-j)) && (x != j)) intersection++;
    }
    return intersection;
}
/* Returns the position of the queen who stands in the worst position, ie it has the greatest number of intersections */
Pos Board::getBadPos() {
    int max = -1;
    Pos ret = {-1, -1};
    for(int i = 0; i < size; i++)
            if(max < getIntersection(i,aBoard[i]))
            {
                max = getIntersection(i,aBoard[i]);
                ret.x = i;
                ret.y = aBoard[i];
            }
    return ret;
}
/* Selects a new random position for the queen who stands on a bad position */
void Board::setNewPos(Pos p) {
    char temp;
    int randval;
    while(true){
        randval = (*UID)(*random_engine);
        if(randval != p.x) break;
    }
    temp = aBoard[p.x];
    aBoard[p.x] = aBoard[randval];
    aBoard[randval] = temp;
}

/* Save board in temp array */
void Board::saveBoard() {
    for(int i = 0; i < size; i++)
        tmp[i] = aBoard[i];
}
/* restore old board to current */
void Board::restoreBoard() {
    for(int i = 0; i < size; i++)
        aBoard[i] = tmp[i];
}

