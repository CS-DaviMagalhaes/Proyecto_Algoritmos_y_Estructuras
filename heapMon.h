#include <iomanip> // Necesario para get_time
#include <iostream>
#include <sstream> // Necesario para ostringstream
#include <stdexcept>
#include <vector>
using namespace std;

template <typename T> class HeapMon : public T {
public:
  enum Type { MAX_HEAP, MIN_HEAP };

private:
  T **elements;
  int capacity;
  int n;
  Type type;

public:


  HeapMon(int capacity, Type type = MAX_HEAP) : capacity(capacity), type(type) {
    elements = new T *[capacity];
    n = 0;
  }

  ~HeapMon() { delete[] elements; }

  void buildFromArray(T *elements, int n) {
    if (type == MAX_HEAP) {
      delete[] this->elements; // Liberar la memoria existente

      this->elements = new T[n]; // Asignar nueva memoria
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
      this->elements = new T[n];
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

  // push para T
  void push(T *value) { // listo
    if (type == MAX_HEAP) {
      if (n == capacity) {
        // redimensionar
        capacity = 2 * capacity;
        T **new_elements = new T *[capacity];
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
  T pop() { // listo
    if (type == MAX_HEAP) {
      if (n == 0)
        throw out_of_range("Heap vacio");
      T *value = elements[0];
      elements[0] = elements[n - 1];
      n--;
      heapify_down(0);
      return *value;
    } else {
      if (n == 0) {
        throw out_of_range("Heap vacio");
      }
      T *value = elements[0];
      elements[0] = elements[n - 1];
      n--;
      heapify_down2(0);
      return *value;
    }
  }

 
  T* top(){
  if (n == 0)
    throw out_of_range("Heap vacio");
  return elements[0];
  }
  
  vector<T> extractTheTopK(int k) {
    vector<T> topKElements;

    if (k <= 0 || k > n) {
      throw out_of_range("Valor inválido para 'k'");
    }

    for (int i = 0; i < k; i++) {
      if (is_empty()) {
        break; // Si el montículo está vacío, salimos del bucle
      }

      T topElement = pop(); // Extraer el elemento principal del montículo
      topKElements.push_back(
          topElement); // Agregar el elemento extraído al vector
    }

    return topKElements;
  }

  static void sortAsc(T *arr, int n) {
    HeapMon<T> *heap = new HeapMon<T>(10, HeapMon<T>::MIN_HEAP);
    heap->buildFromArray(arr, n);

    for (int i = 0; i < n; i++) {
      arr[i] = heap->pop();
    }
  }

  static void sortDesc(T *arr, int n) { // aqui se utiliza el MAXHEAP
    HeapMon<T> *heap = new HeapMon<T>(10, HeapMon<T>::MAX_HEAP);
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
