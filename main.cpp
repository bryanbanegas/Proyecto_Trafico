#include "lista.h"
#include "grafo.h"

Lista vehiculos;
Grafo ciudad;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *backgroundTexture;
int cantidadCalles=0;

void buildCity(Grafo &ciudad, SDL_Renderer *renderer){
    string direcciones1[2]={"right","down"};
    string direcciones2[2]={"right","right"};
    string direcciones3[2]={"down","down"};
    string direcciones4[2]={"right","up"};
    string direcciones5[2]={"destino","destino"};

    ciudad.agregarInterseccion(direcciones2,0,0,100);
    ciudad.agregarInterseccion(direcciones1,1,100,100);
    ciudad.agregarInterseccion(direcciones2,2,300,100);
    ciudad.agregarInterseccion(direcciones3,3,500,100);
    ciudad.agregarInterseccion(direcciones1,4,100,300);
    ciudad.agregarInterseccion(direcciones4,5,300,300);
    ciudad.agregarInterseccion(direcciones3,6,500,300);
    ciudad.agregarInterseccion(direcciones2,7,100,500);
    ciudad.agregarInterseccion(direcciones4,8,300,500);
    ciudad.agregarInterseccion(direcciones5,9,500,500);
    
    vehiculos.agregar(1,"right",230, renderer, 0, 100);
    
    ciudad.agregarCalle(0,1);
    ciudad.agregarCalle(1,2);
    ciudad.agregarCalle(1,4);
    ciudad.agregarCalle(2,3);
    ciudad.agregarCalle(2,5);
    ciudad.agregarCalle(3,6);
    ciudad.agregarCalle(4,5);
    ciudad.agregarCalle(4,7);
    ciudad.agregarCalle(5,6);
    ciudad.agregarCalle(5,8);
    ciudad.agregarCalle(6,9);
    ciudad.agregarCalle(7,8);
    ciudad.agregarCalle(8,9);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for(Calle *calle:ciudad.calles){
        SDL_RenderDrawLine(renderer, calle->origen->x+5, calle->origen->y+5, calle->destino->x+5, calle->destino->y+5);
        cantidadCalles++;
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for(auto &pair:ciudad.intersecciones){
        Interseccion *inter=pair.second;
        SDL_Rect rect={inter->x, inter->y, 10, 10};
        SDL_RenderFillRect(renderer, &rect);
    }
}

void botonAgregarCalle(){
    int n=rand()%cantidadCalles;
    bool terminar=false;

    

}

void createBackgroundTexture(){
    backgroundTexture=SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 800, 600);
    
    SDL_SetRenderTarget(renderer, backgroundTexture);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    buildCity(ciudad,renderer);

    SDL_SetRenderTarget(renderer, NULL);
}


int main(int argc, char *argv[]) {
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        cout<<"Error: "<<SDL_GetError()<<endl;
        return -1;
    }

    window=SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if(!window){
        cout<<"Error: "<<SDL_GetError()<<endl;
        SDL_DestroyRenderer(nullptr);
        SDL_DestroyWindow(nullptr);
        SDL_Quit();
        return -1;
    }

    renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        cout<<"Error: "<<SDL_GetError()<<endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    createBackgroundTexture();

    bool run=true;
    SDL_Event event;
    while(run){
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                run=false;
            }
        }

        vehiculos.move(ciudad);

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        vehiculos.render();

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}