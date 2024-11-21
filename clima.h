#ifndef CLIMA_H
#define CLIMA_H
#include <string>

class Clima{
private:
    std::string tipo;
    float rango;
public:
    Clima *left;
    Clima *right;

    Clima(std::string ti, float ran)
    :tipo(ti), rango(ran), left(nullptr), right(nullptr){}
    ~Clima(){
        if (left) delete left;
        if (right) delete right;
    }
    
    std::string getTipoDeClima(){
        return tipo;
    }
    
    float getRango(){
        return rango;
    }
};

#endif