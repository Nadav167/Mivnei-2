#pragma once
#include <memory>

class Node {
        Node* parent;
        int id;
        int genreChanges;

    public:
        explicit Node(int id) : id(id), parent(nullptr),genreChanges(0) {}
        ~Node() = default;
        Node* getParent();
        int getGenreChanges();
        int getId();
        void updateGenreChange();
        void setGenreChanges(int changes);
        void setParent(Node* parent);
    };

    int Node::getId() {
        return this->id;
    }
    int Node::getGenreChanges() {
        return this->genreChanges;
    }
    void Node::setGenreChanges(int changes) {
        this->genreChanges = changes;
    }
    void Node::updateGenreChange(){
        this->genreChanges++;
    }

    Node<T> *Node::getParent() {
        return parent;
    }

    void Node::setParent(Node* parent){
        this->parent = parent;
    }
};



