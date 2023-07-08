// Clase Blockchain
#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdlib.h>

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "Block.h"
#include "double.h"
#include "heap.h"
#include "heapMon.h"
using namespace std;

class Blockchain {
   private:
    List<Block *> *chain = new DoubleList<Block *>();
    Heap<retiro>* heap_fechaMax = new Heap<retiro>(10, Heap<retiro>::MAX_HEAP);
    Heap<retiro>* heap_fechaMin = new Heap<retiro>(10, Heap<retiro>::MIN_HEAP);
    HeapMon<retiro>* heap_montoMin = new HeapMon<retiro>(10, HeapMon<retiro>::MIN_HEAP);
    HeapMon<retiro>* heap_montoMax = new HeapMon<retiro>(10, HeapMon<retiro>::MAX_HEAP);

    unsigned int size_chain = 0;
    
   public:
    // Constructor
    Blockchain() {}

    // Public Functions
    void addBlock(retiro *data);
    void show_blockchain();
    void import_blockchain(const string& archivo);
    void test_proof_work(int id);
    void fix_all();
    void max_value(string tipe);
    void min_value(string tipe);
    void calcular_monto_acumulado(string nombre_cliente);

    // nuevo
    void search(string opc);

};

void Blockchain::addBlock(retiro *data) {
    if (this->chain->back() != nullptr) {
        Block *prev_block = this->chain->back();
        Block *new_block = new Block(data);
        string prev_hash = prev_block->get_hash();
        new_block->set_id(this->size_chain + 1, prev_hash);
        new_block->mine();
        this->chain->push_back(new_block);
        this->size_chain = this->chain->size();
        
    } else {
        Block *new_block = new Block(data);
        new_block->set_id(this->size_chain + 1, "");
        new_block->mine();
        this->chain->push_back(new_block);
        this->size_chain = this->chain->size();
    }
    heap_fechaMax->push(data);
    heap_fechaMin->push(data);
    heap_montoMin->push(data);
    heap_montoMax->push(data);
    
}

void Blockchain::max_value(string tipe){
    if(tipe=="Fecha"||tipe=="fecha"){
        cout<<endl;
        retiro* max=heap_fechaMax->top();
        cout << max->cliente << endl; 
        cout << max->lugar << endl;
        cout << max->monto << endl; 
        cout << max->fecha<< endl; 
        cout << "----------------------" << endl; 
    }
    else if (tipe=="Monto"|| tipe=="monto")
    {   
        cout<<endl;
        retiro* max=heap_montoMax->top();
        cout << max->cliente << endl; 
        cout << max->lugar << endl;
        cout << max->monto << endl; 
        cout << max->fecha<< endl; 
        cout << "----------------------" << endl; 

    }
    else{
        cout<<"Termino ingresado no aceptado"<<endl; 
    }

}
void Blockchain::min_value(string tipe){
    if(tipe=="Fecha"||tipe=="fecha"){
        cout<<endl;
        retiro* min=heap_fechaMin->top();
        cout << min->cliente << endl; 
        cout << min->lugar << endl;
        cout << min->monto << endl; 
        cout << min->fecha<< endl; 
        cout << "----------------------" << endl; 
    }
    else if (tipe=="Monto"|| tipe=="monto")
    {   
        cout<<endl;
        retiro* min=heap_montoMin->top();
        cout << min->cliente << endl; 
        cout << min->lugar << endl;
        cout << min->monto << endl; 
        cout << min->fecha<< endl; 
        cout << "----------------------" << endl; 

    }
    else{
        cout<<"Termino ingresado no aceptado"<<endl;

    }
    
}

void Blockchain::show_blockchain() {
    ListIterator<Block *> it;
    for (it = this->chain->begin(); it != this->chain->end(); ++it) {
        Block *currentBlock = *it;
        currentBlock->show_block_info(cout);
    }
}
void Blockchain::calcular_monto_acumulado(string nombre_cliente){
    int total = 0; 
    ListIterator<Block *> it;
    for (it = this->chain->begin(); it != this->chain->end(); ++it) {
        Block *currentBlock = *it;
        if (currentBlock->get_cliente() == nombre_cliente)
            total += currentBlock->get_monto();
    }
    cout << "monto total: " << total << " coins" << endl; 
}

void Blockchain::search(string opc){
    if(opc=="1"){
        string nombre_cliente;
        cout<<"Ingrese el nombre del usuario"<<endl;
        cin>>nombre_cliente;

        ListIterator<Block *> it;
        cout<<"\n";
        cout<<"----------------------------------------\n";
        cout << "\tRetiros de cliente " << nombre_cliente ;
        for (it = this->chain->begin(); it != this->chain->end(); ++it) {
            Block *currentBlock = *it;
            if (currentBlock->get_cliente() == nombre_cliente)
                currentBlock->show_block_info(cout);
        }
    }
    else if(opc=="2"){
            string lugar;
            cout<<"Ingrese un lugar"<<endl;
            cin>>lugar;

            ListIterator<Block *> it;
            cout<<"\n";
            cout<<"----------------------------------------\n";
            cout << "\tRetiros en " << lugar ;
            for (it = this->chain->begin(); it != this->chain->end(); ++it) {
                Block *currentBlock = *it;
                if (currentBlock->get_lugar() == lugar)
                    currentBlock->show_block_info(cout);
            }
    }
    else if(opc=="3"){
        double monto;
        cout<<"Ingrese un monto"<<endl;
        cin>>monto;

        ListIterator<Block *> it;
        cout<<"\n";
        cout<<"----------------------------------------\n";
        cout << "\tRetiros con un monto de s/" << monto  ;
        for (it = this->chain->begin(); it != this->chain->end(); ++it) {
            Block *currentBlock = *it;
            if (currentBlock->get_monto() == monto)
                currentBlock->show_block_info(cout);
        }
    }
}



void Blockchain::import_blockchain(const string& archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cout << "Error al abrir el archivo CSV.\n";
        return;
    }

    string linea;
    while (getline(file, linea)) {
        istringstream ss(linea);
        string value;
        vector<string> values;

        while (getline(ss, value, ',')) {
            values.push_back(value);
        }

        if (values.size() == 4) {
            retiro* data = new retiro();
            data->cliente = values[0];
            data->lugar = values[1];
            data->monto = std::stoi(values[2]);
            data->fecha = values[3];

            addBlock(data);
        }
    }

    file.close();
}

void Blockchain::test_proof_work(int id) {
    int cont = 1;
    ListIterator<Block *> it;
    string hash_tmp;
    bool flag1 = false;
    bool flag2 = false;
    for (it = this->chain->begin(); it != this->chain->end(); ++it) {
        Block *currentBlock = *it;
        if (flag2 == true) {
            currentBlock->set_hash_prev(hash_tmp);
            currentBlock->mine();
        }
        if (flag1 == true) {
            currentBlock->set_hash_prev(hash_tmp);
        }
        if (cont == id) {
            string new_name;
            cout << endl
                 << "Ingrese nombre para el nuevo lugar de retiro: ";
            cin >> new_name;
            currentBlock->modify(new_name);
            cout << endl
                 << "Desea arreglar el blockChain? (0 o 1): ";
            bool fix;
            cin >> fix;
            if (fix == false) {
                flag1 = true;
            } else {
                currentBlock->mine();
                flag2 = true;
            }
        }
        hash_tmp = currentBlock->get_hash();
        cont++;
    }
}

void Blockchain::fix_all() {
    ListIterator<Block *> it;
    string hash_tmp;
    for (it = this->chain->begin(); it != this->chain->end(); ++it) {
        Block *currentBlock = *it;
        if (currentBlock->get_validation() == false) {
            currentBlock->set_hash_prev(hash_tmp);
            currentBlock->mine();
        }
        hash_tmp = currentBlock->get_hash();
    }
}

#endif

