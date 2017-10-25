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

  cout << endl;

  cout << "Resultado: " << endl;
  arbol.printTree();

  cout << endl;
}

int main(void)
{
  prueba3();

}
