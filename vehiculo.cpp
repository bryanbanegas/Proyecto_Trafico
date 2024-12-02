#include "vehiculo.h"

Vehiculo::Vehiculo(int id, string direccion, bool ambulance, SDL_Renderer *rend, int x, int y, vector<int> camino)
    : id(id), direccion(direccion), ambulance(ambulance), renderer(rend), xpos(x), ypos(y), camino(camino){
    caminosRecorridos.resize(camino.size(),-1);
    srcRect.x=xpos;
    srcRect.y=ypos;
    srcRect.w=20;
    srcRect.h=20;
    originalDireccion=direccion;
}

Vehiculo::~Vehiculo() {}

string Vehiculo::movimiento(const Grafo &ciudad){
    string dir[2];
    int n=rand(),contar=-1;
    bool terminar=false,yaRecorrido=false;
    Interseccion *inter,*inter2;

    if(ambulance){
        caminosRecorridos[0]=0;
        caminosRecorridos[1]=1;
        for(auto &pair:ciudad.intersecciones){
            inter=pair.second;
            if(srcRect.x==inter->x&&srcRect.y==inter->y){
                for(auto &pair2:ciudad.intersecciones){
                    inter2=pair2.second;
                    if(srcRect.x+100==inter2->x&&srcRect.y==inter2->y){
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
                    if(srcRect.x-100==inter2->x&&srcRect.y==inter2->y){
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
                    if(srcRect.x==inter2->x&&srcRect.y-100==inter2->y){
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
                    if(srcRect.x==inter2->x&&srcRect.y+100==inter2->y){
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
            //derecha
            if(srcRect.x>=inter->x-20&&srcRect.x<=inter->x&&srcRect.y==inter->y&&inter->semaforo&&inter->color=="red"&&direccion=="right"){
                if(!moveForAmbulance){
                    originalDireccion=direccion;
                    direccion="parar";
                }
            }else if(srcRect.x>=inter->x-20&&srcRect.x<=inter->x&&srcRect.y==inter->y&&inter->semaforo&&inter->color=="green"&&direccion=="parar"){
                if(!moveForAmbulance){
                    direccion=originalDireccion;
                }
            }
            //izquierda
            if(srcRect.x>=inter->x&&srcRect.x<=inter->x+20&&srcRect.y==inter->y&&inter->semaforo&&inter->color=="red"&&direccion=="left"){
                if(!moveForAmbulance){
                    originalDireccion=direccion;
                    direccion="parar";
                }
            }else if(srcRect.x>=inter->x&&srcRect.x<=inter->x+20&&srcRect.y==inter->y&&inter->semaforo&&inter->color=="green"&&direccion=="parar"){
                if(!moveForAmbulance){
                    direccion=originalDireccion;
                }
            }
            //arriba
            if(srcRect.x==inter->x&&srcRect.y>=inter->y&&srcRect.y<=inter->y+20&&inter->semaforo&&inter->color=="red"&&direccion=="up"){
                if(!moveForAmbulance){
                    originalDireccion=direccion;
                    direccion="parar";
                }
            }else if(srcRect.x==inter->x&&srcRect.y>=inter->y&&srcRect.y<=inter->y+20&&inter->semaforo&&inter->color=="green"&&direccion=="parar"){
                if(!moveForAmbulance){
                    direccion=originalDireccion;
                }
            }
            //abajo
            if(srcRect.x==inter->x&&srcRect.y>=inter->y-20&&srcRect.y<=inter->y&&inter->semaforo&&inter->color=="red"&&direccion=="down"){
                if(!moveForAmbulance){
                    originalDireccion=direccion;
                    direccion="parar";
                }
            }else if(srcRect.x==inter->x&&srcRect.y>=inter->y-20&&srcRect.y<=inter->y&&inter->semaforo&&inter->color=="green"&&direccion=="parar"){
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
                    if(srcRect.x+100==inter2->x&&srcRect.y==inter2->y&&inter2->disponible){
                        if(inter->direcciones[0]=="right"||inter->direcciones[1]=="right"){
                            contar++;
                            dir[contar]="right";
                        }
                    }
                    if(srcRect.x-100==inter2->x&&srcRect.y==inter2->y&&inter2->disponible){
                        if(inter->direcciones[0]=="left"||inter->direcciones[1]=="left"){
                            contar++;
                            dir[contar]="left";
                        }
                    }
                    if(srcRect.x==inter2->x&&srcRect.y-100==inter2->y&&inter2->disponible){
                        if(inter->direcciones[0]=="up"||inter->direcciones[1]=="up"){
                            contar++;
                            dir[contar]="up";
                        }
                    }
                    if(srcRect.x==inter2->x&&srcRect.y+100==inter2->y&&inter2->disponible){
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

    if(direccion=="right"){
        srcRect.x++;
        if(ambulance){
            srcRect.x++;
        }
        xpos=srcRect.x;
    }else if(direccion=="left"){
        srcRect.x--;
        xpos=srcRect.x;
    }else if(direccion=="up"){
        srcRect.y--;
        ypos=srcRect.y;
    }else if(direccion=="down"){
        srcRect.y++;
        ypos=srcRect.y;
    }

    return direccion;
}

void Vehiculo::Render(){
    if(ambulance){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }else{
        SDL_SetRenderDrawColor(renderer,255,0,0,255);
    }
    if(id!=0){
        SDL_RenderFillRect(renderer, &srcRect);
    }
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