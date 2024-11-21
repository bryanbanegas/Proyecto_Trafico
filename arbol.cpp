#include "arbol.h"

void Arbol::agregarNodo(std::string tipo, float dato, Clima *actualNodo){
    if(actualNodo->getRango()==dato){
        std::cout<<"Este valor ya esta en el arbol."<<std::endl;
    }else if(actualNodo->getRango()>dato){
        if(!actualNodo->left){
            actualNodo->left=new Clima(tipo,dato);
        }else{
            agregarNodo(tipo,dato,actualNodo->left);
        }
    }else if(actualNodo->getRango()<dato){
        if(!actualNodo->right){
            actualNodo->right=new Clima(tipo,dato);
        }else{
            agregarNodo(tipo,dato,actualNodo->right);
        }
    }
}

void Arbol::agregar(std::string tipo, float dato){
    if(!root){
        root=new Clima(tipo,dato);
    }else{
        agregarNodo(tipo,dato,root);
    }
}

int Arbol::getRangoDeClima(std::string tipo){
    if(root){
        return getRangoDeClimaEnArbol(tipo,root);
    }
    return 0;
}

int Arbol::getRangoDeClimaEnArbol(std::string tipo,Clima *actualNodo){
    if(actualNodo->getTipoDeClima()==tipo){
        return actualNodo->getRango();
    }
    if(actualNodo->left){
        int rango=getRangoDeClimaEnArbol(tipo,actualNodo->left);
        if(rango!=0){
            return rango;
        }
    }
    if(actualNodo->right){
        int rango=getRangoDeClimaEnArbol(tipo,actualNodo->right);
        if(rango!=0){
            return rango;
        }
    }
    return 0;
}