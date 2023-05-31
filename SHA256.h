#include <math.h>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct SHA256 {
    string hash_result;
    SHA256() {}
    SHA256(string input) {
        hash_result = generate_hash(input);
    }
    string generate_hash(string input);
    ~SHA256() {}
};

/*
   Pasos para realizar el SHA-256 Hash
   1. Mensaje input transformarlo a binario
   2. Inicializar los valores de hash 'h'
   3. Inicializar valores de redondeo 'K'
   4. Bucle de 'chuncks'
   5. Generar la planificación del mensaje final
   6. Realizar la compresión final de la data
   7. Desarrollar la última mutación de los valores 'h'
   8. Mutar y Concatenar los valores 'h'
*/

string text_to_binary(string data);
string integer_to_binary_bits(int char_to_int, int cant_bits);
string bits_to_hexadecimal(uint32_t data);
int binary_to_int(string binaryString);

uint32_t operandRotR(uint32_t X, int base);
uint32_t operandShR(uint32_t X, int base);
uint32_t operandMaj(uint32_t X, uint32_t Y, uint32_t Z);
uint32_t operandCh(uint32_t X, uint32_t Y, uint32_t Z);
uint32_t operandSn(uint32_t X, int n);
uint32_t operandOn(uint32_t X, int n);

string SHA256::generate_hash(string input) {
    vector<uint32_t> h_consts;

    string resultado = "";
    // El primer paso para generar el SHA256 es volver el input a binario
    string input_binary = text_to_binary(input);
    int input_binary_size = input_binary.size();
    // Al resultado obtenido se le adiciona un '1'
    input_binary += "1";
    // Agregar al string resultante una cantidad de 0's que seán necesarios para
    // generar un string que su tamano sea multiplo de 512 y tenga menos de 448 bits
    while (true) {
        if (input_binary.size() % 512 == 448) break;
        input_binary += "0";
    }
    // Agregarle una cadena de 64 bits, que corresponda al binario del tamano actual del string binario
    input_binary += integer_to_binary_bits(input_binary_size, 64);

    // El segundo paso es generar los valores hash 'h'
    h_consts.push_back(0x6a09e667);
    h_consts.push_back(0xbb67ae85);
    h_consts.push_back(0x3c6ef372);
    h_consts.push_back(0xa54ff53a);
    h_consts.push_back(0x510e527f);
    h_consts.push_back(0x9b05688c);
    h_consts.push_back(0x1f83d9ab);
    h_consts.push_back(0x5be0cd19);

    // El tercer paso es generar las constantes de redondeo 'K'
    uint32_t K[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
        0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
        0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
        0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
        0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
        0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

    // El cuarto paso es generar un bucle que mutará cada 'chunck'
    // que tendrá 512 bits, por lo que tras cada mutación al final
    // se tendra un vector de 'chuncks'
    vector<vector<int>> bloqueBits = vector<vector<int>>();
    for (int i = 0; i < input_binary.size(); i += 512) {
        vector<int> subBloque = vector<int>(16);
        string substring_input = input_binary.substr(i, 512);
        for (int j = 0; j < 512; j += 32) {
            string bit32substring = substring_input.substr(j, 32);
            subBloque[j / 32] = binary_to_int(bit32substring);
        }
        bloqueBits.push_back(subBloque);
    }

    // El quinto paso es generar un vector W
    // Este vector de 64 digitos tendrá el contenido del
    // mensaje resultante
    vector<uint32_t> W = vector<uint32_t>(64);

    // El sexto paso es la compresión de la data
    // Dentro del bucle se mutarán los 'chuncks' empleando los valores 'h'
    for (int i = 0; i < bloqueBits.size(); i++) {
        uint32_t a = h_consts[0], b = h_consts[1], c = h_consts[2],
                 d = h_consts[3], e = h_consts[4], f = h_consts[5], g = h_consts[6], h = h_consts[7];

        // Descomponer vector W, esto se logra cumpliendo estos requerimientos
        // por cada 64 bits
        /*
        S1 = (e rightrotate 6) xor (e rightrotate 11) xor (e rightrotate 25)
        ch = (e and f) xor ((not e) and g)
        temp1 = h + S1 + ch + k[i] + w[i]
        S0 = (a rightrotate 2) xor (a rightrotate 13) xor (a rightrotate 22)
        maj = (a and b) xor (a and c) xor (b and c)
        temp2 := S0 + maj
        h = g
        g = f
        f = e
        e = d + temp1
        d = c
        c = b
        b = a
        a = temp1 + temp2
        */
        for (int j = 0; j < 64; j++) {
            if (j < 16) {
                W[j] = bloqueBits[i][j];
            } else {
                W[j] = operandOn(W[j - 2], 1) + W[j - 7] + operandOn(W[j - 15], 0) + W[j - 16];
            }

            uint32_t T1 = h + operandSn(e, 1) + operandCh(e, f, g) + K[j] + W[j];
            uint32_t T2 = operandSn(a, 0) + operandMaj(a, b, c);

            h = g;
            g = f;
            f = e;
            e = d + T1;
            d = c;
            c = b;
            b = a;
            a = T1 + T2;
        }
        // El septimo paso es la modificación final
        // de los valores de 'h', el cual cumple las siguiente regla:
        /*
        h0 = h0 + a
        h1 = h1 + b
        h2 = h2 + c
        h3 = h3 + d
        h4 = h4 + e
        h5 = h5 + f
        h6 = h6 + g
        h7 = h7 + h
        */
        h_consts[0] = a + h_consts[0];
        h_consts[1] = b + h_consts[1];
        h_consts[2] = c + h_consts[2];
        h_consts[3] = d + h_consts[3];
        h_consts[4] = e + h_consts[4];
        h_consts[5] = f + h_consts[5];
        h_consts[6] = g + h_consts[6];
        h_consts[7] = h + h_consts[7];
    }

    // El octavo paso y el último es el pasar cada valor de 'h' a
    // hexadecimal, de este modo se obtendrá una cadena de 512 caracteres
    for (auto h : h_consts) {
        resultado += bits_to_hexadecimal(h);
    }
    return resultado;
}

// Volver un string a binario
string text_to_binary(string data) {
    string result = "";
    for (int i = 0; i < data.size(); i++) {
        result += integer_to_binary_bits(data[i], 8);
    }
    return result;
}

// Volver un entero a un string
string integer_to_binary_bits(int char_to_int, int cant_bits) {
    string result = string(cant_bits, '0');
    int8_t turn_binar = 0;
    while (true) {
        if (char_to_int == 0) {
            break;
        }
        turn_binar = ((char_to_int & 1) + 48);
        result[cant_bits - 1] = turn_binar;
        --cant_bits;
        char_to_int = char_to_int / 2;
    }
    return result;
}

// Volver un binario a un entero
int binary_to_int(string binaryString) {
    int result = 0, i = 0;
    while (true) {
        if (binaryString.size() == 0) break;
        char last_char = binaryString[binaryString.size() - 1];
        int last_int = last_char - '0';
        int pow2perChar = pow(2, i);
        int num_result = last_int * pow2perChar;
        result += num_result;
        binaryString.pop_back();
        ++i;
    }
    return result;
}

// Volver una cadena de 32 bits a su representación hexadecimal
string bits_to_hexadecimal(uint32_t data) {
    string hexadecimalTable = "0123456789ABCDEF";
    string hexadecimalResult = "";
    uint32_t dividend = data;
    int rest = 0, quotient = 17, cant_hexadecimal = 0, index = 0;
    char hexadecimalChar;
    while (true) {
        if (rest < 16 && quotient < 16) {
            hexadecimalChar = hexadecimalTable[dividend];
            hexadecimalResult += hexadecimalChar;
            ++cant_hexadecimal;
            break;
        }
        rest = dividend % 16;
        quotient = dividend / 16;
        dividend = quotient;
        hexadecimalChar = hexadecimalTable[rest];
        hexadecimalResult += hexadecimalChar;
        ++cant_hexadecimal;
    }
    reverse(hexadecimalResult.begin(), hexadecimalResult.end());
    index = 8 - cant_hexadecimal;
    string result = string(index, '0');
    result += hexadecimalResult;
    return result;
}

// El circular right shift de bits n para una palabra binaria
uint32_t operandRotR(uint32_t X, int base) {
    uint32_t result = ((X >> base) | (X << (32 - base)));
    return result;
}

// Denota el circular right shift de bits n para una palabra binaria
uint32_t operandShR(uint32_t X, int base) {
    uint32_t result = (X >> base);
    return result;
}

uint32_t operandMaj(uint32_t X, uint32_t Y, uint32_t Z) {
    uint32_t result = ((X & Y) ^ (X & Z) ^ (Y & Z));
    return result;
}

uint32_t operandCh(uint32_t X, uint32_t Y, uint32_t Z) {
    uint32_t result = ((X & Y) ^ (~X & Z));
    return result;
}

// Empleando operador XOR
uint32_t operandSn(uint32_t X, int n) {
    uint32_t result;
    if (n == 0) {
        result = (operandRotR(X, 2) ^ operandRotR(X, 13) ^ operandRotR(X, 22));
    } else {
        result = (operandRotR(X, 6) ^ operandRotR(X, 11) ^ operandRotR(X, 25));
    }
    return result;
}

uint32_t operandOn(uint32_t X, int n) {
    uint32_t result;
    if (n == 0) {
        result = (operandRotR(X, 7) ^ operandRotR(X, 18) ^ operandShR(X, 3));
    } else {
        result = (operandRotR(X, 17) ^ operandRotR(X, 19) ^ operandShR(X, 10));
    }
    return result;
}
