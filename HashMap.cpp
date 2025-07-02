
#include "HashMap.h"
#include <stdexcept>
#include <iostream>

Node* HashMap::insert(int num){
    if(this->numObjects == this-> size){
        this->reHash();
    }
    int i = hash(num);
    while(array[i].key != 0){
        if(array[i].key == num){
            throw MyFailure();
        }
        i = (i+1) % this-> size;
    }
    array[i].key = num;
    array[i].data = new Node(num);
    this->numObjects++;
    return array[i].data;
}

int HashMap::hash(int num){
    return num % this->size;
}

void HashMap::reHash(){
    int tempSize = this->size;
    this->size = tempSize * 2;
    object* tempArray = array;
    this->array = new object[this->size];
    this->numObjects = 0;
    for(int i = 0; i < tempSize; i++){
        this->insert(tempArray[i].key);
    }
    delete[] tempArray;
}

int HashMap::getSize(){
    return this->size;
}

int HashMap::getNumObjects(){
    return this->numObjects;
}

Node* HashMap::find(int num){
    int i = hash(num);
    int j = i;
    while((array[i].key != num)){
        i = (i+1) % this-> size;
        if (i == j){
            throw MyFailure();
        }
    }
    return array[i].data;
}
HashMap::~HashMap() {
    for (int i = 0; i < size; ++i) {
        if (array[i].data != nullptr) {
            delete array[i].data;
        }
    }
    delete[] array;
}