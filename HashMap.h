#pragma once
#include "Node.h"
#include <exception>

class MyFailure : public std::exception {};

class HashMap {
    struct object{
        int key;
        Node* data;
        int genreSize;
        object(): key(0), data(nullptr), genreSize(0){}

    };
    private:
        int size;
        object* array;
        int numObjects;
        int hash(int num);
        void reHash();


    public:
        HashMap(): size(7),numObjects(0) {
            this->array = new object[size];
        }
        ~HashMap();
        Node* insert(int num, Node* temp = nullptr);
        Node* find(int num);
        int getSize();
        int getNumObjects();
};






