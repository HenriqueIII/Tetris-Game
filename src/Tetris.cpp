#include "Tetris.h"
#include "Piece.h"
#include "utils/Keyboard.h"
#include "utils/Display.h"
#include "utils/Common.h"
#include "utils/Random.h"
#include <random>

Tetris * Tetris::instance = 0;

void Tetris::go(){
    // Programar o teclado para nao esperar actuação de tecla
    kbd.setMode(kbd.VIEW);
    BOARD->show(); // Refrescar a imagem do receptaculo.
    showPoints();
    do{
        play(); // Provocar um ciclo de vida de uma peça
    }while(!isOver()); // Enquanto for possivel criar peças
    showMessage("GAME OVER");
    //Programar o teclado para eserar atuação de tecla
    kbd.setMode(kbd.WAIT);
    // Aguardar actuação da tecla ENTER
    while(kbd.get() != '\r');
}

void Tetris::play(){
    Random::init();
    Piece piece;
    piece.show();
    piece.drop();
    piece.addToBoard();
    // TODO
}

void Tetris::showMessage( char * msg ) {
    dsp.setCursor(Board::X, Board::Y+Board::HEIGHT+1); // TODO com posição de arena
    dsp.setBackground(Display::BLACK);
    dsp.setForeground(Display::WHITE);
    dsp.puts( msg );
}

void Tetris::showPoints() {
    char str[20] = "POINTS= ";
    int l = Common::strlen(Common::itoa(points)) + 8;
    char p[l];
    Common::strcpy(p,Common::itoa(points));
    for (int i = 8; i < l; i++){
        str[i]=p[i-8];
    }
    showMessage(str);
}