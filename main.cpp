#include "carro.h"

Carro *carro;
Carro *bloque;

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

    bloque=new Carro("right",230, renderer, 500, 30);
    carro=new Carro("right",230, renderer, 0, 30);

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

        bloque->Render();
        carro->Render();
        carro->movimiento();

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    delete carro;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

/*
thread t1(task,&square);
    
    t1.join();*/

