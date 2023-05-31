#ifndef RETIRO_H
#define RETIRO_H
#include <iostream>
#include <ctime>
#include <string>
using namespace std;

struct retiro{
    string cliente;
    string lugar;
    double monto;
    string fecha;
    
    retiro(){}

    retiro(string cli, string lug, double mon ,string time) {
            cliente= cli;
            lugar= lug;
            monto=mon;
            fecha = time;
        }
    
    string get_data(){
        string data= "";
        data+=this->cliente;
        data+=this->lugar;
        data+= to_string(this->monto);
        data+=this->fecha;
        return data;
    }

};
#endif
