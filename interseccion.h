#ifndef INTERSECCION_H
#define INTERSECCION_H

#include <string>
using namespace std;

class Interseccion{
public:
    string direcciones[2];
    int id, x, y;
public:
    Interseccion(string direccion[2], int iD, int xpos, int ypos){
        direcciones[0]=direccion[0];
        direcciones[1]=direccion[1];
        id=iD; 
        x=xpos; 
        y=ypos;
    }
};

#endif