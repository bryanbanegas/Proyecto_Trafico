#ifndef INTERSECCION_H
#define INTERSECCION_H

#include <string>
using namespace std;

class Interseccion{
public:
    string direcciones[2];
    int id, x, y, xTemporal, yTemporal;
public:
    bool disponible=true;
    bool semaforo=false;
    string color="green";
    
    Interseccion(string direccion[2], int iD, int xpos, int ypos, int sizeRect){
        direcciones[0]=direccion[0];
        direcciones[1]=direccion[1];
        id=iD; 
        x=xpos; 
        y=ypos;
        xTemporal=xpos/(sizeRect*10);
        yTemporal=ypos/(sizeRect*10);
    }
};

#endif