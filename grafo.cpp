#include "grafo.h"
#include <iostream>

void Grafo::agregarInterseccion(string direcciones[2], int id, int x, int y){
    intersecciones[id]=new Interseccion(direcciones,id,x,y);
}

void Grafo::agregarCalle(int origen, int destino){
    Interseccion *origin=intersecciones[origen];
    Interseccion *destiny=intersecciones[destino];
    Calle *nuevaCalle=new Calle(origin, destiny);
    calles.push_back(nuevaCalle);
}