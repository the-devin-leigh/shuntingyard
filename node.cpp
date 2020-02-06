#include <iostream>
#include "node.h"

using namespace std;

Node::Node(){
}

Node::~Node(){ //destructor
  delete &data;
}

char* getData(Node* n){
  return data;
}

Node* Node::getLeft(){
  return left;
}

Node* Node::getRight(){
  return right;
}
