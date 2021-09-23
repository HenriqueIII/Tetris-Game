#include "Piece.h"
#include "Board.h"
#include "Tetris.h"
#include "utils/Display.h"
#include "utils/Keyboard.h"
#include <random>

Piece::Piece( int col, int id, Point b1, Point b2, Point b3, Point b4, Point b5, Point b6, Point b7):
base(Board::WIDTH/2, 2), color (col), pieceID(id)
{
    relative[0]=Point(0,0);
    relative[1]=b1;
    relative[2]=b2;
    relative[3]=b3;
    relative[4]=b4;
    relative[5]=b5;
    relative[6]=b6;
    relative[7]=b7;
}

static Piece pieces [Piece::MAX_PIECES] [Piece::STATES] = {
    {
        Piece(Display::BYELLOW, 0,
            Point(-2, -1), Point(-1, -1), Point(0,-1), Point(1,-1), Point(1, 0), Point (0, 1), Point(1,1)),
        Piece(Display::BYELLOW, 0,
            Point(-2, 0), Point(-1, 0), Point(1, 0), Point(2, 0), Point(3, 0), Point (2,-1), Point(3,-1)),
        Piece(Display::BYELLOW, 0,
            Point(-2, -2), Point(-1, -2), Point(-2,-1), Point(-1,-1), Point(-2, 0), Point (-1, 0), Point(1,0)),
        Piece(Display::BYELLOW, 0,
            Point(-2, 0), Point(-1, 0), Point(1, 0), Point(2,0), Point(3, 0), Point (-2, 1), Point(-1,1))
    },
    {
        Piece(Display::BCYAN, 1,
            Point(0, -2), Point(1, -2), Point(0, -1), Point(1,-1), Point(1, 0), Point (0, 1), Point(1, 1)),
        Piece(Display::BCYAN, 1,
            Point(-4, 0), Point(-3, 0), Point(-2, 0), Point(-1, 0), Point(1, 0), Point (2, 0), Point(3, 0)),
        Piece(Display::BCYAN, 1,
            Point(0, -2), Point(1, -2), Point(0, -1), Point(1,-1), Point(1, 0), Point (0, 1), Point(1, 1)),
        Piece(Display::BCYAN, 1,
            Point(-4, 0), Point(-3, 0), Point(-2, 0), Point(-1, 0), Point(1, 0), Point (2, 0), Point(3, 0))
    },
    {
        Piece(Display::BMAGENTA, 2,
            Point(-2, 0), Point(-1,0), Point(1, 0), Point(-2,1), Point(-1, 1), Point (0, 1), Point(1,1)),
        Piece(Display::BMAGENTA, 2,
            Point(-2, 0), Point(-1,0), Point(1, 0), Point(-2,1), Point(-1, 1), Point (0, 1), Point(1,1)),
        Piece(Display::BMAGENTA, 2,
            Point(-2, 0), Point(-1,0), Point(1, 0), Point(-2,1), Point(-1, 1), Point (0, 1), Point(1,1)),
        Piece(Display::BMAGENTA, 2,
            Point(-2, 0), Point(-1,0), Point(1, 0), Point(-2,1), Point(-1, 1), Point (0, 1), Point(1,1))
    },
    {
        Piece(Display::BGREEN, 3,
            Point(-2, 0), Point(-1,0), Point(1, 0), Point(2,0), Point(3, 0), Point (0, -1), Point(1,-1)),
        Piece(Display::BGREEN, 3,
            Point(0, -1), Point(0, 1), Point(1, -1), Point(1,0), Point(1, 1), Point (2, 0), Point(3,0)),
        Piece(Display::BGREEN, 3,
            Point(-2, 0), Point(-1,0), Point(1, 0), Point(2,0), Point(3, 0), Point (0, 1), Point(1,1)),
        Piece(Display::BGREEN, 3,
            Point(-2, 0), Point(-1,0), Point(0, -1), Point(1, -1), Point(1, 0), Point (0, 1), Point(1,1))
    },
    {
        Piece(Display::BRED, 4,
            Point(-2, 0), Point(-1,0), Point(1, 0), Point(-2,1), Point(-1, 1), Point (-2, 2), Point(-1,2)),
        Piece(Display::BRED, 4,
            Point(-2, 0), Point(-1,0), Point(1, 0), Point(2,0), Point(3, 0), Point (2, 1), Point(3,1)),
        Piece(Display::BRED, 4,
            Point(-2, 0), Point(-1,0), Point(1, 0), Point(0,-1), Point(1, -1), Point (0, -2), Point(1,-2)),
        Piece(Display::BRED, 4,
            Point(-2, 0), Point(-1,0), Point(1, 0), Point(2,0), Point(3, 0), Point (-2, -1), Point(-1, -1)),
    },
    {
        Piece(Display::BWHITE, 5,
            Point(-2, 0), Point(-1,0), Point(1, 0), Point(0,-1), Point(1, -1), Point (2, -1), Point(3,-1)),
        Piece(Display::BWHITE, 5,
            Point(-2, -1), Point(-1,-1), Point(-2, 0), Point(-1,0), Point(1, 0), Point (0, 1), Point(1, 1)),
        Piece(Display::BWHITE, 5,
            Point(-2, 0), Point(-1,0), Point(1, 0), Point(0,-1), Point(1, -1), Point (2, -1), Point(3,-1)),
        Piece(Display::BWHITE, 5,
            Point(-2, -1), Point(-1,-1), Point(-2, 0), Point(-1,0), Point(1, 0), Point (0, 1), Point(1, 1)),
    },
    {
        Piece(Display::BBLUE, 6,
            Point(-2, -1), Point(-1,-1), Point(0, -1), Point(1,-1), Point(1, 0), Point (2, 0), Point(3,0)),
        Piece(Display::BBLUE, 6,
            Point(-2, 1), Point(-1,1), Point(-2, 0), Point(-1,0), Point(1, 0), Point (0, -1), Point(1, -1)),
        Piece(Display::BBLUE, 6,
            Point(-2, -1), Point(-1,-1), Point(0, -1), Point(1,-1), Point(1, 0), Point (2, 0), Point(3,0)),
        Piece(Display::BBLUE, 6,
            Point(-2, 1), Point(-1,1), Point(-2, 0), Point(-1,0), Point(1, 0), Point (0, -1), Point(1, -1))
    }

};

Piece::Piece(){
    int npiece;
    npiece = rand() % 7;
    state = 0;
    *this = ::pieces[npiece][state];
}

void Piece::show() {
    for (int i = 0; i < MAX_BLOCKS; i++)
        BOARD->showBlock( base.add (relative[i]), color );
}

void Piece::hide() {
    for (int i = 0; i < MAX_BLOCKS; i++)
        BOARD->hideBlock( base.add (relative[i]));
}

bool Piece::validPosition( Point p ){
    return(
        p.getX() >= 0 && p.getX() <= Board::WIDTH &&
        p.getY() < Board::HEIGHT &&
        ! BOARD->isFilled( p )
    );
}

bool Piece::canRotate() {
    Point p;
    int nextState = (state==3 ? 0 : state+1 );
    Piece newPiece = pieces[pieceID][nextState];
    newPiece.base = base;
    for ( int  i = 0 ; i < MAX_BLOCKS ; i++) {
        p = newPiece.relative[i];
        if (!validPosition ( newPiece.base.add(p) ) )
            return false;
    }
    return true;
}

void Piece::rotate(){
    hide();
    Point oldBase = base;
    int nextState = (state==3 ? 0 : state+1 );
    Piece newPiece = pieces[pieceID][nextState];
    for (int i = 0; i < MAX_BLOCKS; i++)
        relative[i]=newPiece.relative[i];
    state = nextState;
    base = oldBase;
    show();
}

void Piece::moveBy( Point delta ){
    hide();
    base.addEqual( delta );
    show();
}

bool Piece::canMoveBy( Point delta ){
    Point newBase = base.add( delta );
    for (int i = 0; i < MAX_BLOCKS; ++i )
        if ( !validPosition(newBase.add(relative[i])))
            return false; 
    return true;
}

static const float SECONDS_BY_MOVE = 0.6;

void Piece::drop(){
    DeltaTime gap ( SECONDS_BY_MOVE );
    bool flag = true;

    while ( canMoveDown() ) {
        if (flag)
            gap.start();
        do {
            int key = kbd.get();

            switch( key ){
                case SHIFT_LEFT: tryMoveLeft(); break;
                case SHIFT_RIGHT: tryMoveRight(); break;
                case TERMINATE: TETRIS->exit(); return;
                case DROP_DOWN: flag=false; break;
                case ROTATE: tryRotate(); break;
                default: break;
            }
        } while (flag && !gap.dttimeout() );
        tryMoveDown();
    }
}

void Piece::addToBoard() {
    for (int i = 0; i < MAX_BLOCKS; i++)
        BOARD->addBlock(base.add(relative[i]), color);
}
