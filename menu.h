#include <iostream>
#include <chrono>
#include <iomanip> // Necesario para get_time
#include <sstream> // Necesario para ostringstream
#include <ctime>
#include <fstream>
#include <vector>

#include "Block.h"
#include "BlockChain.h"
#include "retiro.h"

void Menu(Blockchain *coins) {
    int block;
    char rpta;
    string cliente, lugar;
    double monto;

    do {
        cout << endl
             << "---------------------------" << endl;
        cout << "    coins Menu" << endl;
        cout << "---------------------------" << endl;
        cout << "1. Crear Bloque" << endl;
        cout << "2. Imprimir Blockchain" << endl;
        cout << "3. Proof Of Work Test" << endl;
        cout << "4. Arreglar Blockchain" << endl;
        cout << "5. Importar Blockchain" << endl;
        cout << "6. Mayor Valor" << endl;
        cout << "7. Menor Valor" << endl;
        cout << "8. Calcular monto usuario" << endl;
        cout << "9. Salir" << endl;

        cout << endl
             << "Ingrese una opcion: ";
        cin >> rpta;
        cout << endl;

    } while (rpta != '1' && rpta != '2' && rpta != '3' && rpta != '4' && rpta != '5' && rpta != '6'&& rpta != '7'&& rpta != '8'&& rpta !='9');

    if (rpta == '1') {  // Creamos y a;adimos el bloque a la blockchain

        cout << "---------------------------" << endl;
        cout << endl
             << "Ingrese cliente: ";
        cin >> cliente;
        cout << "Ingrese lugar: ";
        cin >> lugar;
        cout << "Ingrese cantidad de coins a enviar: ";
        cin >> monto;
        cout << endl;
        auto fechaActual = chrono::system_clock::now();
        time_t fechaActualTimeT = chrono::system_clock::to_time_t(fechaActual);
        tm* fechaActualTM = localtime(&fechaActualTimeT);
        ostringstream fechaActualStringStream;
        fechaActualStringStream << put_time(fechaActualTM, "%Y-%m-%d");
        string fechaActualString = fechaActualStringStream.str();
        retiro *data = new retiro(cliente, lugar, monto, fechaActualString);



        coins->addBlock(data);
        cout << endl
             << "Bloque creado satisfactoriamente." << endl;
        Menu(coins);
    } else if (rpta == '2') {
        coins->show_blockchain();
        Menu(coins);

    } else if (rpta == '3') {
        cout << "---------------------------" << endl;
        cout << endl
             << "Ingrese Bloque: ";
        cin >> block;
        coins->test_proof_work(block);
        Menu(coins);

    } else if (rpta == '4') {
        cout << "---------------------------" << endl;
        cout << "Arreglando Blockchain..." << endl;
        cout << "---------------------------" << endl;

        coins->fix_all();
        cout << endl
             << "Blockchain Arreglada Satisfactoriamente." << endl;
        Menu(coins);

    }

    else if (rpta == '5') {
        string file;
        cout << "Ingrese nombre del archivo (path): " << endl;
        cin >> file;
        coins->import_blockchain(file);
        cout << "Archivo CSV importado exitosamente.\n";
        Menu(coins);
    }

    else if (rpta == '6') {
        string tipe;
        cout <<"Mayor valor de monto o fecha: ";
        cin>>tipe;

        coins->max_value(tipe);
        Menu(coins);

    }
    else if (rpta == '7') {
        string tipe;
        cout <<"Menor valor de monto o fecha: ";
        cin>>tipe;
        coins->min_value(tipe);
        Menu(coins);

    }
    else if (rpta == '8'){
        string nombre_cliente;
        cout << "Ingrese el nombre del usuario" << endl; 
        cin >> nombre_cliente; 
        coins->calcular_monto_acumulado(nombre_cliente);
        Menu(coins);
    }
    else if (rpta == '9') {
        cout << endl
             << "Gracias por usar la plataforma. " << endl;
        cout << endl
             << " " << endl;
    }

}
