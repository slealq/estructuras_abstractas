#include "arbol.h"

int main(void)
{
  C_BinTree arbol;
  arbol.insertBST(100);
  arbol.insertBST(80);
  arbol.insertBST(75);
  arbol.insertBST(190);
  arbol.insertBST(60);
  cout << " preorder " << endl;
  arbol.preorder();
  cout << " inorder " << endl;
  arbol.inorder();
  cout << " postorder " << endl;
  arbol.postorder();
  cout << " tamaño " << endl;
  cout << arbol.height() << endl;
  arbol.printTree();
}
