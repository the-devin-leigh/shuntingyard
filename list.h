#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

class List{
public:
  List();
  ~List();
  void push(Node*); //push node to stack
  void pop(); //remove head from stack
  void remove(); //pops without deleting
  Node* peek(); //check head
  
  void enqueue(Node*); //adds to queue
  void dequeue(); //deletes data in queue
  bool empty(); //check if empty
  Node* getHead();
  Node* getTail();
private:
  Node* head;
  Node* tail;
};

#endif //LIST_H
