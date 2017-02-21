/*
 * Create by Slavick Kuzmin 29/09/2016 16:45
 *
 */
#include <iostream>
#include "Board.h"
#include "ctime"

int main() {
    const int size = 200; // the size of the chessboard
    Board board(size);
    board.randomPlacement();

    //begin init
    double maxTemperature = 40.0;
    double minTemperature = 1e-10;

    int t_iter = 40;

    double p = 0;
    int oldAnalyse, newAnalyse;

    int counter = 0; // the number of loop iterations

    //==========
    oldAnalyse = board.analyse();
    clock_t begin = clock();
    while(maxTemperature > minTemperature) {
        for(int i = 0; i < t_iter; i++) {
            board.saveBoard();

            board.setNewPos(board.getBadPos());

            newAnalyse = board.analyse();

            if(newAnalyse == 0) break;

            if(newAnalyse < oldAnalyse) {
                oldAnalyse = newAnalyse;
            }
            else {
                p = exp((oldAnalyse - newAnalyse) / maxTemperature);
                if (p <= board.prob->operator()(*(board.random_engine))) {
                    board.restoreBoard();
                    oldAnalyse = board.analyse();
                }
            }
            counter++;
        }
        maxTemperature *= 0.98;
        if(newAnalyse == 0) break;
    }

    //===================
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    board.print();
    std::cout << "==|Annealing simulation for the problem of N Queens|==" << std::endl;
    std::cout << "size=" << size << " counter = " << counter << " maxtemp = " << maxTemperature << " Analyse = " << board.analyse() << " Time spent= "<< time_spent <<std::endl;
    return 0;
}