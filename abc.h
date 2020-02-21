#ifndef ABC_H
#define ABC_H

#include <iostream>
#include <cstring>
#include "list.h"

using namespace std;

class abc{
public:
  abc();//constructor
  ~abc();
  List* getQueue();
  void setQueue(List*);
  void makePostfix();
  void makeTree(List*);
  void infixTool(Node*);
  void postfixTool(Node*);
  void prefixTool(Node*);
private:
  bool isOperator(char);
  int precedence(char);
  bool stillPlaying;
  List* stack;
  List* operatorStack;
  List* expressionQueue;
};

#endif //ABC_H
