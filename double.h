#ifndef DOUBLY_H
#define DOUBLY_H
#include <iostream>
#include "list.h"
using namespace std;

// TODO: Implement all methods
template <typename T>
class DoubleList : public List<T> {
private:
    Node<T>* head;
    Node<T>* tail;
    int nodes;

public:
    DoubleList() : List<T>() {
        head = nullptr;
        tail = nullptr;
        nodes = 0;
    }

    ~DoubleList(){
        // TODO
        delete tail;
        while(head != nullptr){
            Node<T> * temp = head;
            head = head ->next;
            delete temp;
        }
        delete head;
        nodes = 0;
    }
    typedef ListIterator<T> Iterator;

    Iterator begin() {
        return Iterator(this, this->head);
    }

    Iterator end() {
        return Iterator(this, nullptr);
    }

    T front(){
        try{
            if(is_empty()) throw(nodes);
            return head->data;
        }
        catch(int nodes){
            cout << "No se puede obtener el front de un lista de " << nodes << " elementos\n";
            return T{};
        }
    }

    T back(){
        try{
            if(is_empty()) throw(nodes);
            return tail->data;
        }
        catch(int nodes){
            // cout << "No se puede obtener el back de un lista de " << nodes << " elementos\n";
            return T{};
        }
    }

    void push_front(T data){

        auto * temp = new Node<T>(data);
        temp->next = head;
        if(!is_empty()) {
            head->prev = temp;
        }else tail = temp;
        head = temp;
        temp->prev = nullptr;
        nodes++;

    }

    void push_back(T data){
        auto * node = new Node<T> (data);
        if(is_empty()){
            push_front(data);
            return;
        }
        node->next = nullptr;
        tail->next = node;
        node->prev = tail;
        tail = node;
        nodes++;
    }

    T pop_front(){
        try{
            if(is_empty()) throw(nodes);
            nodes--;
            Node<T> * temp = head;
            head = head->next;
            T data = temp->data;
            delete temp;
            if(!nodes) tail = nullptr;
            else head->prev = nullptr;
            return data;
        }
        catch(int nodes){
            cout << "No se puede eliminar elementos en una lista de "<<nodes << " elementos\n";
            return T{};
        }
    }


    T pop_back(){
        try {
            if(is_empty()) throw(nodes);
            nodes--;
            if(!nodes){
                tail = nullptr;
                T data = head->data;
                delete head;
                head = nullptr;
                return data;
            }
            Node<T> * temp = tail;
            T data = temp->data;
            tail = tail->prev;
            temp->prev->next = nullptr;
            delete temp;
            return data;
        }
        catch(int nodes){
            cout << "No se puede eliminar elementos en una lista de "<<nodes << " elementos\n";
            return T{};
        }
    }

    void insert(T data, int pos){
        if(pos>=nodes){
            push_back(data);
        }
        if(pos <=0){
            push_front(data);
        }
        pos--;
        nodes++;
        auto * nodo = new Node<T>(data);
        Node<T> * temp = head;
        while(pos--){
            temp = temp -> next;
        }
        temp->next->prev = nodo;
        nodo->next = temp->next;
        nodo->prev = temp;
        temp->next = nodo;
    }

    bool remove(int pos){
        if(pos>=nodes || pos<0) return false;
        nodes--;
        if(!pos){
            pop_front();
            return true;
        }
        if(pos==nodes){
            pop_back();
            return true;
        }
        if(pos <= abs(nodes-pos)){
            pos--;
            Node<T> * temp = head;
            while(pos--){
                temp = temp -> next;
            }
            Node<T> * to_eliminate = temp->next;
            temp->next->next->prev = temp;
            temp->next = temp->next->next;
            delete to_eliminate;
            return true;
        }else{
            pos = nodes-pos-1;
            Node<T> * temp = tail;
            while(pos--){
                temp = temp->prev;
            }
            Node<T> * to_eliminate = temp->prev;
            temp->prev->prev->next = temp;
            temp->prev = temp->prev->prev;
            delete to_eliminate;
            return true;
        }
    }

    T& operator[](int pos){
        if(pos>=nodes || pos<0) throw "error";
        if(pos <= abs(nodes-pos)){
            Node<T> * temp = head;
            while(pos--){
                temp = temp -> next;
            }
            return temp->data;
        }else{
            pos = nodes-pos-1;
            Node<T> * temp = tail;
            while(pos--){
                temp = temp->prev;
            }
            return temp->data;
        }
    }

    bool is_empty(){return !nodes;}

    int size(){return nodes;}

    void clear(){
        while(head != nullptr){
            Node<T> * temp = head;
            head = head ->next;
            delete temp;
        }
        nodes = 0;
        tail = nullptr;
    }

    Node<T> * &  merge(Node<T> * &l1,Node<T> * &l2){
        auto * sorted_temp = new Node<T> (0);
        Node<T> * current_node = sorted_temp;
        while(l1 != nullptr && l2 != nullptr){
            if(l1->data < l2->data){
                current_node->next = l1;
                l1 = l1->next;
            }else{
                current_node->next = l2;
                l2 = l2->next;
            }
            current_node = current_node->next;
        }
        if(l1!= nullptr){
            current_node->next = l1;
            l1 = l1->next;
        }
        if(l2!= nullptr){
            current_node->next = l2;
            l2 = l2->next;
        }
        return sorted_temp->next;
    }

    Node<T> * & merge_sort(Node<T> * &temp_head){
        if(temp_head == nullptr || temp_head->next == nullptr) {
            return temp_head;
        }
        Node<T> * temp = temp_head;
        Node<T> * slow = temp_head;
        Node<T> * fast = temp_head;

        while(fast!= nullptr && fast->next != nullptr){
            temp = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        temp->next = nullptr;
        Node<T> * left_side = merge_sort(temp_head);
        Node<T> * right_side = merge_sort(slow);
        return merge(left_side,right_side);
    }

    void sort(){
        head = merge_sort(head);
        Node<T> * temp = head;
        Node<T> * temp1 = temp->next;
        while(temp1!=nullptr){
            temp1->prev = temp;
            temp = temp->next;
            temp1 = temp1->next;
        }
        tail = temp;
        head->prev= nullptr;
    }

    bool is_sorted(){
        if (is_empty()) return false;
        Node<T> * first = head;
        Node<T> * second = first->next;
        while(second!=nullptr){
            if(first->data > second->data){
                return false;
            }
            first = first->next;
            second = second->next;
        }
        return true;
    }

    void reverse(){
        Node<T> * temp = head;
        int temp_ca = nodes;
        for(int i = 0; i < temp_ca;i++){
            push_front(temp->data);
            temp = temp->next;
        }
        while(temp_ca--){
            pop_back();
        }
    }

    std::string name(){
        return "DoubleList";
    }
        
};
#endif
