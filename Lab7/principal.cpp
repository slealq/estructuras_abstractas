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

  cout << "Vamos a insertar varios datos mas: 6, 40, 4, 7, 2" << endl;
  cout << endl;
  arbol.insertAVL(6);
  arbol.insertAVL(40);
  arbol.insertAVL(4);
  arbol.insertAVL(7);
  arbol.insertAVL(2);

  arbol.printTree();
  cout << endl;

  cout << "Ahora vamos a borrar un nodo con dos hijos: 19" << endl;
  arbol.deleteAVL(19);

  cout << endl;
  cout << "Resultado: " << endl;

  cout << endl;
  arbol.printTree();
  cout << endl;

  cout << "Borrar otro nodo con dos hijos: 4" << endl;
  arbol.deleteAVL(4);

  cout << endl;
  cout << "Resultado: " << endl;

  cout << endl;
  arbol.printTree();
  
  cout << endl;
}

int main(void)
{
  prueba3();

}
