#include "cola2.h"
#include <stack>

int main(void){
  std::stack<int> stack; 
  C_cola2<int> cola;
  for(int i=0; i<10; i++){
    //cola.agregar(i);
    stack.push(i);
    //cout << stack.top() << endl;
    //stack.pop();
    //cout << cola.quitar(i) << endl;
  }
  for(int i=0; i<10; i++){
    cout << stack.top() << endl;
    stack.pop();
    //cout << cola.quitar(i) << endl;
  }
};
