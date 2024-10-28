#ifndef CALLE_H
#define CALLE_H

#include "interseccion.h"

class Calle{
public:
    Interseccion *origen;
    Interseccion *destino;
public:
    Calle(Interseccion *origin, Interseccion *destiny)
    :origen(origin), destino(destiny){}
};

#endif