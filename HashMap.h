#pragma once
#include "Node.h"
#include <exception>


class HashMap {
    struct object{
        int key;
        int genreSize;
        Node* data;
        object() : key(0), genreSize(0), data(nullptr) {}

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
class MyFailure : public std::exception {
public:
    const char* what() const noexcept override {
        return "MyFailure";
    }
};





