#include "vehiculo.h"
#include "grafo.h"

Vehiculo *carro;
Grafo ciudad;

void construirCiudad(Grafo &ciudad, SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for(Calle *calle:ciudad.calles){
        SDL_RenderDrawLine(renderer, calle->origen->x+5, calle->origen->y+5, calle->destino->x+5, calle->destino->y+5);
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for(auto &pair:ciudad.intersecciones){
        Interseccion *inter=pair.second;
        SDL_Rect rect={inter->x, inter->y, 10, 10};
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[]) 
{
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        cout<<"Error: "<<SDL_GetError()<<endl;
        return 1;
    }

    SDL_Window *window=SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    if(!window){
        cout<<"Error: "<<SDL_GetError()<<endl;
        SDL_DestroyRenderer(nullptr);
        SDL_DestroyWindow(nullptr);
        SDL_Quit();

        return 1;
    }

    SDL_Renderer *renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!renderer){
        cout<<"Error: "<<SDL_GetError()<<endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    //bloque=new Vehiculo("right",230, renderer, 500, 30);
    string direcciones1[2];
    string direcciones2[2];
    string direcciones3[2];
    string direcciones4[2];
    string direcciones5[2];
    string direcciones6[2];
    direcciones1[0]="right";
    direcciones1[1]="down";
    direcciones2[0]="right";
    direcciones2[1]="right";
    direcciones3[0]="down";
    direcciones3[1]="down";
    direcciones4[0]="right";
    direcciones4[1]="up";
    direcciones5[0]="destino";
    direcciones5[1]="destino";
    direcciones6[0]="destino";
    direcciones6[1]="destino";

    ciudad.agregarInterseccion(direcciones1,0,100,100);
    ciudad.agregarInterseccion(direcciones2,1,300,100);
    ciudad.agregarInterseccion(direcciones3,2,500,100);
    ciudad.agregarInterseccion(direcciones1,3,100,300);
    ciudad.agregarInterseccion(direcciones4,4,300,300);
    ciudad.agregarInterseccion(direcciones3,5,500,300);
    ciudad.agregarInterseccion(direcciones2,6,100,500);
    ciudad.agregarInterseccion(direcciones4,7,300,500);
    ciudad.agregarInterseccion(direcciones6,8,500,500);
    
    carro=new Vehiculo("down",230, renderer, 100, 100);
    
    ciudad.agregarCalle(0,1);
    ciudad.agregarCalle(0,3);
    ciudad.agregarCalle(1,4);
    ciudad.agregarCalle(1,2);
    ciudad.agregarCalle(2,5);
    ciudad.agregarCalle(3,6);
    ciudad.agregarCalle(3,4);
    ciudad.agregarCalle(4,7);
    ciudad.agregarCalle(4,5);
    ciudad.agregarCalle(5,8);
    ciudad.agregarCalle(6,7);
    ciudad.agregarCalle(7,8);

    SDL_Event event;
    bool run=true;
    while(run){
        if(SDL_PollEvent(&event)){
            if(SDL_QUIT==event.type){
                run=false;
            }
        }

        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        construirCiudad(ciudad, renderer);
        
        carro->Render();
        carro->movimiento(ciudad);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    for(auto &pair:ciudad.intersecciones)delete pair.second;
    for(Calle *calle:ciudad.calles)delete calle;
    delete carro;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}