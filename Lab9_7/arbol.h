// arbol.h
#include<iostream>
#include<string>
#include<vector>
#include "cola2.h"
//#include<stack>
#include<queue>

#ifndef CLASEARBOL
#define CLASEARBOL

using namespace std;

struct S_node{
  int dato;
  S_node *left;
  S_node *right;
  // nuevo arbol
  int height;
};

class C_BinTree {
 protected:
  S_node *raiz;
 public:
  C_BinTree(void){
    this->raiz = NULL;
  }
  ~C_BinTree(void){
    // Destructor
    delete raiz;
  }
  void insertBST(int dato){
    // Cover para insertar un dato desde arriba
    insertBST(dato, this->raiz);
  }
  
  void insertBST(int dato, S_node * nodo){
    // Si existe raiz :
    if(raiz){
      int temporal;
      temporal = nodo->dato;
      // Si el dato que se desea insertar es menor que el actual se incertara a la izquierda, caso contrario se hara a la derecha
      if(dato<=temporal){
	if(nodo->left){
	  // nodo->left tiene algo
	  insertBST(dato, nodo->left);
	  return;
	}// if nodo->left
	else{
	  // nodo->left no tiene nada
	  S_node *aux;
	  aux = new S_node;
	  aux->dato = dato;
	  aux->right = NULL;
	  aux->left = NULL;
	  nodo->left = aux;
	  return;
	}//else
      }//if temporal <= dato
      
      if(dato>temporal){
	if(nodo->right){
	  // nodo->right tiene algo
	  insertBST(dato, nodo->right);
	  return;
	}// if nodo->right
	else{
	  // nodo->right no tiene nada
	  S_node *aux;
	  aux = new S_node;
	  aux->dato = dato;
	  aux->right = NULL;
	  aux->left = NULL;
	  nodo->right = aux;
	  return;
	}//else
	// si el nodo en el que se quiere insertar existe, se itera sobre este como en el punto 2
	
      }//if temporal->dato
    }//if raiz
    else{
      // Si no existe raiz el nodo se insertara como raiz
      // Raiz == NULL
      S_node *aux;
      aux = new S_node;
      aux->dato = dato;
      aux->right = NULL;
      aux->left = NULL;
      this->raiz = aux;
      return;
    }
  }
  void preorder(void){
    // DLR
    preorder(this->raiz);
  }
  void preorder(S_node * nodo){
    // DLR
    if(nodo){
      // aca nodo existe osea no es NULL
      cout << nodo->dato << endl;
      preorder(nodo->left);
      preorder(nodo->right);
    }
  }
  void inorder(void){
    // LDR
    inorder(this->raiz);
  }
  void inorder(S_node * nodo){
    if(nodo){
      inorder(nodo->left);
      cout << nodo->dato << endl;
      inorder(nodo->right);
    }
  }
  void postorder(void){
    // LRD
    postorder(this->raiz);
  }
  void postorder(S_node * nodo){
    if(nodo){
      postorder(nodo->left);
      postorder(nodo->right);
      cout << nodo->dato << endl;
    }
  }
  int height(void){
    return height(this->raiz);
  }
  int height(S_node * nodo ){
    if(nodo){
      int l_height = height(nodo->left);
      int r_height = height(nodo->right);
      if (l_height > r_height){
	return (l_height+1);
      }
      else {
	return (r_height+1);
      }//else
      
    }
    else{
      return 0;
    }
  }// height snode

  void delete_tree(int dato){
    // Funcion dummy para iniciar recursion
    //    cout << "Aqui" << endl;
    delete_tree(dato, this->raiz);
  }
  
  bool delete_tree(int dato, S_node * nodo){
    //    cout << "Entre" << endl;
    // Si en el siguiente nodo esta el dato:
    if(!nodo){
      // Si en lo que estoy no es un nodo entonces devolverme
      return false;
    }


    //    cout << nodo->left->dato << endl;
    // Si el nodo a la derecha tiene el valor deseado hay que evaluar tres cosas    
    if((nodo->right && nodo->right->dato == dato) || (nodo->left && nodo->left->dato == dato)){
      S_node * hijo;
      //      S_node * temp;
      if(nodo->left){
	hijo = nodo->left;
	
      }
      else{
	hijo = nodo->right;
      }

      if(!hijo->left && !hijo->right){
	// nodo hoja
	if(nodo->left){
	  nodo->left = NULL;
	}
	else{
	  nodo->right = NULL;
	}
	//hijo = NULL;
	return true;
      }

      if((!hijo->left && hijo->right) || (!hijo->right && hijo->left)){
	// nodo solo tiene un hijo
	//	cout << "Caso de solo un hijo" << endl;
	if(hijo->left){
	  // El unico hijo es el izquierdo, entonces el izquierdo sube
	  if(nodo->left){
	    nodo->left = hijo->left;
	  }
	  else{
	    nodo->right = hijo->left;
	  }//else
	}//if hijo left
	else{
	  // hijo->right
	  if(nodo->left){
	    nodo->left = hijo->right;
	  }
	  else{
	    nodo->right = hijo->right;
	  }
	}//else
	return true;
      }

      if(hijo->left && hijo->right){
	S_node * temp;
	S_node * aux = new S_node();
	temp = hijo->left;
	while(!temp){
	  // Mientras temp no sea null
	  temp = temp->left;
	}
	int nuevo_dato = temp->left->dato;
	aux->dato = nuevo_dato;
	delete temp->left;
	temp->left = NULL;
	
	
	if(nodo->left){
	  aux->left = nodo->left->left;
	  aux->right = nodo->left->right;
	  nodo->left = aux;
	}// if nodo left
	else{
	  aux->left = nodo->right->left;
	  aux->right = nodo->right->right;
	  nodo->right = aux;
	} // else nodo left
	return true;
      }
      

      delete hijo;
      return true;
    }
    if(delete_tree(dato, nodo->right)){
      return true;
    }
    if(delete_tree(dato, nodo->left)){
      return true;
    }
    return false;
  }// delete

  struct Trunk{
    Trunk *prev;
    string str;
    
    Trunk(Trunk *prev, string str)
    {
      this->prev = prev;
      this->str = str;
    }
  };

  // Helper function to print branches of the binary tree                                                                                                                                                                                                                         
  void showTrunks(Trunk *p){
    if (p == nullptr)
      return;
    
    showTrunks(p->prev);
    
    cout << p->str;
  }

  void printTree(void){
    printTree(this->raiz, nullptr, false);
  }

  void printTree(S_node *root, Trunk *prev, bool isLeft)
  {
    if (root == nullptr)
      return;
    
    string prev_str = "     ";
    Trunk *trunk = new Trunk(prev, prev_str);
    
    printTree(root->left, trunk, true);
    
    if (!prev)
      trunk->str = "---";
    else if (isLeft)
      {
	trunk->str = ".---";
	prev_str = "   |";
      }
    else
      {
	trunk->str = "`---";
	prev->str = prev_str;
      }
    
    showTrunks(trunk);
    cout << root->dato << endl;
    
    if (prev)
      prev->str = prev_str;
    trunk->str = "   |";
    
    printTree(root->right, trunk, false);
  }
  
  void insertComplete(int dato){
    // Insertar para mantener un
    // arbol completo
    // Si se puede insertar de tal forma
    // Que no se aumente la altura
    // Entonces se inserta ahi
    S_node * aux = new S_node();
    aux->dato = dato;
    aux->left = NULL;
    aux->right = NULL;

    insertComplete(aux, this->raiz);

  }// insertComplete


  bool insertComplete(S_node * nodo_nuevo, S_node * nodo){
    // Se prueba si en el nodo actual, hay
    // un espacio en nodo->left o nodo->right
    // si no se entra en recursion
    

    queue<S_node*> cola;

    //    cola.agregar(nodo);
    cola.push(nodo);
    while(cola.empty() == false){
      //nodo = cola.quitar();
      nodo = cola.front();
      cola.pop();
      if(nodo==NULL){
	//cout << "NULL" << endl;
	continue;
      }
      //cout << nodo->dato << endl;
      if(!nodo->left){
	nodo->left = nodo_nuevo;
	return true;
      }

      if(!nodo->right){
	nodo->right = nodo_nuevo;
	return true;
      }

      if(nodo->left){
	cola.push(nodo->left);
	//cola.agregar(nodo->left);
      }//if
      else{
	nodo->left = nodo_nuevo;
	return true;
      }
      if(nodo->right){
	cola.push(nodo->right);

      }//if
      else{
	nodo->right = nodo_nuevo;
	return true;
	//cola.agregar(NULL);
      }
      //delete nodo;
    }
  }

  void printTree_test(void){
    // imprimir con forma de arbol
    S_node * nodo = this->raiz;
    string dash_izq = "/";
    string dash_der = "\\";
    string enter = "\n";
    string espacio = "  ";
    //int piso = height() - 1;
    
    
    queue<S_node*> cola;

    //    cola.agregar(nodo);
    cola.push(nodo);
    while(cola.empty() == false){
      //nodo = cola.quitar();
      nodo = cola.front();
      cola.pop();
      if(nodo==NULL){
	cout << "NULL" << endl;
	continue;
      }
      cout << nodo->dato << endl;
      if(nodo->left){
	cola.push(nodo->left);
	//cola.agregar(nodo->left);
      }//if
      else{
	cola.push(NULL);
	//cola.agregar(NULL);
      }
      if(nodo->right){
	cola.push(nodo->right);
	//cola.agregar(nodo->right);
      }//if
      else{
	cola.push(NULL);
	//cola.agregar(NULL);
      }
      delete nodo;
    }
    cout << "" << endl;
    
  }// printTree


  void printBranches(int loop, int whitespaces){
    for(int i=0; i<loop; i++){
      
    }

  }// printBranches
  
};



#endif
