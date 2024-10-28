#include <SDL2/SDL.h>      
#include <iostream>         
#include <cstdlib>    
#include "grafo.h"   
using namespace std;

class Vehiculo {
public:
    Vehiculo(string direccion, float velocidad, SDL_Renderer *ren, int x, int y);
    ~Vehiculo();

    void movimiento(Grafo ciudad);
    void Render();

private:
    string direccion;
    int xpos;
    int ypos;
    SDL_Rect srcRect;
    SDL_Renderer *renderer;
};