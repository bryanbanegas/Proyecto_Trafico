#include "vehiculo.h"

Vehiculo::Vehiculo(int iD, string Direccion, bool Ambulance, SDL_Renderer *rend, int x, int y, vector<int> Camino)
    : id(iD), direccion(Direccion), ambulance(Ambulance), renderer(rend), xpos(x), ypos(y), camino(Camino){
    caminosRecorridos.resize(camino.size(),-1);
    srcRect.x=xpos;
    srcRect.y=ypos;
    srcRect.w=20;
    srcRect.h=20;
    originalDireccion=direccion;
}

string Vehiculo::movimiento(const Grafo &ciudad, const int sizeRecrt){
    srcRect.x=xpos;
    srcRect.y=ypos;
    srcRect.w=sizeRecrt+10;
    srcRect.h=sizeRecrt+10;
    string dir[2];
    int n=rand(),contar=-1;
    Interseccion *inter,*inter2;
    if(direccion=="right"){
        srcRect.x++;
        if(ambulance){
            srcRect.x++;
        }
        xpos=srcRect.x;
    }else if(direccion=="left"){
        srcRect.x--;
        if(ambulance){
            srcRect.x--;
        }
        xpos=srcRect.x;
    }else if(direccion=="up"){
        srcRect.y--;
        if(ambulance){
            srcRect.y--;
        }
        ypos=srcRect.y;
    }else if(direccion=="down"){
        srcRect.y++;
        if(ambulance){
            srcRect.y++;
        }
        ypos=srcRect.y;
    }
    if(ambulance){
        if(direccion=="destino"){
            return direccion;
        }
        caminosRecorridos[0]=0;
        caminosRecorridos[1]=1;
        for(auto &pair:ciudad.intersecciones){
            inter=pair.second;
            if(srcRect.x==inter->x&&srcRect.y==inter->y){
                for(auto &pair2:ciudad.intersecciones){
                    inter2=pair2.second;
                    if(srcRect.x+ciudad.distancia==inter2->x&&srcRect.y==inter2->y){
                        for(int i=0;i<camino.size();i++){
                            if(inter2->id==camino.at(i)&&inter2->id!=caminosRecorridos.at(i)){
                                int valor=inter2->id;
                                caminosRecorridos[i]=valor;
                                direccion="right";
                                contar++;
                                break;
                            }
                        }
                    }
                    if(srcRect.x-ciudad.distancia==inter2->x&&srcRect.y==inter2->y){
                        for(int i=0;i<camino.size();i++){
                            if(inter2->id==camino.at(i)&&inter2->id!=caminosRecorridos.at(i)){
                                int valor=inter2->id;
                                caminosRecorridos[i]=valor;
                                direccion="left";
                                contar++;
                                break;
                            }
                        }
                    }
                    if(srcRect.x==inter2->x&&srcRect.y-ciudad.distancia==inter2->y){
                        for(int i=0;i<camino.size();i++){
                            if(inter2->id==camino.at(i)&&inter2->id!=caminosRecorridos.at(i)){
                                int valor=inter2->id;
                                caminosRecorridos[i]=valor;
                                direccion="up";
                                contar++;
                                break;
                            }
                        }
                    }
                    if(srcRect.x==inter2->x&&srcRect.y+ciudad.distancia==inter2->y){
                        for(int i=0;i<camino.size();i++){
                            if(inter2->id==camino.at(i)&&inter2->id!=caminosRecorridos.at(i)){
                                int valor=inter2->id;
                                caminosRecorridos[i]=valor;
                                direccion="down";
                                contar++;
                                break;
                            }
                        }
                    }
                }
                if(contar==-1){
                    direccion="destino";              
                }
            }
        }
    }else{
        for(auto &pair:ciudad.intersecciones){
            inter=pair.second;
            if(srcRect.x>=inter->x-srcRect.w&&srcRect.x<=inter->x&&srcRect.y==inter->y&&inter->semaforo&&inter->color=="red"&&direccion=="right"){
                if(!moveForAmbulance){
                    originalDireccion=direccion;
                    direccion="parar";
                }
            }else if(srcRect.x>=inter->x-srcRect.w&&srcRect.x<=inter->x&&srcRect.y==inter->y&&inter->semaforo&&inter->color=="green"&&direccion=="parar"){
                if(!moveForAmbulance){
                    direccion=originalDireccion;
                }
            }
            if(srcRect.x>=inter->x&&srcRect.x<=inter->x+srcRect.w&&srcRect.y==inter->y&&inter->semaforo&&inter->color=="red"&&direccion=="left"){
                if(!moveForAmbulance){
                    originalDireccion=direccion;
                    direccion="parar";
                }
            }else if(srcRect.x>=inter->x&&srcRect.x<=inter->x+srcRect.w&&srcRect.y==inter->y&&inter->semaforo&&inter->color=="green"&&direccion=="parar"){
                if(!moveForAmbulance){
                    direccion=originalDireccion;
                }
            }
            if(srcRect.x==inter->x&&srcRect.y>=inter->y&&srcRect.y<=inter->y+srcRect.w&&inter->semaforo&&inter->color=="red"&&direccion=="up"){
                if(!moveForAmbulance){
                    originalDireccion=direccion;
                    direccion="parar";
                }
            }else if(srcRect.x==inter->x&&srcRect.y>=inter->y&&srcRect.y<=inter->y+srcRect.w&&inter->semaforo&&inter->color=="green"&&direccion=="parar"){
                if(!moveForAmbulance){
                    direccion=originalDireccion;
                }
            }
            if(srcRect.x==inter->x&&srcRect.y>=inter->y-srcRect.w&&srcRect.y<=inter->y&&inter->semaforo&&inter->color=="red"&&direccion=="down"){
                if(!moveForAmbulance){
                    originalDireccion=direccion;
                    direccion="parar";
                }
            }else if(srcRect.x==inter->x&&srcRect.y>=inter->y-srcRect.w&&srcRect.y<=inter->y&&inter->semaforo&&inter->color=="green"&&direccion=="parar"){
                if(!moveForAmbulance){
                    direccion=originalDireccion;
                }
            }
        }
        for(auto &pair:ciudad.intersecciones){
            inter=pair.second;
            if(srcRect.x==inter->x&&srcRect.y==inter->y){
                for(auto &pair2:ciudad.intersecciones){
                    inter2=pair2.second;
                    if(srcRect.x+ciudad.distancia==inter2->x&&srcRect.y==inter2->y&&inter2->disponible){
                        if(inter->direcciones[0]=="right"||inter->direcciones[1]=="right"){
                            contar++;
                            dir[contar]="right";
                        }
                    }
                    if(srcRect.x-ciudad.distancia==inter2->x&&srcRect.y==inter2->y&&inter2->disponible){
                        if(inter->direcciones[0]=="left"||inter->direcciones[1]=="left"){
                            contar++;
                            dir[contar]="left";
                        }
                    }
                    if(srcRect.x==inter2->x&&srcRect.y-ciudad.distancia==inter2->y&&inter2->disponible){
                        if(inter->direcciones[0]=="up"||inter->direcciones[1]=="up"){
                            contar++;
                            dir[contar]="up";
                        }
                    }
                    if(srcRect.x==inter2->x&&srcRect.y+ciudad.distancia==inter2->y&&inter2->disponible){
                        if(inter->direcciones[0]=="down"||inter->direcciones[1]=="down"){
                            contar++;
                            dir[contar]="down";                        
                        }
                    }
                }
                if(contar>-1){
                    n=rand()%(contar+1);
                    direccion=dir[n];
                    originalDireccion=direccion;
                }else{
                    direccion="destino";              
                }
            }
        }
    }

    return direccion;
}

void Vehiculo::Render(const int sizeRecrt){
    if(ambulance){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }else{
        SDL_SetRenderDrawColor(renderer,255,0,0,255);
    }
    SDL_RenderFillRect(renderer, &srcRect);
}

int Vehiculo::getID(){
    return id;
}

SDL_Rect Vehiculo::getRect(){
    return srcRect;
}

string Vehiculo::getDireccion(){
    return direccion;
}

void Vehiculo::setDireccion(string direc){
    direccion=direc;
}