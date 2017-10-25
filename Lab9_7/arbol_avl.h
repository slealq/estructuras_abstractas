// arbol.h
#include<iostream>
#include<string>
#include<vector>
//#include "cola2.h"
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
  int height=0;
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

  void preorder(void){
    // DLR
    preorder(this->raiz);
  }
  void inorder(void){
    // LDR
    inorder(this->raiz);
  }
  void postorder(void){
    // LRD
    postorder(this->raiz);
  }
  
  int height(void){
    return height(this->raiz);
  }
  
  void printTree(void){
    printTree(this->raiz, nullptr, false);
  }

  
  
 private:
  
  S_node * insertAVL(S_node * node, int data){
    
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

  void showTrunks(Trunk *p){
    if (p == nullptr)
      return;
    
    showTrunks(p->prev);
    
    cout << p->str;
  }

  int height(S_node * nodo ){
    // tambien actualiza el height de todos los nodos 
    
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

  void update_height(void){
    // ir nodo por nodo y aplicar height
    S_node * nodo = this->raiz;
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
      nodo->height = height(nodo)-1;

      //cout << nodo->dato << endl;
      if(nodo->left){
	cola.push(nodo->left);
	//cola.agregar(nodo->left);
      }//if
      else{
	//cola.push(NULL);
	//cola.agregar(NULL);
      }
      if(nodo->right){
	cola.push(nodo->right);
	//cola.agregar(nodo->right);
      }//if
      else{
	//cola.push(NULL);
	//cola.agregar(NULL);
      }
      //delete nodo;
    }
   
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

  void inorder(S_node * nodo){
    if(nodo){
      inorder(nodo->left);
      cout << nodo->dato << endl;
      inorder(nodo->right);
    }
  }

  void postorder(S_node * nodo){
    if(nodo){
      postorder(nodo->left);
      postorder(nodo->right);
      cout << nodo->dato << endl;
    }
  }

  
  
};



#endif
