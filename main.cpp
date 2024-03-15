//Neel Madala
//3/15/12024
//This program takes in a function puts it through the shunting yard alogrithm and then into a binary expression tree. Then allows the user to print out their function in Infix, Postfix, or Prefix notation

#include <iostream>
#include <cstring>
#include <cctype>
#include "node.h"
using namespace std;
void enqueue(Node*& front, Node*& rear, char value);
void dequeue(Node*& front, Node*& rear);
bool isEmpty(Node* front, Node*rear);
void pop(Node*& top);
void push(Node*& top, char value);
int precedence(char p);
void pushTree(Node*& top, Node* tree);
void disInfix(Node* InF);
void disPrefix(Node* PreF);
void disPostfix(Node* PosF);
void displayQueue(Node* front, Node* rear);
void print(Node* tree, int count);
int main() {
  bool looping = true;
  char command[10];
  char input[100];
  Node* top = NULL;
  Node* front = NULL;
  Node* rear = NULL;
  char value;
  while(looping == true) {//using the program
    cout << "INPUT or QUIT" << endl;
    cin.get(command, 10);
    cin.clear();
    cin.ignore(10000, '\n');
    if(strcmp(command, "INPUT") == 0) {
      cout << "Enter your input" << endl;
      cin.getline(input, 100);
      cin.clear();
      cout << strlen(input) << endl;
      top = NULL;
      front = NULL;
      rear = NULL;
      for(int i = 0 ; i <= strlen(input); i++) {//goes through each char in the input
	if(input[i] != ' ') {//Not a  space
	  if(isdigit(input[i])) {//if a number add to queue
	    cout << input[i] << endl;
	    enqueue(front, rear, input[i]);
	  }
	  else {
	    int inP = precedence(input[i]);
	    if(top == NULL) {//if the stack is empty add value to it
	      cout << input[i] << endl;
	      push(top, input[i]);
	    }
	    else {//if the stack has something on it
	      int topP = precedence(top->getData());
	      if(inP  == 1 || inP == 2 || inP == 3) {//operators precedence check if the operator is greater precedence then what you are gonna add to it in which case move the top of the stack to the queue until it is less or you reach (
		if(top != NULL) {
		  while(topP >= inP && top->getData() != '(') {
		    topP = precedence(top->getData());
		    
		    enqueue(front, rear, top->getData());
		    pop(top);
		    if(top ==NULL) {//end of list stop
		      break;
		    }
		  }
		}
		cout << input[i] << endl;
		push(top, input[i]);//Add the input to the stack  
	      }
	      else if(inP == 5) {//left parenthesises just add
		cout << input[i] << endl;
		push(top, input[i]);
	      }
	      else if(inP == 6) {//right parenthesises pop the stack till the matched parentheseses
		while(top->getData() != '(') {
		  cout << "This isn't happening" << endl;
		  enqueue(front, rear, top->getData());
		  pop(top);
		}
		if(top->getData() == '(') {
		  pop(top);
		}
	      }
	    }
	  }
	}
      }
      
      
      while(top != NULL) {//move the stack to the queue at the end
	cout << "test4" << top->getData() << endl;
	enqueue(front, rear, top->getData());
	pop(top);
      }
      cout << "Queue is: " << endl;
      displayQueue(front, rear);
      Node* tree = NULL;//top of the tree stack
      while(front != rear) {
	value = front->getData();
	int vP = precedence(value);
	if(vP == 0) {//if the value is a number
	  cout << "test" << endl;
	  push(tree, value);//just push it to the tree
	}
	else {
	  Node* temp = new Node();
	  temp->setData(value);
	  //tree->setNext(NULL);
	  temp->setRight(tree);
	  pop(tree);
	  //tree->setNext(NULL);
	  temp->setLeft(tree);
	  pop(tree);
	  pushTree(tree, temp);
	}
	front = front->getNext();
	print(tree, 0);
      }
      //Rear Node
      value = rear->getData();
      int vP = precedence(value);
      if(vP = 0) {
	push(tree, value);
      }
      else {
	Node* temp = new Node();
	temp->setData(value);
	temp->setRight(tree);
	pop(tree);
	temp->setLeft(tree);
	pop(tree);
	pushTree(tree, temp);
      }
      bool check = false;
      cout << "Binary Expansion Tree Done" << endl << endl;
      int count  = 0;
      print(tree, count);
      while(check == false) {
	cout << "Display Option: IN for infix notation, POST for postfix notation, PRE for prefix notation" << endl;
	cin.get(command, 10);
	cin.clear();
	cin.ignore(10000, '\n');
	if(strcmp(command, "IN") == 0) {
	  disInfix(tree);
	  cout << endl << endl;
	  check = true;
	}
	else if(strcmp(command, "POST") == 0) {
	  disPostfix(tree);
	  cout << endl << endl;
	  check =true;
	}
	else if(strcmp(command, "PRE") == 0) {
	  disPrefix(tree);
	  cout << endl << endl;
	  check = true;
	}
	else {
	  cout <<"Input invalid" << endl;
	}
      }
    }
    else if (strcmp(command, "QUIT") == 0) {
      cout << "Done!" << endl;
      looping = false;
    }
    else {
      cout << "Invalid Input" << endl;
    }
  }
}
void enqueue(Node*& front, Node*& rear, char value) {
  Node* temp = new Node();
  temp->setData(value);
  temp->setNext(NULL);
  if(front == NULL) { //Empty queue
    front = temp;
    rear = temp;
  }
  else {
    rear->setNext(temp);
    rear = temp;
  }
}
void dequeue(Node*& front, Node*& rear) {
  if(isEmpty(front, rear)) {
    cout << "Empty queue" <<endl;
  }
  else if (front == rear) {
    //delete both nodes
    front == NULL;
    rear == NULL;
  }
  else {
    Node* temp = front;
    front = front->getNext();
    temp->setNext(NULL);
  }
}
bool isEmpty(Node* front, Node*rear) {
  if(front == NULL && rear == NULL) {
    return true;
  }
  else{
    return false;
  }
}
void pop(Node*& top) {//remove the top node
  if(top == NULL) {
    cout << "Empty1" << endl;
  }
  else {
    Node* temp = top;
    top = top->getNext();
    temp->setNext(NULL);
  }
}
void push(Node*& top, char value) {//add to the stack
  Node* temp = new Node();
  temp->setData(value);
  temp->setNext(top);
  top = temp;
}
int precedence(char p) {
  if (p == '^') {
    return 3; //Highest
  }
  else if (p == '*' || p == '/') {
    return 2; //Second highest
  }
  else if (p == '+' || p == '-') {
    return 1; //Second lowest
  }
  else if (p == '(') {
    return 5; //Can be anything, as long as it is differentiated from the rest
  }
  else if (p == ')') {
    return 6;
  }
  else {
    return 0; //Lowest, which are the numbers
  }
}
void pushTree(Node*& top, Node* tree) {//gonna add a node to the tree stack instead of adding data value, makes it so that can give the nodes children
   tree->setNext(top);
   top = tree;
}
//Display tree functions
void disInfix(Node* InF) { //Display Infix Function
  if (InF->getLeft() != NULL) {
    disInfix(InF->getLeft());
  }
  cout << InF->getData();
  if(InF->getRight() != NULL) {
    disInfix(InF->getRight());
  }
  return;
}

void disPrefix(Node* PreF) { //Display Prefix Function
  cout << PreF->getData();
  if(PreF->getLeft() != NULL) {
    disPrefix(PreF->getLeft());
  }
  if(PreF->getRight() != NULL) {
    disPrefix(PreF->getRight());
  }
  return;
}

void disPostfix(Node* PosF) { //Display Postfix Function
  if (PosF->getLeft() != NULL) {
        disPostfix(PosF->getLeft());
  }
  if(PosF->getRight() != NULL) {
    disPostfix(PosF->getRight());
  }
  cout << PosF->getData();
  return;
}
void displayQueue(Node* front, Node* rear) { //DisplayQueue function
    if (isEmpty(front, rear)) {
        cout << "Empty queue" << endl;
    }
    else {
        Node* temp = front;
        while (temp != NULL) {
            cout << temp->getData() << " ";
            temp = temp->getNext();
        }
        cout << endl;
    }
}
void print(Node* tree, int count) {//print out tree
  if(tree->getRight() != NULL) {//get to the right child 
    print(tree->getRight(), count+1);
  }
  for(int i = 0; i < count; i++) {//tabs over
    cout << '\t';
  }
  cout << tree->getData() << endl;//print out value
  //left side
  if(tree->getLeft() != NULL) {//get to the left child
    print(tree->getLeft(), count+1);
  }
}
