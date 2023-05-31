#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
   T data;
    Node<T>* next;
    Node<T>* prev;
// constructor 
    Node(){ 
        next = nullptr;
        prev = nullptr;
        data = 0;
    }
    Node(T value){
        data = value;
        next = nullptr;
        prev = nullptr;
    }
// destructor
    void killSelf(){
        delete this;      
    }    
};

#endif
