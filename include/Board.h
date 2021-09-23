#ifndef BOARD_H
#define BOARD_H

#include "utils/Display.h"
#include "utils/Point.h"
#include "Line.h"

class Board{
    static Board * instance; // Singleton
public:
    enum {
        X = 3, // Abssissa de Board
        Y = 4,
        HEIGHT=24,
        WIDTH=20,
        COLOR=Display::BLACK
    };
private:
    // Ultima Linha que contem algum bloco
    int lastLine;
    // Array de apontadores para linhas
    Line * lines[HEIGHT];
    // Colorir uma celula-caracter do ecrã
    static void display( Point pos, int color );
    // Remover e destruir a linha da coordenada y
    void deleteLine( int y );
    // Deslocar uma linha de from para to
    void moveLine( int from, int to );
public:
    Board();
    void addBlock( Point p, int color );
    bool allLinesOcupated();
    void show();
    bool isFilled( Point loc );
    static void showBlock( Point pos, int color ){
        display(pos, color);
    }
    static void hideBlock( Point pos ) {
        display(pos, Board::COLOR);
    }
    // Devolve o apontador para singleton
    static Board * getInstance(){
        if (instance == 0)
            instance = new Board;
        return instance;
    }
};

#define BOARD Board::getInstance()




#endif