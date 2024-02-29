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
      
      
