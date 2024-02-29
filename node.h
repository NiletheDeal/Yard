#ifndef NODE_H
#define NODE_H

using namespace std;

class Node {
 public:
  Node(); //Constructor
  ~Node(); //Destructor
  //Setters
  void setRight(Node*);
  void setLeft(Node*);
  void setNext(Node*);
  void setData(char*);
  //Getters
  Node* getRight();
  Node* getLeft();
  Node* getNext();
  char* getData();
 private:
  Node* left;
  Node* right;
  Node* next;
  char* data;
 
};
#endif
