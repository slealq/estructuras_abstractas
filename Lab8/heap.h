// heap.h
#include<iostream>
#include<vector>

#ifndef CLASEARBOL
#define CLASEARBOL

using namespace std;

// vector

class C_Heap {
 protected:
  vector<int> heap;
  int htype; // 0 es max 1 es min
 private:
  int leftChild(int i){
    //devuelve la pos del left child
    int resultado = 2*i+1;
    if(resultado<capacity()){
      return resultado;
      
    }

    else{
      return -1;
    }

  }

  int rightChild(int i){
    //devuleve la pos del right child
    int resultado = 2*i+2;
    if(resultado<capacity()){
      return resultado;
    }
    
    else{
      return -1;
    }
    
  }

  int percolate_down(int ipos){
    if(htype == 0){
      // max heap type
      int mayor = ipos; // se supone el nodo como el mayor
      if(heap[leftChild(ipos)] > heap[mayor]){
	// si el hijo izquierdo es mayor
	mayor = leftChild(ipos);
      }//if left child
      
      if(heap[rightChild(ipos)] > heap[mayor]){
	mayor = rightChild(ipos);
      }// if right child
      
      if(mayor == ipos){
	// no hice nada entonces me devuelvo
	return 0;
      }
      else{
	int temp = heap[ipos];
	heap[ipos] = heap[mayor];
	heap[mayor] = temp;
	percolate_down(mayor);
      }//else
    }// htype == 0

    if(htype == 1){
      if(leftChild(ipos)==-1||rightChild(ipos)==-1){
	return 0;
      }
      int menor = ipos; // se supone el nodo como el menor
      if(heap[leftChild(ipos)] < heap[menor]){
	// si el hijo izquierdo es mayor
	if(heap[leftChild(ipos)]!=-1){
	  menor = leftChild(ipos);
	}
      }//if left child
      
      if(heap[rightChild(ipos)] < heap[menor]){
	if(heap[rightChild(ipos)]!=-1){
	  menor = rightChild(ipos);
	}
      }// if right child
      
      if(menor == ipos){
	// no hice nada entonces me devuelvo
	return 0;
      }
      else{
	int temp = heap[ipos];
	heap[ipos] = heap[menor];
	heap[menor] = temp;
	percolate_down(menor);
      }//else

      
    }// htype == 1
  }
  
 public:
  C_Heap(int inthtype, int capacidad=1){
    //
    heap.resize(capacidad);
    htype = inthtype;
    for(int i = 0; i<heap.size(); i++){
      heap[i] = -1;
    }
  }

  ~C_Heap(void){
    // destructor
  }

  int getMax(void){
    return heap[0]; 
    
  }

  void print_heap(void){
    cout << "\nHeap: " << endl;
    for(int i=0; i<heap.size(); i++){
      cout << heap[i];
      cout << " " ;
    }//for
    cout << endl;
    cout << endl;
  }

  void delMax(void){
    heap[0] = heap[heap.size()-1];
    heap[heap.size()-1] = -1;
    percolate_down(0);
  }

  void insert(int dato){
    int pos = 0;
    bool espacio = false;
    for(int i=0; i<heap.size(); i++){
      //buscar el primer espacio vacio
      if(heap[i] == -1){
	pos = i;
	espacio = true;
	break;
      }//if
    }//for

    if(!espacio){
      cout << "No hay espacio para insertar" << endl;
      return;
    }
    
    heap[pos] = dato;

    // heapyfing
    for(int i = count()/2 -1; i>=0; i--){
      percolate_down(i);
    }
    
  }

  int capacity(void){
    // debería de volver cantidad de datos
    return heap.capacity();
  }

  void resize(int isize){
    // hay dos casos
    // esta el caso donde es reducir
    int contador;
    contador = capacity();
    
    heap.resize(isize);

    if(isize > contador){
      // es una expansion, entonces tengo que agregar ceros
      for(int i = contador; i<isize; i++){
	heap[i] = -1;
      }
    }
    
    // y aumentar 
  }

  int count(void){
    //devuelve la cantidad de elementos en el heap
    int counter = 0;
    for(int i=0; i<heap.size(); i++){
      if(heap[i] != -1){
	counter +=1;
      }//if
    }//for

    return counter;
  }
};

#endif
