#include <SDL2/SDL.h>      
#include <iostream>         
#include <cstdlib>       
using namespace std;

class Carro {
public:
    Carro(string direccion, float velocidad, SDL_Renderer *ren, int x, int y);
    ~Carro();

    void movimiento();
    void Render();

private:
    string direccion;
    int xpos;
    int ypos;
    SDL_Rect srcRect;
    SDL_Renderer *renderer;
};