#include <iomanip> // Necesario para get_time
#include <iostream>
#include <sstream> // Necesario para ostringstream
#include <stdexcept>
#include <vector>
using namespace std;

template <typename T> class Heap : public T {
public:
  enum Type { MAX_HEAP, MIN_HEAP };

private:
  T **elements;
  int capacity;
  int n;
  Type type;

public:
//  Heap(T *elements, int n, Type type = MAX_HEAP)
//      : elements(elements), n(n), type(type) {
//    capacity = n;
//    for (int i = n / 2 - 1; i >= 0; i--)
//      heapify_down(i);
//  }

  Heap(int capacity, Type type = MAX_HEAP) : capacity(capacity), type(type) {
    elements = new T *[capacity];
    n = 0;
  }

  ~Heap() { delete[] elements; }
  /*
  T& operator[](int index) {
      // Add bounds checking if desired
      return elements[index];
  }
  */
  
int convertir_fecha(string fechaStr) {
    // Convertir la fecha a un número
    tm fechaInfo = {};
    istringstream ss(fechaStr);
    ss >> get_time(&fechaInfo, "%Y-%m-%d");
    time_t fechaNumericaIngresada = mktime(&fechaInfo) / (60 * 60 * 24);

    return fechaNumericaIngresada;
  }

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
    Heap<T> *heap = new Heap<T>(10, Heap<T>::MIN_HEAP);
    heap->buildFromArray(arr, n);

    for (int i = 0; i < n; i++) {
      arr[i] = heap->pop();
    }
  }

  static void sortDesc(T *arr, int n) { // aqui se utiliza el MAXHEAP
    Heap<T> *heap = new Heap<T>(10, Heap<T>::MAX_HEAP);
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
    int maxi = convertir_fecha(elements[i]->fecha), imax = i;

    if (left < n && convertir_fecha(elements[left]->fecha) > maxi) {
      maxi = convertir_fecha(elements[left]->fecha);
      imax = left;
    }
    if (right < n && convertir_fecha(elements[right]->fecha) > maxi) {
      maxi = convertir_fecha(elements[right]->fecha);
      imax = right;
    }
    if (maxi == convertir_fecha(elements[i]->fecha))
      return;
    else {
      swap(elements[i], elements[imax]);
      heapify_down(imax);
    }
  }

  void heapify_up(int i) {
    while (i > 0 && convertir_fecha(elements[Parent(i)]->fecha) <
                        convertir_fecha(elements[i]->fecha)) {
      swap(elements[Parent(i)], elements[i]);
      i = Parent(i);
    }
  }
  void heapify_down2(int i) {
    int left = Left(i), right = Right(i);
    int extremum = convertir_fecha(elements[i]->fecha), imin = i;

    if (left < n && convertir_fecha(elements[left]->fecha) < extremum) {
      extremum = convertir_fecha(elements[left]->fecha);
      imin = left;
    }
    if (right < n && convertir_fecha(elements[right]->fecha) < extremum) {
      extremum = convertir_fecha(elements[right]->fecha);
      imin = right;
    }

    if (extremum == convertir_fecha(elements[i]->fecha))
      return;
    else {
      swap(elements[i], elements[imin]);
      heapify_down2(imin);
    }
  }

  void heapify_up2(int i) {
    while (i > 0) {
      int parent = Parent(i);
      if (convertir_fecha(elements[parent]->fecha) >
          convertir_fecha(elements[i]->fecha)) {
        swap(elements[parent], elements[i]);
        i = parent;
      } else {
        break;
      }
    }
  }
};
