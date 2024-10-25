#include "carro.h"

Carro::Carro(string direccion, float velocidad, SDL_Renderer *rend, int x, int y)
    : direccion(direccion), renderer(rend), xpos(x), ypos(y){
    srcRect.x=xpos;
    srcRect.y=ypos;
    srcRect.w=32;
    srcRect.h=32;
}

Carro::~Carro() {}

void Carro::movimiento(){
    int posX=500, posY=30, n=rand();

    string dirrecciones[2];
    dirrecciones[0]="right";
    dirrecciones[1]="down";

    if(direccion=="right"){
        srcRect.x+=5;
    }else if(direccion=="left"){
        srcRect.x--;
    }else if(direccion=="up"){
        srcRect.y--;
    }else if(direccion=="down"){
        srcRect.y+=5;
    }

    if(srcRect.x==posX&&srcRect.y==posY){
        n=rand()%2;
        direccion=dirrecciones[n];
    }

    if(srcRect.x==800){
        srcRect.x=0;
        srcRect.y=30;
        direccion="right";
    }else if(srcRect.y==600){
        srcRect.x=0;
        srcRect.y=30;
        direccion="right";
    }
}

void Carro::Render(){
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderFillRect(renderer,&srcRect);
}