#pragma once
#include <memory>

class Node {
        Node* parent;
        int id;
        int genreChanges;

    public:
    	explicit Node(int id) : parent(nullptr), id(id), genreChanges(0) {}
        ~Node() = default;
        Node* getParent() const;
        int getGenreChanges() const;
        int getId() const;
        void updateGenreChange();
        void setGenreChanges(int changes);
        void setParent(Node* parent);
};



