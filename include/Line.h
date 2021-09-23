#ifndef LINE_H
#define LINE_H

#include "utils/DeltaTime.h"
#include "utils/Point.h"

class Line{
public:
    enum {
        NONE = -1,          // Cor ficiticia para inexistência de bloco
        WIDTH = 20,         // Numero de células da linha.
        BLINK_DELETE = 10   // Numero de intermitencias de visibilidade
                            // a provocar na linha a remover
    };
private:
    int line[WIDTH];
public:
    Line();
    void setColor( int x, int color ){
        line[x] = color;
    }
    bool isFilled( int x ){
        return line[x] != NONE;
    }
    void blink( int y );
    void show( int y );
    void hide( int y );
    bool isFilled();
};



#endif