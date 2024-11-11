#include "vehiculo.h"

Vehiculo::Vehiculo(int id, string direccion, float velocidad, SDL_Renderer *rend, int x, int y)
    : id(id), direccion(direccion), velocidad(velocidad), renderer(rend), xpos(x), ypos(y){
    srcRect.x=xpos;
    srcRect.y=ypos;
    srcRect.w=32;
    srcRect.h=32;
}

Vehiculo::~Vehiculo() {}

void Vehiculo::Clear(){
    SDL_SetRenderDrawColor(renderer,255,0,0,0);
    SDL_RenderFillRect(renderer, &srcRect);
}

void Vehiculo::Render(){
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_RenderFillRect(renderer, &srcRect);
}

void Vehiculo::movimiento(Grafo ciudad){
    string dir[2];
    int n=rand(),contar=-1;
    bool terminar=false;
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
            for(auto &pair2:ciudad.intersecciones){
                Interseccion *inter2=pair2.second;
                if(srcRect.x+100==inter2->x&&srcRect.y==inter2->y){
                    if(inter->direcciones[0]=="right"||inter->direcciones[1]=="right"){
                        contar++;
                        dir[contar]="right";
                    }
                }
                if(srcRect.x-100==inter2->x&&srcRect.y==inter2->y){
                    if(inter->direcciones[0]=="left"||inter->direcciones[1]=="left"){
                        contar++;
                        dir[contar]="left";
                    }
                }
                if(srcRect.x==inter2->x&&srcRect.y-100==inter2->y){
                    if(inter->direcciones[0]=="up"||inter->direcciones[1]=="up"){
                        contar++;
                        dir[contar]="up";
                    }
                }
                if(srcRect.x==inter2->x&&srcRect.y+100==inter2->y){
                    if(inter->direcciones[0]=="down"||inter->direcciones[1]=="down"){
                        contar++;
                        dir[contar]="down";                        
                    }
                }
            }
            if(contar>-1){
                n=rand()%(contar+1);
                direccion=dir[n];
            }else{
                direccion="destino";              
            }
        }
    }
}

int Vehiculo::getID(){
    return id;
}

SDL_Rect& Vehiculo::getRect(){
    return srcRect;
}