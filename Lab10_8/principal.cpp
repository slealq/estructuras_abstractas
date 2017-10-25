#include "heap.h"

int main(void){
  C_Heap heap = new C_Heap(0, 3);

  // probar el heap
  for(int i=0; i<10; i++){
    cout << endl;
    heap.insert(i);
  }

  
  
};
