#include "lista.h"
#include "grafo.h"

Lista vehiculos;
Grafo ciudad;

class Proyect{
private:
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *backgroundTexture;
int xpos, ypos, size, speed;

void buildCity(Grafo &ciudad, SDL_Renderer *renderer){
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
}

void createBackgroundTexture(){
    backgroundTexture=SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 640, 480);
    SDL_SetRenderTarget(renderer, backgroundTexture);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    string direcciones1[2]={"right","down"};
    string direcciones2[2]={"right","right"};
    string direcciones3[2]={"down","down"};
    string direcciones4[2]={"right","up"};
    string direcciones5[2]={"destino","destino"};

    ciudad.agregarInterseccion(direcciones1,0,100,100);
    ciudad.agregarInterseccion(direcciones2,1,300,100);
    ciudad.agregarInterseccion(direcciones3,2,500,100);
    ciudad.agregarInterseccion(direcciones1,3,100,300);
    ciudad.agregarInterseccion(direcciones4,4,300,300);
    ciudad.agregarInterseccion(direcciones3,5,500,300);
    ciudad.agregarInterseccion(direcciones2,6,100,500);
    ciudad.agregarInterseccion(direcciones4,7,300,500);
    ciudad.agregarInterseccion(direcciones5,8,500,500);
    
    vehiculos.agregar(1,"down",230, renderer, 100, 100);
    
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

    buildCity(ciudad,renderer);

    SDL_SetRenderTarget(renderer, NULL);
}

void movement(){
    vehiculos.move(ciudad);
}

void Render(){
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    vehiculos.agregar(1,"down",20,renderer,xpos,ypos);
    vehiculos.render();

    SDL_RenderPresent(renderer);
}

void cleanup(){
    if(backgroundTexture)SDL_DestroyTexture(backgroundTexture);
    if(renderer)SDL_DestroyRenderer(renderer);
    if(window)SDL_DestroyWindow(window);
    SDL_Quit();
}

public:
    Proyect():window(nullptr), renderer(nullptr), backgroundTexture(nullptr), 
    xpos(50), ypos(50), size(30), speed(2){} 

    ~Proyect(){
        cleanup();
    }

    bool init(){
        if(SDL_Init(SDL_INIT_VIDEO)!=0){
            cout<<"Error: "<<SDL_GetError()<<endl;
            return false;
        }

        window=SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
        if(!window){
            cout<<"Error: "<<SDL_GetError()<<endl;
            SDL_DestroyRenderer(nullptr);
            SDL_DestroyWindow(nullptr);
            SDL_Quit();
            return false;
        }

        renderer=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(!renderer){
            cout<<"Error: "<<SDL_GetError()<<endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }

        createBackgroundTexture();

        return true;
    }

    void run(){
        bool run=true;
        SDL_Event event;
        while(run){
            while(SDL_PollEvent(&event)){
                if(event.type==SDL_QUIT){
                    run=false;
                }
            }

            movement();
            Render();
            SDL_Delay(16);
        }
    }
};

int main(int argc, char *argv[]) {
    Proyect proyect;

    if(!proyect.init()){
        return -1;
    }

    proyect.run();
    return 0;
}

/*int main(int argc, char *argv[]) 
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
    

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    
    vehiculos.render();

    SDL_RenderPresent(renderer);
    
    SDL_Event event;
    bool run=true,construir=true;
    while(run){
        if(SDL_PollEvent(&event)){
            if(SDL_QUIT==event.type){
                run=false;
            }
        }
        

        vehiculos.clear(renderer);
        vehiculos.move(ciudad);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    for(auto &pair:ciudad.intersecciones)delete pair.second;
    for(Calle *calle:ciudad.calles)delete calle;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}*/