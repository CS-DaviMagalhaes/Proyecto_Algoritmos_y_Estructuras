#include "retiro.h"
#include <iomanip> // Necesario para get_time
#include <iostream>
#include <sstream> // Necesario para ostringstream
#include <stdexcept>
#include <vector>
using namespace std;

template <typename T> class HeapMon : public retiro {
public:
  enum Type { MAX_HEAP, MIN_HEAP };

private:
  retiro **elements;
  int capacity;
  int n;
  Type type;

public:


  HeapMon(int capacity, Type type = MAX_HEAP) : capacity(capacity), type(type) {
    elements = new retiro *[capacity];
    n = 0;
  }

  ~HeapMon() { delete[] elements; }
  /*
  retiro& operator[](int index) {
      // Add bounds checking if desired
      return elements[index];
  }
  */
  
// int convertir_fecha(string fechaStr) {
//     // Convertir la fecha a un número
//     tm fechaInfo = {};
//     istringstream ss(fechaStr);
//     ss >> get_time(&fechaInfo, "%Y-%m-%d");
//     time_t fechaNumericaIngresada = mktime(&fechaInfo) / (60 * 60 * 24);

//     return fechaNumericaIngresada;
//   }

  void buildFromArray(retiro *elements, int n) {
    if (type == MAX_HEAP) {
      delete[] this->elements; // Liberar la memoria existente

      this->elements = new retiro[n]; // Asignar nueva memoria
      capacity = n;
      this->n = n;

      for (int i = 0; i < n; i++) {
        this->elements[i] = elements[i];
      }

      for (int i = n / 2 - 1; i >= 0; i--) {
        heapify_down(i);
      }
    }

    else {
      delete[] this->elements;
      this->elements = new retiro[n];
      capacity = n;
      this->n = n;

      for (int i = 0; i < n; i++) {
        this->elements[i] = elements[i];
      }

      for (int i = n / 2 - 1; i >= 0; i--) {
        heapify_down2(i);
      }
    }
  }

  int size() { return n; }

  bool is_empty() { return n == 0; }

  // push para retiro
  void push(retiro *value) { // listo
    if (type == MAX_HEAP) {
      if (n == capacity) {
        // redimensionar
        capacity = 2 * capacity;
        retiro **new_elements = new retiro *[capacity];
        for (int i = 0; i < n; i++)
          new_elements[i] = elements[i];
      }
      elements[n] = value;
      n++;
      heapify_up(n - 1);
    } else {
      if (n == capacity) {
        capacity = 2 * capacity;
      }
      elements[n] = value;
      n++;
      heapify_up2(n - 1);
    }
  }
  retiro pop() { // listo
    if (type == MAX_HEAP) {
      if (n == 0)
        throw out_of_range("Heap vacio");
      retiro *value = elements[0];
      elements[0] = elements[n - 1];
      n--;
      heapify_down(0);
      return *value;
    } else {
      if (n == 0) {
        throw out_of_range("Heap vacio");
      }
      retiro *value = elements[0];
      elements[0] = elements[n - 1];
      n--;
      heapify_down2(0);
      return *value;
    }
  }

 
  retiro* top(){
  if (n == 0)
    throw out_of_range("Heap vacio");
  return elements[0];
  }
  
  vector<retiro> extractTheTopK(int k) {
    vector<retiro> topKElements;

    if (k <= 0 || k > n) {
      throw out_of_range("Valor inválido para 'k'");
    }

    for (int i = 0; i < k; i++) {
      if (is_empty()) {
        break; // Si el montículo está vacío, salimos del bucle
      }

      retiro topElement = pop(); // Extraer el elemento principal del montículo
      topKElements.push_back(
          topElement); // Agregar el elemento extraído al vector
    }

    return topKElements;
  }

  static void sortAsc(retiro *arr, int n) {
    HeapMon<retiro> *heap = new HeapMon<retiro>(10, HeapMon<retiro>::MIN_HEAP);
    heap->buildFromArray(arr, n);

    for (int i = 0; i < n; i++) {
      arr[i] = heap->pop();
    }
  }

  static void sortDesc(retiro *arr, int n) { // aqui se utiliza el MAXHEAP
    HeapMon<retiro> *heap = new HeapMon<retiro>(10, HeapMon<retiro>::MAX_HEAP);
    heap->buildFromArray(arr, n);

    for (int i = 0; i < n; i++) {
      arr[i] = heap->pop();
    }
  }

private:
  int Parent(int i) { return (i - 1) / 2; }

  int Left(int i) { return (2 * i + 1); }

  int Right(int i) { return (2 * i + 2); }

  void heapify_down(int i) {
    int left = Left(i), right = Right(i);
    int maxi = elements[i]->monto, imax = i;

    if (left < n && elements[left]->monto > maxi) {
      maxi = elements[left]->monto;
      imax = left;
    }
    if (right < n && elements[right]->monto > maxi) {
      maxi = elements[right]->monto;
      imax = right;
    }
    if (maxi == elements[i]->monto)
      return;
    else {
      swap(elements[i], elements[imax]);
      heapify_down(imax);
    }
  }

  void heapify_up(int i) {
    while (i > 0 && elements[Parent(i)]->monto <
                        elements[i]->monto) {
      swap(elements[Parent(i)], elements[i]);
      i = Parent(i);
    }
  }
  void heapify_down2(int i) {
    int left = Left(i), right = Right(i);
    int extremum = elements[i]->monto, imin = i;

    if (left < n && elements[left]->monto < extremum) {
      extremum = elements[left]->monto;
      imin = left;
    }
    if (right < n && elements[right]->monto < extremum) {
      extremum = elements[right]->monto;
      imin = right;
    }

    if (extremum == elements[i]->monto)
      return;
    else {
      swap(elements[i], elements[imin]);
      heapify_down2(imin);
    }
  }

  void heapify_up2(int i) {
    while (i > 0) {
      int parent = Parent(i);
      if (elements[parent]->monto >
          elements[i]->monto) {
        swap(elements[parent], elements[i]);
        i = parent;
      } else {
        break;
      }
    }
  }
};