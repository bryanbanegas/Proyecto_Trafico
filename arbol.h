#pragma once
#include <iostream>
#include <vector>
#include "clima.h"

class Arbol{
private:
    Clima *root;

    void agregarNodo(std::string tipo, float dato, Clima *nuevoNodo);
    int getRangoDeClimaEnArbol(std::string tipo, Clima *actualNodo);
public:
    Arbol():root(nullptr){}
    ~Arbol(){
        if(root)delete root;
    }

    void agregar(std::string tipo, float dato);
    int getRangoDeClima(std::string tipo);
};