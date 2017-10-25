#include "arbol_avl.h"

void prueba3(void){
  C_AVLTree arbol;
  cout << endl;

  cout << "Insertando la secuencia: 8, 6, 15, 3, 19, 20" << endl;

  arbol.insertAVL(8);
  arbol.insertAVL(6);
  arbol.insertAVL(15);
  arbol.insertAVL(3);
  arbol.insertAVL(19);
  arbol.insertAVL(20);
  
  cout << endl;

  cout << "Resultado: " << endl;
  arbol.printTree();

  cout << endl;
  cout << "Prueba: Borrar hoja: 3" << endl;
  arbol.deleteAVL(3);
    
  arbol.printTree();

  cout << endl;
  cout << "Ahora voy a introducir el 3 de nuevo" << endl;
  arbol.insertAVL(3);

  arbol.printTree();
  cout << endl;

  cout << "Ahora borro el nodo 6: 1 hijo" << endl;
  arbol.deleteAVL(6);
  
  
  arbol.printTree();
  
  cout << endl;
}

int main(void)
{
  prueba3();

}
