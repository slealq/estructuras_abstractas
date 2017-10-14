// arbol.h
#include<iostream>
#include<string>
#include<vector>
#include "cola2.h"

#ifndef CLASEARBOL
#define CLASEARBOL

using namespace std;

struct S_node{
  int dato;
  S_node *left;
  S_node *right;
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
    delete(dato, this->raiz);
  }
  
  void delete_tree(int dato, S_node * nodo){
    if(nodo->dato==dato){
      // En el nodo actual, el dato es el que se necesita
      // Primero hay que revisar si está o no
      
      // Si el nodo es hoja lo elimina
      
      // Si el nodo tiene un hijo entonces
      // el hijo ocupa ese espacio
      
      // Tiene dos hijos Se busca el sucesor
      // en orden y  este pasa a sustituir
      // el nodo que se elimina
      

    }
    else{
      // El nodo actual no contiene el dato que necesito
      delete(dato, nodo->left);
      delete(dato, nodo->right);
    }
    
  }// delete

  void insertComplete(int dato){
    // Insertar para mantener un
    // arbol completo
  }// insertComplete

  void printTree(void){
    // imprimir con forma de arbol
    S_node * nodo = this->raiz;
    string dash_izq = "/";
    string dash_der = "\\";
    string enter = "\n";
    string espacio = "  ";
    C_cola2<S_node*> cola;
    cout << "arbol a mano" << endl;
    cout << nodo->dato << endl;
    cout << nodo->left->dato << endl;
    cout << nodo->right->dato << endl;
    cout << nodo->left->left->dato << endl;
    cout << nodo->left->left->left->dato << endl;

    cout << "" << endl;
    cola.agregar(nodo);
    while(cola.is_empty() == false){
      nodo = cola.quitar();
      if(nodo==NULL){
	cout << "NULL" << endl;
	continue;
      }
      cout << nodo->dato << endl;
      if(nodo->left){
	cola.agregar(nodo->left);
      }//if
      else{
	cola.agregar(NULL);
      }
      if(nodo->right){
	cola.agregar(nodo->right);
      }//if
      else{
	cola.agregar(NULL);
      }
      delete nodo;
    }
    cout << "" << endl;
    
  }// printTree
};



#endif
