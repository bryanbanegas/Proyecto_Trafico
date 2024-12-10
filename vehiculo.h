#ifndef VEHICULO_H
#define VEHICULO_H
#include <SDL2/SDL.h>     
#include <SDL2/SDL_ttf.h> 
#include <iostream>         
#include <cstdlib>
#include "grafo.h"   
 
using namespace std;

class Vehiculo {
private:
    int id;
    string direccion;
    SDL_Rect srcRect;
    SDL_Renderer *renderer;
public:
    Vehiculo *siguiente=nullptr;
    string originalDireccion;
    bool ambulance, move=true, moveForAmbulance=false, noChocar=false;
    const vector<int> camino;
    vector<int>  caminosRecorridos;
    int xpos, ypos, originalX, originalY;

    Vehiculo(int id, string direccion, bool ambulance, SDL_Renderer *ren, int x, int y, vector<int> camino);
    ~Vehiculo(){}

    string movimiento(const Grafo &ciudad,const int sizeRecrt);
    void Render(const int sizeRecrt);
    int getID();
    SDL_Rect getRect();
    string getDireccion();
    void setDireccion(string direc);
};

#endif