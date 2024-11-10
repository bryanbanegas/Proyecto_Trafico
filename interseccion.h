#ifndef INTERSECCION_H
#define INTERSECCION_H

#include <string>
using namespace std;

class Interseccion{
public:
    string direcciones[2];
    int id, x, y, cantidadCalles;
public:
    Interseccion(string direccion[2], int iD, int xpos, int ypos, int cantidad){
        direcciones[0]=direccion[0];
        direcciones[1]=direccion[1];
        id=iD; 
        x=xpos; 
        y=ypos;
        cantidadCalles=cantidad;
    }

    void calleAgregada(){
        cantidadCalles++;
    }

    int getCantidadCalles(){
        return cantidadCalles;
    }
};

#endif