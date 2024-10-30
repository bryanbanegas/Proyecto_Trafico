#ifndef VEHICULO_H
#define VEHICULO_H

#include <SDL2/SDL.h>      
#include <iostream>         
#include <cstdlib>    
#include "grafo.h"   
using namespace std;

class Vehiculo {
private:
    int id;
    string direccion;
    float velocidad;
    int xpos, ypos;
    SDL_Rect srcRect;
    SDL_Renderer *renderer;
public:
    Vehiculo *siguiente=nullptr;

    Vehiculo(int id, string direccion, float velocidad, SDL_Renderer *ren, int x, int y);
    ~Vehiculo();

    void movimiento(Grafo ciudad);
    void Render();
    int getID();
};

#endif