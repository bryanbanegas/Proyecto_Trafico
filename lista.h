#include "vehiculo.h"

class Lista{
protected:
    Vehiculo* listaDeVehiculos;
    int n=rand();
public:
    bool choque=false;
    int cantidadDeVehiculos=0, choqueX, choqueY, numeroDeChoques=0, id1=0, id2=0;
    Lista():listaDeVehiculos(nullptr){}
    ~Lista(){
        Vehiculo* actual=listaDeVehiculos;
        while(actual!=nullptr){
            Vehiculo* temporal=actual;
            actual=actual->siguiente;
            delete temporal;
        }
    }

    void agregar(string direccion, bool ambulance, SDL_Renderer *ren, int x, int y, vector<int> camino){
        cantidadDeVehiculos++;
        Vehiculo* nuevoVehiculo=new Vehiculo(cantidadDeVehiculos,direccion,ambulance,ren,x,y,camino);
        if(listaDeVehiculos==nullptr){
            listaDeVehiculos=nuevoVehiculo;
        }else{
            Vehiculo *actual=listaDeVehiculos;
            while(actual->siguiente!=nullptr){
                actual=actual->siguiente;
            }
            actual->siguiente=nuevoVehiculo;
        }
    }

    void eliminar(int id){
        Vehiculo* actual=listaDeVehiculos;
        if(listaDeVehiculos==nullptr){
            cout<<"No hay Vehiculos."<<endl;
        }else{
            if(listaDeVehiculos->getID()==id){
                Vehiculo *temporal=listaDeVehiculos;
                listaDeVehiculos=listaDeVehiculos->siguiente;
                delete temporal;
                cantidadDeVehiculos--;
                return;
            }
            Vehiculo *anterior=nullptr;
            while(actual!=nullptr&&actual->getID()!=id){
                anterior=actual;
                actual=actual->siguiente;
            }
            if(actual!=nullptr){
                anterior->siguiente=actual->siguiente;
                delete actual;
            }
        }
    }

    void clear(SDL_Renderer *renderer){
        Vehiculo* actual=listaDeVehiculos;
        while(actual!=nullptr){
            if(actual!=nullptr){
                SDL_Rect rect=actual->getRect();
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_SetRenderDrawColor(renderer,0,0,0,0);
                SDL_RenderFillRect(renderer,&rect);
            }
            actual=actual->siguiente;
        }
    }
    
    void move(Grafo &ciudad, int sizeRect){
        Vehiculo *actual=listaDeVehiculos;
        while(actual!=nullptr){
            if(!checkCollision(actual,ciudad)){
                if(actual->move){
                    if(actual->movimiento(ciudad,sizeRect)=="destino"){
                        if(actual->ambulance){
                            eliminar(actual->getID());
                            eliminar(id1);
                            eliminar(id2);
                            numeroDeChoques=0;
                            Interseccion *inter;
                            for(auto &pair:ciudad.intersecciones){
                                inter=pair.second;
                                inter->disponible=true;
                            }
                        }else{
                            eliminar(actual->getID());
                        }
                    }
                }
            }else{
                if(actual->move){
                    if(actual->movimiento(ciudad,sizeRect)=="destino"){
                        eliminar(actual->getID());
                    }
                }
            }
            actual=actual->siguiente;
        }
    }

    void render(int sizeRect){
        Vehiculo *actual=listaDeVehiculos;
        while(actual!=nullptr){
            actual->Render(sizeRect);
            actual=actual->siguiente;
        }
    }

    bool checkCollision(Vehiculo *srcRect,Grafo &ciudad){
        Vehiculo *actual=listaDeVehiculos;
        while(actual!=nullptr){
            if(srcRect->getID()!=actual->getID()){
                if(!(srcRect->ypos+srcRect->getRect().w<=actual->ypos||
                srcRect->ypos>=actual->ypos+srcRect->getRect().w||
                srcRect->xpos+srcRect->getRect().w<=actual->xpos||
                srcRect->xpos>=actual->xpos+srcRect->getRect().w)){
                    if(srcRect->originalDireccion==actual->originalDireccion){
                        if(!srcRect->move){
                            return true;
                        }else{
                            if(srcRect->ambulance){
                                actual->originalX=actual->xpos;
                                actual->originalY=actual->ypos;
                                actual->originalDireccion=actual->getDireccion();
                                if(srcRect->getDireccion()=="up"||srcRect->getDireccion()=="down"){
                                    actual->moveForAmbulance=true;
                                    actual->move=true;
                                    actual->setDireccion("right");
                                }else if(srcRect->getDireccion()=="right"||srcRect->getDireccion()=="left"){
                                    actual->moveForAmbulance=true;
                                    actual->move=true;
                                    actual->setDireccion("up");
                                }
                                srcRect->move=false;
                                return true;
                            }else{
                                return false;
                            }
                        }
                    }else{
                        if(srcRect->ambulance){
                            if(actual->getDireccion()=="choco"){
                                srcRect->setDireccion("destino");
                                numeroDeChoques=0;
                                Interseccion *inter;
                                for(auto &pair:ciudad.intersecciones){
                                    inter=pair.second;
                                    inter->disponible=true;
                                }
                                return false;
                            }
                            if(srcRect->xpos>actual->xpos){
                                return false;
                            }else{
                                actual->move=false;
                                return true;
                            }
                        }else{
                            n=rand()%100;
                            if(n<10&&numeroDeChoques==0&&!srcRect->noChocar&&srcRect->xpos<=300&&srcRect->xpos>=100&&srcRect->ypos<=300&&srcRect->ypos>=100){
                                numeroDeChoques++;
                                choque=true;
                                choqueX=srcRect->xpos;
                                choqueY=srcRect->ypos;
                                id1=srcRect->getID();
                                id2=actual->getID();
                                srcRect->setDireccion("choco");
                                srcRect->originalDireccion="choco";
                                actual->setDireccion("choco");
                                actual->originalDireccion="choco";
                            }else{
                                srcRect->noChocar=true;
                                actual->noChocar=true;
                                if(srcRect->xpos>actual->xpos&&srcRect->getDireccion()=="right"){
                                    return false;
                                }else if(srcRect->xpos<actual->xpos&&srcRect->getDireccion()=="left"){
                                    return false;
                                }else{
                                    if(actual->move){
                                        srcRect->move=false;
                                        return true;
                                    }else{
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            actual=actual->siguiente;
        }
        if(srcRect->moveForAmbulance){
            if(!collision(srcRect)){
                if(srcRect->xpos==srcRect->originalX&&srcRect->ypos==srcRect->originalY){
                    srcRect->setDireccion(srcRect->originalDireccion);
                    srcRect->moveForAmbulance=false;
                }else{
                    srcRect->move=true;
                }
            }else{
                if(srcRect->getDireccion()=="right"){
                    srcRect->setDireccion("left");
                }else if(srcRect->getDireccion()=="left"){
                    srcRect->setDireccion("right");
                }else if(srcRect->getDireccion()=="up"){
                    srcRect->setDireccion("down");
                }else if(srcRect->getDireccion()=="down"){
                    srcRect->setDireccion("up");
                }
                srcRect->move=false;
            }
            return false;
        }else{
            srcRect->noChocar=false;
            srcRect->move=true;
            return false;
        }
    }

    bool collision(Vehiculo *srcRect){
        Vehiculo *actual=listaDeVehiculos;
        while(actual!=nullptr){
            if(srcRect->getID()!=actual->getID()){
                if(!(srcRect->ypos+srcRect->getRect().w+1<=actual->ypos||
                srcRect->ypos>=actual->ypos+srcRect->getRect().w+1||
                srcRect->xpos+srcRect->getRect().w+1<=actual->xpos||
                srcRect->xpos>=actual->xpos+srcRect->getRect().w+1)){
                    return true;
                }
            }
            actual=actual->siguiente;
        }
        return false;
    }

    bool collisionForAdd(int x, int y, int w){
        Vehiculo* actual=listaDeVehiculos;
        while(actual!=nullptr){
            if(!(y+w<=actual->ypos||
            y>=actual->ypos+w||
            x+w<=actual->xpos||
            x>=actual->xpos+w)){
                return true;
            }
            actual=actual->siguiente;
        }
        return false;
    }

    void updatePos(int sizeRect){
        Vehiculo* actual=listaDeVehiculos;
        int resta;
        while(actual!=nullptr){
            if(actual->originalDireccion=="right"||actual->originalDireccion=="left"){
                resta=actual->ypos/sizeRect;
                actual->xpos-=resta;
                actual->ypos-=resta;
            }else{
                resta=actual->xpos/sizeRect;
                actual->xpos-=resta;
                actual->ypos-=resta;
            }
            actual=actual->siguiente;
        }
    }
};