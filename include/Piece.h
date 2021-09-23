#ifndef PIECE_H
#define PIECE_H

#include "utils/Point.h"

class Piece{
public:
    enum{
        MAX_BLOCKS = 8, MAX_PIECES = 7, STATES = 4,
        SHIFT_LEFT = 'i', SHIFT_RIGHT = 'p',
        ROTATE = 'o', TERMINATE = 27,
        DROP_DOWN = ' '
    };
private:
    Point base;
    int color;
    Point relative[MAX_BLOCKS];
    int state, pieceID;
    // Metodos basicos
    void hide();    // Ocultar peça
    void rotate();  // Promove a rotaçao
    void moveBy(Point delta); // Desloca de delta
    // Metodos de teste
    bool validPosition(Point p); // Testa se p livre
    bool canRotate();               // Testa se pode rodar
    bool canMoveBy(Point delta);    // Testa se pode deslocar-se
    // Testar se pode mover-se para baixo
    bool canMoveDown() { 
        return canMoveBy ( Point ( 0, +1 ) ); 
    }
    void tryMoveBy( Point delta ) {
        if ( canMoveBy( delta ) )
            moveBy(delta);
    }  
    void tryMoveLeft(){
        tryMoveBy(Point( -2 , 0 ));
    }
    void tryMoveRight(){
        tryMoveBy(Point( +2, 0 ));
    }
    void tryMoveDown(){
        tryMoveBy(Point( 0, +1 ));
    }
    void tryRotate(){
        if ( canRotate() )
            rotate();
    }
public:
    Piece( int color, int id, Point b1, Point b2, Point b3, Point b4, Point b5, Point b6, Point b7);
    Piece();
    void show();
    void addToBoard();
    void drop();
    
};

#endif