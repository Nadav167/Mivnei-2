
#include "Node.h"
int Node::getId() const {
    return this->id;
}
int Node::getGenreChanges() const {
    return this->genreChanges;
}
void Node::setGenreChanges(int changes) {
    this->genreChanges = changes;
}
void Node::updateGenreChange(){
    this->genreChanges++;
}

Node* Node::getParent() const {
    return parent;
}

void Node::setParent(Node* parent){
    this->parent = parent;
}