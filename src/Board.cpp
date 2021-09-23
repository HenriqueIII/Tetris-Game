#include "Board.h"
#include "Tetris.h"

Board * Board::instance = 0;

Board::Board() {
    for (int y = 0; y < HEIGHT; ++y )
        lines[ y ] = new Line;
    // Ultima linha sem nenhum elemento preenchido
    lastLine = HEIGHT;
}

bool Board::isFilled( Point loc ){
    return lines[loc.getY()]->isFilled(loc.getX());
}

void Board::display( Point loc, int col ){
    // Modificar a cor de escrita para col
    dsp.setBackground(col-8);
    dsp.setForeground(col);
    // Posicionar o cursor
     dsp.setCursor( loc.getX()+Board::X, loc.getY()+Board::Y );
    if (col == Board::COLOR){
        dsp.putc(' ');
        return;
    }
    if(loc.getX()%2==0)
       dsp.putc('[');
    else
        dsp.putc(']');
    // Escrever o caracter
    
}

void Board::show() {
    // Desenha os lados
    for (int y = 4; y < HEIGHT; ++y ){
        dsp.setBackground(Display::WHITE);
        dsp.putc(X-2, y+Y, '[', Display::BLACK);
        dsp.putc(X-1, y+Y, ']', Display::BLACK);
        dsp.putc(X+WIDTH, y+Y, '[', Display::BLACK);
        dsp.putc(X+WIDTH+1, y+Y, ']', Display::BLACK);
    }
    // Desenha o fundo
    dsp.setCursor(X-2, Y+HEIGHT );
    dsp.setBackground(Display::WHITE);
    dsp.setForeground(Display::BLACK);
    for (int x = -2; x <= WIDTH+1; ++x)
        if (x % 2)
            dsp.putc(']');
        else
            dsp.putc('[');
}

void Board::addBlock(  Point p, int color ){
    lines[p.getY()]->setColor(p.getX(), color);
    if ( p.getY() < lastLine )
        lastLine=p.getY();
}

bool Board::allLinesOcupated(){
    for (int y = HEIGHT - 1; y >= lastLine; y--)
        if (lines[y]->isFilled())
            deleteLine( y++ );
    return lastLine < 4;
}

void Board::deleteLine( int y ) {
    lines[y]->blink( y );
    lines[y]->hide( y );
    TETRIS->addPoints( 1 );
    delete lines[y];
    for ( ; y > lastLine; y--)
        moveLine( y-1, y);
    lines[y] = new Line;
    ++lastLine; 
}

void Board::moveLine( int from, int to ){
    lines[from]->hide( from );
    lines[to] = lines[from];
    lines[to]->show( to );
}