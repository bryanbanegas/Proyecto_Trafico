#include "lista.h"
#include "grafo.h"
#include "arbol.h"

Lista vehiculos;
Arbol arbolDeClimas;
Grafo ciudad;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *backgroundTexture;
bool build=true;
int cantidadCalles=-1,cantidadIntersecciones=-1;

//Hola, Analfabeto. Suerte!! xoxo (jenn)

void buildCity(Grafo &ciudad, SDL_Renderer *renderer){
    if(build){
        string direcciones1[2]={"right","down"};
        string direcciones2[2]={"right","up"};
        string direcciones3[2]={"right","down"};

        ciudad.agregarInterseccion(direcciones1,0,0,100);
        ciudad.agregarInterseccion(direcciones1,1,100,100);
        ciudad.agregarInterseccion(direcciones2,2,200,100);
        ciudad.agregarInterseccion(direcciones3,3,300,100);
        ciudad.agregarInterseccion(direcciones1,4,100,200);
        ciudad.agregarInterseccion(direcciones2,5,200,200);
        ciudad.agregarInterseccion(direcciones3,6,300,200);
        ciudad.agregarInterseccion(direcciones1,7,100,300);
        ciudad.agregarInterseccion(direcciones2,8,200,300);
        ciudad.agregarInterseccion(direcciones3,9,300,300);
    
        vehiculos.agregar(1,"right",40, renderer, 0, 100);
        vehiculos.agregar(2,"right",60, renderer, 100, 300);
    
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

        arbolDeClimas.agregar("Climas",70);
        arbolDeClimas.agregar("Dia Soleado",50);
        arbolDeClimas.agregar("Tormenta",110);
        arbolDeClimas.agregar("Nevada",80);
        arbolDeClimas.agregar("Tormenta Electrica",150);

        build=false;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for(Calle *calle:ciudad.calles){
        cantidadCalles++;
        SDL_RenderDrawLine(renderer, calle->origen->x+5, calle->origen->y+5, calle->destino->x+5, calle->destino->y+5);
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for(auto &pair:ciudad.intersecciones){
        cantidadIntersecciones++;
        Interseccion *inter=pair.second;
        SDL_Rect rect={inter->x, inter->y, 10, 10};
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect button={700, 0, 50, 50};
    SDL_RenderFillRect(renderer, &button);
}

void createBackgroundTexture(){
    backgroundTexture=SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,  1000, 1000);
    
    SDL_SetRenderTarget(renderer, backgroundTexture);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    cantidadCalles=0;
    cantidadIntersecciones=0;
    buildCity(ciudad,renderer);

    SDL_SetRenderTarget(renderer, NULL);
}

void botonAgregarCalle(){
    int n=rand(), num=cantidadIntersecciones+1, limite=0;
    bool yaCreo=false,crearCalle,terminar=false,crearDerecha=true,crearIzquierda=true,crearArriba=true,crearAbajo=true;

    while(!terminar){
        limite++;
        n=rand()%cantidadIntersecciones;
        if(n<cantidadIntersecciones&&ciudad.intersecciones.count(n)>0){
            for(auto &pair:ciudad.intersecciones){
                Interseccion *inter=pair.second;
                if(ciudad.intersecciones.at(n)->x==0){
                    crearIzquierda=false;
                }
                if(ciudad.intersecciones.at(n)->x+100==inter->x&&ciudad.intersecciones.at(n)->y==inter->y){
                    crearDerecha=false;
                    crearCalle=true;
                    for(Calle *calle:ciudad.calles){
                        if(calle->origen==ciudad.intersecciones.at(n)&&calle->destino==inter||
                        calle->origen==inter&&calle->destino==ciudad.intersecciones.at(n)){
                            crearCalle=false;
                            break;
                        }
                    }
                    if(crearCalle){
                        ciudad.agregarCalle(ciudad.intersecciones.at(n)->id,inter->id);
                        yaCreo=true;
                    }
                }
                if(ciudad.intersecciones.at(n)->x-100==inter->x&&ciudad.intersecciones.at(n)->y==inter->y){
                    crearIzquierda=false;
                    crearCalle=true;
                    for(Calle *calle:ciudad.calles){
                        if(calle->origen==ciudad.intersecciones.at(n)&&calle->destino==inter||
                        calle->origen==inter&&calle->destino==ciudad.intersecciones.at(n)){
                            crearCalle=false;
                            break;
                        }
                    }
                    if(crearCalle){
                        ciudad.agregarCalle(ciudad.intersecciones.at(n)->id,inter->id);
                        yaCreo=true;
                    }
                }
                if(ciudad.intersecciones.at(n)->x==inter->x&&ciudad.intersecciones.at(n)->y+100==inter->y){
                    crearAbajo=false;
                    crearCalle=true;
                    for(Calle *calle:ciudad.calles){
                        if(calle->origen==ciudad.intersecciones.at(n)&&calle->destino==inter||
                        calle->origen==inter&&calle->destino==ciudad.intersecciones.at(n)){
                            crearCalle=false;
                            break;
                        }
                    }
                    if(crearCalle){
                        ciudad.agregarCalle(ciudad.intersecciones.at(n)->id,inter->id);
                        yaCreo=true;
                    }
                }
            }
            if(!yaCreo){
                if(crearDerecha){
                    ciudad.agregarInterseccion(ciudad.intersecciones.at(n)->direcciones,num,ciudad.intersecciones.at(n)->x+100,ciudad.intersecciones.at(n)->y);
                    ciudad.agregarCalle(ciudad.intersecciones.at(n)->id,num);
                    terminar=true;
                }else if(crearIzquierda){
                    ciudad.agregarInterseccion(ciudad.intersecciones.at(n)->direcciones,num,ciudad.intersecciones.at(n)->x-100,ciudad.intersecciones.at(n)->y);
                    ciudad.agregarCalle(ciudad.intersecciones.at(n)->id,num);
                    terminar=true;
                }else if(crearAbajo){
                    ciudad.agregarInterseccion(ciudad.intersecciones.at(n)->direcciones,num,ciudad.intersecciones.at(n)->x,ciudad.intersecciones.at(n)->y+100);
                    ciudad.agregarCalle(ciudad.intersecciones.at(n)->id,num);
                    terminar=true;
                }
            }
        }
        if(limite==100){
            terminar=true;
            cout<<"Se llego al limite."<<endl;
        }
    }

    
    createBackgroundTexture();
}

int main(int argc, char *argv[]) {
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        cout<<"Error: "<<SDL_GetError()<<endl;
        return -1;
    }

    window=SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_SHOWN);
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

    string climaActual="Dia Soleado";
    bool run=true;
    SDL_Event event;
    while(run){
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                run=false;
            }else if(event.type==SDL_MOUSEBUTTONDOWN){
                int x,y;
                SDL_GetMouseState(&x,&y);
                if(x>=700&&x<=750&&y>=0&&y<=50){
                    botonAgregarCalle();
                }
            }
        }

        SDL_Delay(arbolDeClimas.getRangoDeClima(climaActual));
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