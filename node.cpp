#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

Node::Node() { //Constructor
  left = NULL;
  right = NULL;
  next = NULL;
  data = '\0';
}

Node::~Node() { //Destructor
  
}

//Setters
void Node::setRight(Node* newRight) {
  right = newRight;
}

void Node::setLeft(Node* newLeft) {
  left = newLeft;
}

void Node::setNext(Node* newNext) {
  next = newNext;
}

void Node::setData(char newData) {
  data = newData;
}

//Getters
Node* Node::getRight() {
  return right;
}

Node* Node::getLeft() {
  return left;
}

Node* Node::getNext() {
  return next;
}

char Node::getData() {
  return data;
}
