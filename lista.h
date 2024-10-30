#include "vehiculo.h"

class Lista{
protected:
    Vehiculo *listaDeVehiculos;
    Lista *siguiente;
public:
    Lista():listaDeVehiculos(nullptr), siguiente(nullptr){}

    Lista(int id, string direccion, float velocidad, SDL_Renderer *ren, int x, int y){
        listaDeVehiculos=new Vehiculo(id,direccion,velocidad,ren,x,y);
        siguiente=nullptr;
    }

    void agregar(int id, string direccion, float velocidad, SDL_Renderer *ren, int x, int y){
        Lista *nuevoVehiculo=new Lista(id,direccion,velocidad,ren,x,y);
        if(listaDeVehiculos==nullptr){
            listaDeVehiculos=nuevoVehiculo->listaDeVehiculos;
            siguiente=nuevoVehiculo->siguiente;
        }else{
            Lista *actual=this;
            while(actual->siguiente!=nullptr){
                actual=actual->siguiente;
            }
            actual->siguiente=nuevoVehiculo;
        }
    }

    void eliminar(int id){
        Lista* actual=this;
        if(listaDeVehiculos!=nullptr&&listaDeVehiculos->getID()==id){
            Lista *temporal=siguiente;
            listaDeVehiculos=temporal->listaDeVehiculos;
            siguiente=temporal->siguiente;
            temporal->listaDeVehiculos=nullptr;
            temporal->siguiente=nullptr;
            delete temporal;
            return;
        }
        while(actual->siguiente!=nullptr){
            if (actual->siguiente->listaDeVehiculos->getID()==id) {
                Lista* eliminar=actual->siguiente;
                actual->siguiente=eliminar->siguiente;
                delete eliminar->listaDeVehiculos;
                delete eliminar;
                return;
            }
            actual=actual->siguiente;
        }
    }

    void clear(SDL_Renderer *renderer){
        Lista* actual=this;
        while(actual!=nullptr){
            if(actual->listaDeVehiculos!=nullptr){
                SDL_Rect rect=actual->listaDeVehiculos->getRect();
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(renderer,0,0,0,0);
                SDL_RenderFillRect(renderer,&rect);
            }
            actual=actual->siguiente;
        }
    }
    
    void move(Grafo ciudad){
        Lista* actual=this;
        while(actual!=nullptr){
            actual->listaDeVehiculos->movimiento(ciudad);
            actual=actual->siguiente;
        }
    }

    void render(){
        Lista* actual=this;
        while(actual!=nullptr){
            actual->listaDeVehiculos->Render();
            actual=actual->siguiente;
        }
    }
};