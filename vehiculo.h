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
    SDL_Rect srcRect;
    SDL_Renderer *renderer;
public:
    int xpos, ypos;
    bool move=true;
    Vehiculo *siguiente=nullptr;

    Vehiculo(int id, string direccion, float velocidad, SDL_Renderer *ren, int x, int y);
    ~Vehiculo();

    void Clear();
    void Render();
    void movimiento(Grafo ciudad);
    int getID();
    SDL_Rect& getRect();
};

#endif