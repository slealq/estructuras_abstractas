#include "heap.h"

void test(void){
  // Probar el heap

  C_Heap heap_min = C_Heap(1, 20);
  C_Heap heap_max = C_Heap(0, 20);
  cout << "Insertando secuencia 0, 1, 2,.. 19" << endl;
  for(int i =0; i<20; i++){
    heap_min.insert(i);
    heap_max.insert(i);
  }
  cout << "Heap MAX: " << endl;
  heap_max.print_heap();

  cout << "Heap MIN: " << endl;
  heap_min.print_heap();
  
  cout << "De aca en adelante se probará sólo en HEAP MAX" << endl;

  cout << "Probar get max" << endl;
  cout << "Maximo: " << heap_max.getMax() << endl;

  cout << "Probar delete max" << endl;

  heap_max.delMax();
  heap_max.print_heap();

  cout << "Probar capacity" << endl;
  cout << "Capacity: " << heap_max.capacity() << endl;

  cout << "Probar count" << endl;
  cout << "Count: " << heap_max.count() << endl;

  cout << "Probar resize a 25" << endl;
  heap_max.resize(25);

  heap_max.print_heap();

  cout << "Probar resize a 10" << endl;
  heap_max.resize(5);

  heap_max.print_heap();
  
  
}

int main(void){
  test();
  
};
