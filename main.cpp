#include <stdexcept>
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
int sizeRect=10;
float delayPorZoom=10;
//Hola, Analfabeto. Suerte!! xoxo (jenn)

void buildCity(Grafo &ciudad, SDL_Renderer *renderer){
    if(build){
        string direcciones1[2]={"right","up"};
        string direcciones2[2]={"right","down"};
        string direcciones3[2]={"left","up"};
        string direcciones4[2]={"left","down"};

        ciudad.agregarInterseccion(direcciones1,0,0,100);
        ciudad.agregarInterseccion(direcciones2,1,100,100);
        ciudad.agregarInterseccion(direcciones1,2,200,100);
        ciudad.agregarInterseccion(direcciones2,3,300,100);

        ciudad.agregarInterseccion(direcciones4,4,100,200);
        ciudad.agregarInterseccion(direcciones3,5,200,200);
        ciudad.agregarInterseccion(direcciones4,6,300,200);

        ciudad.agregarInterseccion(direcciones2,7,100,300);
        ciudad.agregarInterseccion(direcciones1,8,200,300);
        ciudad.agregarInterseccion(direcciones2,9,300,300);

        vector<int> sinCamino;
        vehiculos.agregar("right",false, renderer, 100, 100, sinCamino);
    
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
        ciudad.calcularDistancia();
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for(Calle *calle:ciudad.calles){
        
        SDL_RenderDrawLine(renderer, calle->origen->x+sizeRect/2, calle->origen->y+sizeRect/2, calle->destino->x+sizeRect/2, calle->destino->y+sizeRect/2);
    }

    Interseccion *inter;
    int n=0;
    for(auto &pair:ciudad.intersecciones){
        inter=pair.second;
        n=inter->y/100;
        if(n%2!=0&&inter->x!=0){
            inter->semaforo=true;
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for(auto &pair:ciudad.intersecciones){
        inter=pair.second;
        SDL_Rect rect={inter->x, inter->y, sizeRect, sizeRect};
        if(!inter->semaforo){
            SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
        }else{
            if(inter->color=="red"){
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            }else{
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            }
        }
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect button;
    button={700, 0, 50, 50};
    SDL_RenderFillRect(renderer, &button);
    button={700, 100, 50, 50};
    SDL_RenderFillRect(renderer, &button);
    button={700, 200, 50, 50};
    SDL_RenderFillRect(renderer, &button);
    button={700, 300, 50, 50};
    SDL_RenderFillRect(renderer, &button);
    button={760, 300, 50, 50};
    SDL_RenderFillRect(renderer, &button);
}
double calculateDistance(int x1, int y1, int x2, int y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
int blockIntersection(int x, int y) {
    Interseccion *nearestInter, *inter;
    double minDistance = std::numeric_limits<double>::max();

    for (auto &pair:ciudad.intersecciones) {
        inter=pair.second;
        double distance=calculateDistance(x, y, inter->x, inter->y);
        if (distance<minDistance) {
            minDistance=distance;
            nearestInter=inter;
        }
    }
    
    for (auto &pair:ciudad.intersecciones) {
        inter=pair.second;
        if (inter->id==nearestInter->id) {
            nearestInter->disponible=false;
            cout<<"Choque que en la Interseccion: "<<nearestInter->id<<endl;
            return nearestInter->id;
        }
    }
    return 0;
}
void addVehiculo(){
    int n=0;
    vector<int> sincamino;
    bool terminar=false;
    while(!terminar){
        n=rand()%ciudad.intersecciones.size();
        if(ciudad.intersecciones.at(n)->disponible){
            if(!vehiculos.collision(ciudad.intersecciones.at(n)->x,ciudad.intersecciones.at(n)->y)){
                vehiculos.agregar(ciudad.intersecciones.at(n)->direcciones[0],false,renderer,ciudad.intersecciones.at(n)->x,ciudad.intersecciones.at(n)->y,sincamino);
                terminar=true;
                cout<<"Se creo un vehiculo."<<endl;
            }
        }
    }
}
void createBackgroundTexture(){
    backgroundTexture=SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,  1000, 1000);
    
    SDL_SetRenderTarget(renderer, backgroundTexture);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    buildCity(ciudad,renderer);

    SDL_SetRenderTarget(renderer, NULL);
}
void addCalle(){
    int n=0, num=ciudad.intersecciones.size(), limite=0;
    bool yaCreo=false,crearCalle,terminar=false,crearDerecha=true,crearIzquierda=true,crearArriba=true,crearAbajo=true;

    while(!terminar){
        limite++;
        n=rand()%ciudad.intersecciones.size();
        if(n<ciudad.intersecciones.size()&&ciudad.intersecciones.count(n)>0){
            for(auto &pair:ciudad.intersecciones){
                Interseccion *inter=pair.second;
                if(ciudad.intersecciones.at(n)->x==0){
                    crearIzquierda=false;
                }
                if(ciudad.intersecciones.at(n)->x+ciudad.distancia==inter->x&&ciudad.intersecciones.at(n)->y==inter->y){
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
                if(ciudad.intersecciones.at(n)->x-ciudad.distancia==inter->x&&ciudad.intersecciones.at(n)->y==inter->y){
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
                if(ciudad.intersecciones.at(n)->x==inter->x&&ciudad.intersecciones.at(n)->y+ciudad.distancia==inter->y){
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
                    string dir[2];
                    if(ciudad.intersecciones.at(n)->direcciones[1]=="up"){
                        dir[1]="down";
                    }else if(ciudad.intersecciones.at(n)->direcciones[1]=="down"){
                        dir[1]="up";
                    }
                    dir[0]=ciudad.intersecciones.at(n)->direcciones[0];
                    ciudad.agregarInterseccion(dir,num,ciudad.intersecciones.at(n)->x+ciudad.distancia,ciudad.intersecciones.at(n)->y);
                    ciudad.agregarCalle(ciudad.intersecciones.at(n)->id,num);
                    terminar=true;
                }else if(crearIzquierda){
                    string dir[2];
                    if(ciudad.intersecciones.at(n)->direcciones[1]=="up"){
                        dir[1]="down";
                    }else if(ciudad.intersecciones.at(n)->direcciones[1]=="down"){
                        dir[1]="up";
                    }
                    dir[0]=ciudad.intersecciones.at(n)->direcciones[0];
                    ciudad.agregarInterseccion(dir,num,ciudad.intersecciones.at(n)->x-ciudad.distancia,ciudad.intersecciones.at(n)->y);
                    ciudad.agregarCalle(ciudad.intersecciones.at(n)->id,num);
                    terminar=true;
                }else if(crearAbajo){
                    string dir[2];
                    if(ciudad.intersecciones.at(n)->direcciones[0]=="right"){
                        dir[0]="left";
                    }else if(ciudad.intersecciones.at(n)->direcciones[0]=="left"){
                        dir[0]="right";
                    }
                    dir[1]=ciudad.intersecciones.at(n)->direcciones[1];
                    ciudad.agregarInterseccion(dir,num,ciudad.intersecciones.at(n)->x,ciudad.intersecciones.at(n)->y+ciudad.distancia);
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
    Interseccion *inter;
    int contar=0;
    while(run){
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT){
                run=false;
            }else if(event.type==SDL_MOUSEBUTTONDOWN){
                int x,y;
                SDL_GetMouseState(&x,&y);
                if(x>=700&&x<=750&&y>=0&&y<=50){
                    addVehiculo();
                }
                if(x>=700&&x<=750&&y>=100&&y<=150){
                    addCalle();
                }
                if(x>=700&&x<=750&&y>=200&&y<=250){
                    addVehiculo();
                }
                if(x>=700&&x<=750&&y>=300&&y<=350){
                    int mult, n=sizeRect;
                    sizeRect--;
                    for(auto &pair:ciudad.intersecciones){
                        inter=pair.second;
                        mult=sizeRect*10;
                        inter->x=inter->xTemporal*mult;
                        inter->y=inter->yTemporal*mult;
                    }
                    ciudad.calcularDistancia();
                    vehiculos.updatePos(n);
                    createBackgroundTexture();
                }
                if(x>=760&&x<=810&&y>=300&&y<=350){
                    int mult, n=-sizeRect;
                    sizeRect++;
                    for(auto &pair:ciudad.intersecciones){
                        inter=pair.second;
                        mult=sizeRect*10;
                        inter->x=inter->xTemporal*mult;
                        inter->y=inter->yTemporal*mult;
                    }
                    ciudad.calcularDistancia();
                    vehiculos.updatePos(n);
                    createBackgroundTexture();
                }
            }
        }

        SDL_Delay(arbolDeClimas.getRangoDeClima(climaActual)/sizeRect);
        vehiculos.move(ciudad,sizeRect);
        if(vehiculos.choque){
            int destino=blockIntersection(vehiculos.choqueX,vehiculos.choqueY);
            unordered_map<int, int> padres;
            int distancia=ciudad.dijkstra(0,destino,padres);
            if(destino!=-1){
                vector<int> camino=ciudad.reconstruirCamino(0,destino,padres);
                vehiculos.agregar("right", true, renderer, 0, 100, camino);
            }else{
                cout<<"no funciono"<<endl;
            }
            vehiculos.choque=false;
        }
        contar++;
        if(contar==100){
            for(auto &pair:ciudad.intersecciones){
                inter=pair.second;
                if(inter->semaforo){
                    if(inter->color=="green"){
                        inter->color="red";
                    }else{
                        inter->color="green";
                    }
                }
            }
            createBackgroundTexture();
            contar=0;
        }

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        vehiculos.render(sizeRect);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}