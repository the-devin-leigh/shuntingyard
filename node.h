#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <cstring>

using namespace std;

class Node{
 public:
  Node();
  ~Node(); //destructor
  char* getData(Node* n); //returns char in node
  Node* getLeft(); //returns operator to left
  Node* getRight(); //returns operator to right
 private:
  char* data;
  Node* left;
  Node* right;
};

#endif
