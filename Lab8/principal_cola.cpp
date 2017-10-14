#include "cola2.h"

int main(void){
  C_cola2<int> cola;
  for(int i=0; i<10; i++){
    cola.agregar(i);
    cout << cola.quitar(i) << endl;
  }
  for(int i=0; i<10; i++){
    
    //cout << cola.quitar(i) << endl;
  }
};
