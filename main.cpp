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
int main() {
  bool looping = true;
  char command[10];
  char input[100];
  Node* top = NULL;
  Node* front = NULL;
  Node* rear = NULL;
  char value;
  while(looping == true) {
    cout << "INPUT, PRE, POST, IN" << endl;
    cin.get(command, 10);
    cin.clear();
    cin.ignore(10000, '\n');
    if(strcmp(command, "INPUT") == 0) {
      cout << "Enter your input" << endl;
      cin.getline(input, 100);
      cin.clear();
      cin.ignore(10000, '\n');
      int inputCount = 0;
      top = NULL;
      front = NULL;
      rear = NULL;
      for(int i = 0 ; i < strlen(input); i++) {
	if(input[i] != ' ') {
	  if(isdigit(input[i])) {
	    enqueue(front, rear, input[i]);
	  }
	  else {
	    int inP = precedence(input[i]);
	    int topP = precedence(top->getData());
	    if(topP  == 1 || topP == 2 || topP == 3) {//operators precedence check
	      if(top != NULL) {
		while(topP >= inP && top->getData() != '(') {
		  enqueue(front, rear, top->getData());
		  pop(top);
		  topP = precedence(top->getData());
		  if(top ==NULL) {
		    break;
		  }
		}
	      }
	      push(top, input[i]);//Add the input to the stack  
	    }
	    if(topP == 5) {//left parenthesises just add
	      push(top, input[i]);
	    }
	    if(topP == 6) {//right parenthesises pop the stack till the matched parentheseses
	      while(top->getData() != '(') {
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
      while(top != NULL) {//move the stack to the queue at the end
	enqueue(front, rear, top->getData());
	pop(top);
      }
      Node* tree = NULL;//top of the tree stack
      while(front != rear) {
	value = front->getData();
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
	front = front->getNext();
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
      while(check == false) {
	cout << "Display Option: IN for infix notation, POST for postfix notation, PRE for prefix notation" << endl;
	cin.get(command, 10);
	cin.clear();
	cin.ignore(10000, '\n');
	if(strcmp(command, "IN") == 0) {
	  disInfix(tree);
	  check = true;
	}
	else if(strcmp(command, "POST") == 0) {
	  disPostfix(tree);
	  check =true;
	}
	else if(strcmp(command, "PRE") == 0) {
	  disPrefix(tree);
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
    cout << "Empty" << endl;
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
    if (InF != NULL) {
        if (precedence(InF->getData()) != 0) {
            cout << "( ";
        }
        disInfix(InF->getLeft());
        cout << InF->getData() << " ";
        disInfix(InF->getRight());
        if (precedence(InF->getData()) != 0) {
            cout << ") ";
        }
    }
}

void disPrefix(Node* PreF) { //Display Prefix Function
    if (PreF != NULL) {
        cout << PreF->getData() << " ";
        disPrefix(PreF->getLeft());
        disPrefix(PreF->getRight());
    }
}

void disPostfix(Node* PosF) { //Display Postfix Function
    if (PosF != NULL) {
        disPostfix(PosF->getLeft());
        disPostfix(PosF->getRight());
        cout << PosF->getData() << " ";
    }
}
