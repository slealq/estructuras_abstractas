#include "../Lab4/pila.h"
#include "../Lab4/base.h"
#include "../Lab7/arbol_avl.h"

void agregar_en_cola(C_base<int> * puntero1, C_base<int> * puntero2, int dato){

  // la primera pila solo se usa para guardar
  puntero1->agregar(dato);

  // la segunda pila se usa solo para cuando se necesita imprimir

}

int quitar_en_cola(C_base<int> * puntero1, C_base<int> * puntero2){

  // puntero 1 tiene todos los datos

  int temp = puntero1->quitar();
  while(temp!=0){
    puntero2->agregar(temp);
    temp = puntero1->quitar();
  }

  return puntero2->quitar();
}

void probar_cola(void){
  // Funcion main que llama a los helper functions
  C_pila<int> pila1;
  C_pila<int> pila2;
  C_base<int> *puntero1;
  C_base<int> *puntero2;

  puntero1 = &pila1;
  puntero2 = &pila2;

  cout << "Agregar secuencia 1,2....10" << endl;
  for(int i=1; i<=10; i++){
    agregar_en_cola(puntero1, puntero2, i);
  }//for

  for(int j=1; j<=10; j++){
    cout << quitar_en_cola(puntero1, puntero2) << endl;
  }//for
  
}

void probar_arbol(void){
  // Funcion para probar el devolver el mas cercano
  C_AVLTree arbolito;

  for(int i=2; i<=120; i++){
    arbolito.insertAVL(i);
  }

  cout << "El arbolito se ve asi" << endl;

  arbolito.printTree();

  cout << " Devolver el más cercano de 40" << endl;
  cout << arbolito.devolver_cercano(40) << endl;
  
}

int main(void) {
  probar_cola();
  probar_arbol();
  
};
