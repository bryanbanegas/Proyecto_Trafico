#include "vehiculo.h"

class Lista{
protected:
    Vehiculo *listaDeVehiculos;
    Lista *siguiente;
    int n=rand();
public:
    bool choque=false, eliminarVehiculo=false;
    int choqueX, choqueY, numeroDeChoques=0, id1, id2, idEliminar;
    Lista():listaDeVehiculos(nullptr), siguiente(nullptr){}

    Lista(int id, string direccion, float velocidad, SDL_Renderer *ren, int x, int y, vector<int> camino){
        listaDeVehiculos=new Vehiculo(id,direccion,velocidad,ren,x,y,camino);
        siguiente=nullptr;
    }

    void agregar(int id, string direccion, float velocidad, SDL_Renderer *ren, int x, int y, vector<int> camino){
        Lista *nuevoVehiculo=new Lista(id,direccion,velocidad,ren,x,y,camino);
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
            listaDeVehiculos=listaDeVehiculos->siguiente;
            siguiente=temporal->siguiente;
            temporal->listaDeVehiculos=nullptr;
            temporal->siguiente=nullptr;
            delete temporal;
        }
        while(actual->siguiente!=nullptr){
            if(actual->siguiente->listaDeVehiculos->getID()==id){
                Lista* eliminar=actual->siguiente;
                actual->siguiente=eliminar->siguiente;
                delete eliminar->listaDeVehiculos;
                delete eliminar;
                return;
            }
            actual=actual->siguiente;
        }
    }

    Vehiculo* getVehiculo(int id){
        Lista *actual=this;
        while(actual!=nullptr){
            if(actual->listaDeVehiculos->getID()==id){
                return actual->listaDeVehiculos;
            }
            actual=actual->siguiente;
        }
        return actual->listaDeVehiculos;
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
        Lista *actual=this;
        Vehiculo *carro;
        while(actual!=nullptr){
            carro=actual->listaDeVehiculos;
            if(!checkCollision(carro)){
                if(carro->move){
                    if(carro->movimiento(ciudad)=="destino"){
                        eliminar(carro->getID());
                    }
                }
            }else{
                if(carro->move){
                    if(carro->movimiento(ciudad)=="destino"){
                        eliminarVehiculo=true;
                        idEliminar=carro->getID();
                    }
                }
            }
            actual=actual->siguiente;
        }
    }

    void render(){
        Lista *actual=this;
        while(actual!=nullptr){
            actual->listaDeVehiculos->Render();
            actual=actual->siguiente;
        }
    }

    bool checkCollision(Vehiculo *srcRect){
        Lista *actual=this;
        while(actual!=nullptr){
            if(srcRect->getID()!=actual->listaDeVehiculos->getID()){
                if(!(srcRect->ypos+30<=actual->listaDeVehiculos->ypos||
                srcRect->ypos>=actual->listaDeVehiculos->ypos+30||
                srcRect->xpos+30<=actual->listaDeVehiculos->xpos||
                srcRect->xpos>=actual->listaDeVehiculos->xpos+30)){
                    if(srcRect->getDireccion()==actual->listaDeVehiculos->getDireccion()){
                        if(!srcRect->move){
                            return true;
                        }else{
                            if(srcRect->ambulance){
                                if(!actual->listaDeVehiculos->ambulance){
                                    if(srcRect->xpos<actual->listaDeVehiculos->xpos||srcRect->ypos<actual->listaDeVehiculos->ypos){
                                        actual->listaDeVehiculos->originalX=actual->listaDeVehiculos->xpos;
                                        actual->listaDeVehiculos->originalY=actual->listaDeVehiculos->ypos;
                                        actual->listaDeVehiculos->originalDireccion=actual->listaDeVehiculos->getDireccion();
                                        if(srcRect->getDireccion()=="up"||srcRect->getDireccion()=="down"){
                                            actual->listaDeVehiculos->moveForAmbulance=true;
                                            actual->listaDeVehiculos->move=true;
                                            actual->listaDeVehiculos->setDireccion("right");
                                        }else if(srcRect->getDireccion()=="right"||srcRect->getDireccion()=="left"){
                                            actual->listaDeVehiculos->moveForAmbulance=true;
                                            actual->listaDeVehiculos->move=true;
                                            actual->listaDeVehiculos->setDireccion("up");
                                        }
                                    }else{
                                        if(srcRect->getDireccion()=="up"||srcRect->getDireccion()=="down"){
                                            actual->listaDeVehiculos->moveForAmbulance=true;
                                            actual->listaDeVehiculos->move=true;
                                            actual->listaDeVehiculos->setDireccion("left");
                                        }else if(srcRect->getDireccion()=="right"||srcRect->getDireccion()=="left"){
                                            actual->listaDeVehiculos->moveForAmbulance=true;
                                            actual->listaDeVehiculos->move=true;
                                            actual->listaDeVehiculos->setDireccion("down");
                                        }
                                    }
                                }
                                return true;
                            }else{
                                return false;
                            }
                        }
                    }else{
                        if(srcRect->ambulance&&srcRect->xpos>actual->listaDeVehiculos->xpos){
                            return false;
                            if(srcRect->xpos>actual->listaDeVehiculos->xpos){
                                return false;
                            }else{
                                actual->listaDeVehiculos->move=false;
                                return true;
                            }
                        }else if(actual->listaDeVehiculos->ambulance){
                            if(srcRect->xpos<actual->listaDeVehiculos->xpos){
                                return false;
                            }else{
                                srcRect->move=false;
                                return true;
                            }
                        }else{
                            n=rand()%100;
                            if(n>10&&numeroDeChoques<2){
                                numeroDeChoques++;
                                choque=true;
                                choqueX=srcRect->xpos;
                                choqueY=srcRect->ypos;
                                id1=srcRect->getID();
                                id2=actual->listaDeVehiculos->getID();
                                srcRect->setDireccion("choco");
                                actual->listaDeVehiculos->setDireccion("choco");
                            }else{
                                if(srcRect->xpos>actual->listaDeVehiculos->xpos){
                                    return false;
                                }else{
                                    if(actual->listaDeVehiculos->move){
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
            srcRect->move=true;
            return false;
        }
    }

    bool collision(Vehiculo *srcRect){
        Lista *actual=this;
        while(actual!=nullptr){
            if(srcRect->getID()!=actual->listaDeVehiculos->getID()){
                if(!(srcRect->ypos+31<=actual->listaDeVehiculos->ypos||
                srcRect->ypos>=actual->listaDeVehiculos->ypos+31||
                srcRect->xpos+31<=actual->listaDeVehiculos->xpos||
                srcRect->xpos>=actual->listaDeVehiculos->xpos+31)){
                    if(!actual->listaDeVehiculos->ambulance){
                        return true;
                    }
                }
            }
            actual=actual->siguiente;
        }
        return false;
    }
};