#include <iostream>
#include <cstring>

#include "list.h"
#include "abc.h"
#include "node.h"

using namespace std;

abc::abc() {//constructor
  List* expressionQueue = new List();//initializes expressionQueue
  stillPlaying = true;
}

abc::~abc() {

}

void abc::infixTool(Node* binTree) {
  if (isOperator(*binTree->getOp())) {//if the op in the node is an operator
    cout << "( ";
  }else if (binTree->getBack() != NULL) {//if there is a back node
    infixTool(binTree->getBack());//recursivly call infix on the back node
  }else if (binTree->getFront() != NULL) {//if there is a front node
    infixTool(binTree->getFront());//recursivly call infixTool on the front node
  }else if (isOperator(*binTree->getOp())) {//if the op in the node is an operator
    cout << ") ";
  }else {
    cout << endl;
  }
  cout << binTree->getOp() << " ";//print out the op
}

void abc::postfixTool(Node* binTree) {
  if (binTree->isBack()) {//if there is a back node
    postfixTool(binTree->getBack());//recursivly call postifix on the back node
  }
  if(binTree->isFront()) {//if there is a front node
    postfixTool(binTree->getFront());//recursivly call postfix on the front node
  }
  cout << binTree->getOp() << " ";//print out the op in the node
}

void abc::prefixTool(Node* binTree) {
  cout << binTree->getOp() << " ";//print out the op in the node
  if (binTree->getBack() != NULL) {//if there is a back node
    prefixTool(binTree->getBack());//recursivly call prefix on the back node
  }
  if(binTree->getFront() != NULL) {//if there is a front node
    prefixTool(binTree->getFront());//recursivly call prefix on the front node
  }
}

List* abc::getQueue() {
  return expressionQueue; //returns the input queue
}

void abc::setQueue(List * newQ) {
  expressionQueue = newQ; //set expressionQueue equal to input
}

bool abc::isOperator(char op) { //returns true if it is an operator
 switch(op){
   case '+': return true;
   case '-': return true;
   case '*': return true;
   case '/': return true;
   case '^': return true;
   case '(': return true;
   case ')': return true;
   default: return false;
 }
}

int abc::precedence(char op) { //prededence of operator
  switch(op){
    case '+': return 2;
    case '-': return 2;
    case '*': return 3;
    case '/': return 3;
    case '^': return 4;
    default: return 0;
  }
}

void abc::makePostfix() {
  List* stack = new List();
  List* operatorStack = new List();

  //run through expressionQueue
  while (expressionQueue->empty() != true) {
    char* headOp = expressionQueue->getHead()->getOp();//operator at head
    if (!isOperator(*headOp)) { //first char not operator
      Node* newNode = new Node(headOp);//push head to stack
      stack->push(newNode);
      expressionQueue->dequeue();
    }else { //operator
      if (*headOp == '(') { //paren
	Node* newNode = new Node(headOp);
	operatorStack->push(newNode);
	expressionQueue->dequeue();
      }else if(*headOp != ')') { //not end paren
	int pred = precedence(*headOp); //precedence of op
	if (operatorStack->peek() != NULL) { //things in operator stack
	  if (pred != 1) {//as long as the prededence is not 1
	    while(operatorStack->peek() != NULL && precedence(*operatorStack->peek()->getOp()) > pred) { 
	      Node* newNode = new Node(operatorStack->peek()->getOp());
	      stack->push(newNode);
	      operatorStack->pop();
	    }
	    //push the incoming operator to the stack
	    Node* newNode = new Node(headOp);
	    operatorStack->push(newNode);
	    expressionQueue->dequeue();
	  }else {//if eaqual to 1 print this message
	    cout << "You entered an invalid operator" << endl;
	    return;
	  }
	}else {
	  //if there is nothing in the operator stack push straight to the stack
	  Node* newNode = new Node(headOp);
	  operatorStack->push(newNode);
	  expressionQueue->dequeue();
	}
      }else { //if end paren
	while (*operatorStack->peek()->getOp() != '(') {//while there isnt a ( at the top of the operator stack then
	  //push the items at the top of the operator stack to stack
	  Node* newNode = new Node(operatorStack->peek()->getOp());
	  stack->push(newNode);
	  operatorStack->pop();
	}
	//get rid of the ( and )
	expressionQueue->dequeue();
	operatorStack->pop();
      }
    }
  }
  while (operatorStack->empty() != true) {//while the operator stack is not empty
    //push items from the top of the operator stack to the stack
    Node* newNode = new Node(operatorStack->peek()->getOp());
    stack->push(newNode);
    operatorStack->pop();
  }
  Node* current = stack->getHead(); //set current to the head of stack
  List* expressionQueue = new List(); //reintialize the list
  while (0 != current) {//while the current node is not NULL
    //push the current node to the expressionQueue
    Node* newNode = new Node(current->getOp());
    expressionQueue->push(newNode);
    current = current->getNext();
  }
  makeTree(expressionQueue);//make the tree
}

void abc::makeTree(List* input) {
  List* tree = new List();//make new list for tree
  while (input->empty() != true) { //while the input is not empty
    if(isdigit(*input->peek()->getOp())) { //first char is number
      //push the input head to the tree list
      Node* filler = new Node(input->peek()->getOp());
      tree->push(filler);
      input->dequeue();
    }else {
      Node* currentNode = new Node(input->peek()->getOp());//create node for operator
      currentNode->setFront(tree->peek());//set front node to the head of tree
      tree->remove();//take the head out of tree
      currentNode->setBack(tree->peek());//set back node to the head of tree
      tree->remove();//take out the head of tree
      tree->push(currentNode);//add the operator to the tree
      input->dequeue();//take the head out of the input queue
    }
  }
  while (stillPlaying == true) {
    cout << "Do you want to see infix, postfix, prefix: ";
    char *choice = new char[50];
    cin.getline(choice, 50, '\n'); //get user input
    if (strcmp(choice, "infix") == 0) {//if input infix
      infixTool(tree->peek()); //run infix
      cout << endl;
      stillPlaying = false;
    }else if (strcmp(choice, "postfix") == 0) {//if input postfix
      postfixTool(tree->peek());//runs postfix 
      cout << endl;
      stillPlaying = false;
    }else if (strcmp(choice, "prefix") == 0) { //if input prefix
      prefixTool(tree->peek()); //runs prefix
      cout << endl;
      stillPlaying = false;
    }else {
      cout << "Invalid option." << endl;
    }
  }
}
