#ifndef TETRIS_H
#define TETRIS_H

#include "utils/Display.h"
#include "Board.h"

class Tetris{
    static Tetris * instance; // Singleton
    int points; // Pontuação do Jogador

    bool end;   // Flag que determina fim de jogo
    void play();    // Ciclo de vida de uma peça
    void showMessage( char * msg );
    void showPoints();
    bool isOver(){
        return end || BOARD->allLinesOcupated();
    }
public:
    static Tetris * getInstance() {
        if (instance == 0)
            instance = new Tetris;
        return instance;
    }
    // Pontuação a zero. Flag fim de jogo iniciada a FALSE.
    Tetris() : points(0), end(false) {
        dsp.resizeWin();
    }
    // Sequencia completa de acções que decorrem desde
    // o inicio até ao fim de um jogo.
    void go();
    // Apenas usado por board
    void addPoints( int val ){
        points += val;
        showPoints();
    }
    // Apenas usado por piece
    void exit(){
        end = true;
    }
};

#define TETRIS Tetris::getInstance()



#endif