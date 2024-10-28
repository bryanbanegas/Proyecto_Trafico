#include "vehiculo.h"

Vehiculo::Vehiculo(string direccion, float velocidad, SDL_Renderer *rend, int x, int y)
    : direccion(direccion), renderer(rend), xpos(x), ypos(y){
    srcRect.x=xpos;
    srcRect.y=ypos;
    srcRect.w=32;
    srcRect.h=32;
}

Vehiculo::~Vehiculo() {}

void Vehiculo::movimiento(Grafo ciudad){
    int n=rand();

    if(direccion=="right"){
        srcRect.x++;
    }else if(direccion=="left"){
        srcRect.x--;
    }else if(direccion=="up"){
        srcRect.y--;
    }else if(direccion=="down"){
        srcRect.y++;
    }

    for(auto &pair:ciudad.intersecciones){
        Interseccion *inter=pair.second;
        if(srcRect.x==inter->x&&srcRect.y==inter->y){
            n=rand()%2;
            direccion=inter->direcciones[n];
        }
    }
}

void Vehiculo::Render(){
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderFillRect(renderer,&srcRect);
}