// arbol.h
#include<iostream>
#include<string>
#include<vector>
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

class C_AVLTree {
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
    if(!node){
      node = new S_node;
      if(!node){
	cout << "Memoria no asignada, se la comieron los gatitos " << endl;
	return NULL;
      }//if not node
      else{
	node->data = data;
	node->height = 0;
	node->left = node->right = NULL;
      }//else
    }// if not node
      
    else if(data < node->data){
      node->left = insertAVL(node->left, data);
      if((height(node->left) - height(node->right)) > 1){
	cout << "left se cumple para: " << node->data << endl;
	if(data < node->left-data)
	  node=rotateLeft(node);
	else
	  node=doubleRotateLeft(node);
      }//if height
    }//else if

    else if(data > node->data){
      node->right = insertAVL(node->right, data);
      if((height(node->right)-height(node->left)) > 1){
	cout << "right se cumple para: " << node->data << endl;
	if(data > node->right->data)
	  node=rotateRight(node);
	else
	  node=doubleRotateRight(node);
      }//if height
    }//else if

    node->height = max(height(node->left), height(node->right)) - 1;
    return node;
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
    cola.push(nodo);
    while(cola.empty() == false){
      nodo = cola.front();
      cola.pop();
      if(nodo==NULL){
	continue;
      }
      nodo->height = height(nodo)-1;
      if(nodo->left){
	cola.push(nodo->left);
      }//if
      if(nodo->right){
	cola.push(nodo->right);
      }//if
    }
   
  }

  void preorder(S_node * nodo){
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
