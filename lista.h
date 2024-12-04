#include "vehiculo.h"

class Lista{
protected:
    Vehiculo* listaDeVehiculos;
    int n=rand();
public:
    bool choque=false;
    int cantidadDeVehiculos=0, choqueX, choqueY, numeroDeChoques=0, id1, id2;
    Lista():listaDeVehiculos(nullptr){}
    ~Lista(){
        Vehiculo* actual=listaDeVehiculos;
        while(actual!=nullptr){
            Vehiculo* temporal=actual;
            actual=actual->siguiente;
            delete temporal;
        }
    }

    void agregar(string direccion, float velocidad, SDL_Renderer *ren, int x, int y, vector<int> camino){
        cantidadDeVehiculos++;
        Vehiculo* nuevoVehiculo=new Vehiculo(cantidadDeVehiculos,direccion,velocidad,ren,x,y,camino);
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
            }else{
                Vehiculo *actual=listaDeVehiculos;
                Vehiculo *anterior=nullptr;
                while(actual!=nullptr){
                    if(actual->getID()==id){
                        anterior->siguiente=actual->siguiente;
                        delete actual;
                        cantidadDeVehiculos--;
                        break;
                    }
                    actual=actual->siguiente;
                }
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
            if(!checkCollision(actual)){
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

    bool checkCollision(Vehiculo *srcRect){
        Vehiculo *actual=listaDeVehiculos;
        while(actual!=nullptr){
            if(srcRect->getID()!=actual->getID()){
                if(!(srcRect->ypos+30<=actual->ypos||
                srcRect->ypos>=actual->ypos+30||
                srcRect->xpos+30<=actual->xpos||
                srcRect->xpos>=actual->xpos+30)){
                    if(srcRect->getDireccion()==actual->getDireccion()){
                        if(!srcRect->move){
                            return true;
                        }else{
                            if(srcRect->ambulance){
                                if(!actual->ambulance){
                                    if(srcRect->xpos<actual->xpos||srcRect->ypos<actual->ypos){
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
                                    }else{
                                        if(srcRect->getDireccion()=="up"||srcRect->getDireccion()=="down"){
                                            actual->moveForAmbulance=true;
                                            actual->move=true;
                                            actual->setDireccion("left");
                                        }else if(srcRect->getDireccion()=="right"||srcRect->getDireccion()=="left"){
                                            actual->moveForAmbulance=true;
                                            actual->move=true;
                                            actual->setDireccion("down");
                                        }
                                    }
                                }
                                return true;
                            }else{
                                return false;
                            }
                        }
                    }else{
                        if(srcRect->ambulance){
                            if(actual->getDireccion()=="choco"){
                                srcRect->setDireccion("destino");
                                return false;
                            }
                            if(srcRect->xpos>actual->xpos){
                                return false;
                            }else{
                                actual->move=false;
                                return true;
                            }
                        }else if(actual->ambulance){
                            if(srcRect->xpos<actual->xpos){
                                return false;
                            }else{
                                srcRect->move=false;
                                return true;
                            }   
                        }else{
                            n=rand()%100;
                            n=8;
                            if(n<10&&numeroDeChoques==0){
                                numeroDeChoques++;
                                choque=true;
                                choqueX=srcRect->xpos;
                                choqueY=srcRect->ypos;
                                id1=srcRect->getID();
                                id2=actual->getID();
                                srcRect->setDireccion("choco");
                                actual->setDireccion("choco");
                            }else{
                                if(srcRect->xpos>actual->xpos){
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
            if(!collision(srcRect->xpos,srcRect->ypos)){
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

    bool collision(int x, int y){
        Vehiculo* actual=listaDeVehiculos;
        while(actual!=nullptr){
            if(!(y+31<=actual->ypos||
            y>=actual->ypos+31||
            x+31<=actual->xpos||
            x>=actual->xpos+31)){
                if(!actual->ambulance){
                    return true;
                }
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