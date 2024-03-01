#include <iostream>
#include <cstring>

using namespace std;

int main() {
  bool looping = true;
  char command[10];
  char input[10000];
  while(looping == true) {
    cout << "INPUT, PRE, POST, IN" << endl;
    cin.get(command, 10);
    cin.clear();
    cin.ignore(10000, '\n');
    if(strcmp(command, "INPUT") == 0) {
      cout << "Enter your input" << endl;
      cin.getline(input, 10000);
      //queue is a linked list where you save the head and tail, still single link(maybe a method to find the last node(which node points to null)
      //stack is a linked list where you save only the head(bottom of stack), still single link (find the last node that points to not null and then that is the top of stack;
      
