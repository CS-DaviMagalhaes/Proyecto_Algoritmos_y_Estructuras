#ifndef BLOCK_H
#define BLOCK_H
#include <iostream>
#include <string>

#include "SHA256.h"
#include "retiro.h"
using namespace std;

class Block {
   private:
    unsigned int id = 1; 
    unsigned long int nonce;
    retiro *data;
    SHA256 *hash;
    string prev;
    bool is_valid;

   public:
    Block() {
        this->nonce = 1;
        this->data = new retiro();
        this->prev = string(64, '0');
        this->hash = new SHA256(data->get_data() + this->prev);
        this->is_valid = true;
    }

    Block(retiro *_data, unsigned long int _nonce = 1) {
        this->nonce = _nonce;
        this->data = _data;
        this->prev = string(64, '0');
        this->hash = new SHA256(data->get_data() + this->prev);
        if (hash->hash_result.substr(0, 4) != "0000")
            this->is_valid = false;
        else
            this->is_valid = true;
    }
    string get_cliente(){
        return this->data->cliente;
    }
    string get_lugar(){
        return this->data->lugar;
    }

    double get_monto(){
        return this->data->monto;
    }
    void set_id(unsigned int _id_block, string _prev_hash) {
        this->id = _id_block;
        if (this->id == 1) {
            this->prev = string(64, '0');
        } else {
            this->prev = _prev_hash;
        }
    }

    void mine() {
        SHA256 *hashToMine;
        unsigned int cont = 0;
        unsigned int valor = 0;
        string blockData = data->get_data();
        string dataMined;
        while (true) {
            dataMined = blockData;
            valor = int(round((pow((pow(cont, 2)) / 3, 1.0 / 3.0) * 500)));
            if (valor % 2 == 0) {
                string str_nonce = to_string(valor);
                dataMined += str_nonce;
                hashToMine = new SHA256(dataMined);
            }

            if (hashToMine->hash_result.substr(0, 4) == "0000") {
                break;
            }
            ++cont;
        }
        this->hash = hashToMine;
        this->nonce = cont;
        if (this->prev.substr(0, 4) != "0000") {
            this->is_valid = false;
        } else {
            this->is_valid = true;
        }
    }

    void reHash() {
        this->hash = new SHA256(data->get_data() + this->prev);
        if (hash->hash_result.substr(0, 4) != "0000" || this->prev.substr(0, 4) != "0000")
            this->is_valid = false;
        else
            this->is_valid = true;
    }

    string get_hash() {
        return this->hash->hash_result;
    }

    bool get_validation() {
        return this->is_valid;
    }

    void set_aceptada(string _hash_prev, int err = 0) {
        if (_hash_prev != this->prev || this->hash->hash_result.substr(0, 4) != "0000" || err == 1) {
            this->is_valid = false;
        }
    }

    unsigned int get_id() {
        return this->id;
    }

    void set_hash_prev(string _hash_prev) {
        this->prev = _hash_prev;
        this->hash = new SHA256(data->get_data() + this->prev);
        if (hash->hash_result.substr(0, 4) != "0000" || this->prev.substr(0, 4) != "0000")
            this->is_valid = false;
        else
            this->is_valid = true;
    }

    string get_data() {
        return this->data->get_data();
    }

    string get_hash_prev() {
        return this->prev;
    }

    void show_block_info(ostream &os) {
        os << endl;
        os << endl
           << "Block id: " << this->id;
        os << endl
           << "Nonce: " << this->nonce;
        os << endl
           << "----------------------------------------";
        os << endl
           << "cliente: " << this->data->cliente;
        os << endl
           << "lugar: " << this->data->lugar;
        os << endl
           << "Monto: " << this->data->monto;
        os << endl
           << "Fecha: " << this->data->fecha;        
           os << endl;
        os << "----------------------------------------";
        os << endl
           << "Hash Value: " << this->hash->hash_result;
        os << endl
           << "Prev Hash: " << this->prev;
        os << endl
           << "Valid block: " << boolalpha << this->is_valid;
    }

    void modify(string name) {
        this->data->lugar = name;
        this->hash = new SHA256(data->get_data() + this->prev);
        if (hash->hash_result.substr(0, 4) != "0000")
            this->is_valid = false;
        else
            this->is_valid = true;
    }
};
#endif
