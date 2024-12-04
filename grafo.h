#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <queue>
#include "interseccion.h"
#include "calle.h"

class Grafo{
public:
    unordered_map<int, Interseccion*> intersecciones;
    vector<Calle*> calles;
    int distancia;

    void calcularDistancia();
    void agregarInterseccion(string direcciones[2], int id, int x, int y);
    void agregarCalle(int idOrigen, int idDestino);
    int dijkstra(int origen, int destino, unordered_map<int, int> &padres);
    vector<int> reconstruirCamino(int idOrigen, int idDestino, const unordered_map<int, int> &padres);
    string calcularDireccion(int nodoActual, int vecio);
};

#endif