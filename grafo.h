#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <unordered_map>
#include "interseccion.h"
#include "calle.h"

class Grafo{
public:
    unordered_map<int, Interseccion*> intersecciones;
    vector<Calle*> calles;

    void agregarInterseccion(string direcciones[2], int id, int x, int y);
    void agregarCalle(int idOrigen, int idDestino);
};

#endif