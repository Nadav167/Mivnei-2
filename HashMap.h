#pragma once
#include "Node.h"

class HashMap {
    struct object{
        int key;
        int genreSize;
        Node* data;
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
        Node* insert(int num);
        Node* find(int num);
        int getSize();
        int getNumObjects();
};






