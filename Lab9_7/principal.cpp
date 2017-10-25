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

void prueba2(void){
  C_BinTree arbol;

  cout << endl;

  cout << "Insertando la secuencia: 8, 6, 15, 3, 19, 20" << endl;
  arbol.insertBST(8);
  arbol.insertBST(6);
  arbol.insertBST(15);
  arbol.insertBST(3);
  arbol.insertBST(19);

  cout << endl;

  cout << "Resultado" << endl;
  arbol.printTree();

  cout << endl;
  cout << "Rotacion izq en root" << endl;

  //cout << arbol->raiz->height << endl;

  cout << endl;
}


void prueba1(void){
  C_BinTree arbol;
  cout << endl;
  cout << "Insertando la secuencia 100, 80, 75, 85, 190, 60" << endl; 
  arbol.insertBST(100);
  arbol.insertBST(80);
  arbol.insertBST(75);
  arbol.insertBST(85);
  arbol.insertBST(190);
  arbol.insertBST(60);
  cout << endl;
  cout << "Resultado" << endl;
  arbol.printTree();
  cout << endl;
  cout << "Imprimiendo preorder, inorder, postorder" << endl;
  cout << " preorder " << endl;
  arbol.preorder();
  cout << " inorder " << endl;
  arbol.inorder();
  cout << " postorder " << endl;
  arbol.postorder();
  cout << endl;
  cout << "Imprimiendo el tamaño del arbol" << endl;
  cout << " tamaño " << endl;
  cout << arbol.height() << endl;
  cout << endl;
  cout << "Ahora se probara la funcion delete de la tarea" << endl;
  cout << "Arbol actual: " << endl;
  arbol.printTree();
  cout << endl;
  cout << " borrando 60 (Nodo hoja)" << endl;
  arbol.delete_tree(60);
  arbol.printTree();
  cout << endl;
  cout << "Ahora se vuelve a insertar 60, para eliminar 75" << endl;
  arbol.insertBST(60);
  cout << endl;
  cout << "Arbol actual: " << endl;
  arbol.printTree();
  cout << endl;
  cout << " borrando 75 (Nodo con solo un hijo)" << endl;
  arbol.delete_tree(75);
  arbol.printTree();
  cout << endl;
  cout << "Ahora se agregan dos numeros mas para probar el tercer caso" << endl;
  arbol.insertBST(75);
  arbol.insertBST(50);
  cout << endl;
  cout << "Arbol actual:" << endl;
  arbol.printTree();
  cout << endl;
  cout << "Borrando 80 (Nodo con dos hijos). Se agrega la hoja de mas a la izq" << endl;
  arbol.delete_tree(80);
  cout << endl;
  cout << "Arbol actual:" << endl;
  arbol.printTree();
  cout << endl;
  cout << "Finalmente se prueba el insertComplete. (Inserto 20)." << endl;
  arbol.insertComplete(20);
  cout << endl;
  cout << "Arbol actual " << endl;
  cout << endl;
  arbol.printTree();
  cout << endl;
  cout << "InsertComplete. (Inserto 30)." << endl;
  arbol.insertComplete(30);
  cout << endl;
  cout << "Arbol actual " << endl;
  cout << endl;
  arbol.printTree();
}

int main(void)
{
  prueba3();

}
