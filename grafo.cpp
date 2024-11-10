#include "grafo.h"
#include <iostream>

void Grafo::agregarInterseccion(string direcciones[2], int id, int x, int y){
    intersecciones[id]=new Interseccion(direcciones,id,x,y,0);
}

void Grafo::agregarCalle(int origen, int destino){
    Interseccion *origin=intersecciones[origen];
    origin->calleAgregada();
    Interseccion *destiny=intersecciones[destino];
    destiny->calleAgregada();
    Calle *nuevaCalle=new Calle(origin, destiny);
    calles.push_back(nuevaCalle);
}