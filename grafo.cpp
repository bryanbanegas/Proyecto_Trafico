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

string Grafo::calcularDireccion(int nodoActual, int vecino){
    if(intersecciones[vecino]->y<intersecciones[nodoActual]->y){
        return "up";
    }
    if(intersecciones[vecino]->y>intersecciones[nodoActual]->y){
        return "down";
    }
    if(intersecciones[vecino]->x>intersecciones[nodoActual]->x){
        return "right";
    }
    if(intersecciones[vecino]->x<intersecciones[nodoActual]->x){
        return "left";
    }
    return "";
}

int Grafo::dijkstra(int origen, int destino, unordered_map<int, int> &padres){
    unordered_map<int, int> distancias;
    int nodoActual, vecino;
    string direccion;
    for(auto& Interseccion:intersecciones){
        distancias[Interseccion.first]=numeric_limits<int>::max();
    }
    distancias[origen]=0;
    queue<int> siguiente;
    siguiente.push(origen);
    while(!siguiente.empty()){
        nodoActual=siguiente.front();
        siguiente.pop();
        for(auto& calle:calles){
            if(calle->origen->id==nodoActual){
                vecino=calle->destino->id;
                direccion=calcularDireccion(nodoActual,vecino);
                if(intersecciones[nodoActual]->direcciones[0]!=direccion&&intersecciones[nodoActual]->direcciones[1]!=direccion){
                    continue;
                }

                if(distancias[vecino]>distancias[nodoActual]+1){
                    distancias[vecino]=distancias[nodoActual]+1;
                    siguiente.push(vecino);
                    padres[vecino]=nodoActual;
                }
            }
        }
    }

    if(distancias[destino]==numeric_limits<int>::max()){
        return -1;
    }
    return distancias[destino];
}

vector<int> Grafo::reconstruirCamino(int origen, int destino, const unordered_map<int, int> &padres){
    vector<int> camino;
    int nodo=destino;
    while(nodo!=origen){
        camino.push_back(nodo);
        if(padres.find(nodo)==padres.end()){
            return {};
        }
        nodo=padres.at(nodo);
    }
    camino.push_back(origen);
    reverse(camino.begin(), camino.end());
    return camino;
}