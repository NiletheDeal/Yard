#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

int main() {
  bool looping = true;
  char command[10];
  char input[100];
  Node* top = NULL;
  Node* front = NULL;
  Node* rear = NULL;
  while(looping == true) {
    for(int i = 0; i < 100; i++) {
      input[i] = '\0';
    }
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
	    inP = precedence(input[i]);
	    topP = precedence(top->getData);
	    if(topP  == 1 || topP == 2 || topP == 3) {//operators precedence check
	      if(top != NULL) {
		while(topP >= inP && *top->getData() != '(') {
		  enqueue(front, rear, top->getData());
		  pop(top);
		  topP = precedence(top->getData);
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
	      while(*top->getData() != '(') {
		enqueue(front, rear, top->GetData());
		pop(top);
	      }
	      if(*top->getData() == '(') {
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
      //queue is a linked list where you save the head and tail, still single link(maybe a method to find the last node(which node points to null)
      //stack is a linked list where you save only the head(bottom of stack), still single link (find the last node that points to not null and then that is the top of stack;
	  }
	}
      }
    }
    }
  }
}
void enqueue(Node*& front, Node*& rear, char* value) {
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
    temp->setNext(NUll);
  }
}
void push(Node*& top, char* value) {//add to the stack
  Node* temp = new Node();
  temp->setData(value);
  temp->setNext(top);
  top = temp;
}
int precedence(char* p) {
  if (*p == '^') {
    return 3; //Highest
  }
  else if (*p == '*' || *p == '/') {
    return 2; //Second highest
  }
  else if (*p == '+' || *p == '-') {
    return 1; //Second lowest
  }
  else if (*p == '(') {
    return 5; //Can be anything, as long as it is differentiated from the rest
  }
  else if (*p == ')') {
    return 6;
  }
  else {
    return 0; //Lowest, which are the numbers
  }
}
