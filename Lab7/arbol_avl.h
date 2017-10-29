// arbol.h
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<stdlib.h>

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

struct Trunk{
  Trunk *prev;
  string str;
  
  Trunk(Trunk *prev, string str)
  {
    this->prev = prev;
    this->str = str;
  }
};

class C_AVLTree {
 protected:
  S_node *raiz;
 public:
  C_AVLTree(void){
    this->raiz = NULL;
  }
  ~C_AVLTree(void){
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

  void insertAVL(int data){
    this->raiz = insertAVL(this->raiz, data);
  }
  
  void deleteAVL(int data){
    this->raiz = deleteAVL(this->raiz, data);
  }

  int devolver_cercano(int dato){
    int temp = dato;
    int diff = 0;
    S_node * nodo = this->raiz;
    // agregar diff
    diff = abs(dato-nodo->dato);

    queue<S_node*> cola;
    cola.push(nodo);
    while(cola.empty() == false){
      nodo = cola.front();
      cola.pop();
      if(nodo==NULL){
	continue;
      }

      if(abs(dato-nodo->dato) < diff){
	// la diferencia entre temp y el nuevo dato es menor
	diff = abs(dato-nodo->dato);
	temp = nodo->dato;
      }

      if(diff==1){
	return temp;
      }
      
      if(nodo->left){
	cola.push(nodo->left);
      }//if
      if(nodo->right){
	cola.push(nodo->right);
      }//if
    }
    return temp;
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
	node->dato = data;
	node->height = 0;
	node->left = node->right = NULL;
      }//else
    }// if not node
      
    else if(data < node->dato){
      node->left = insertAVL(node->left, data);
      if((height(node->left) - height(node->right)) > 1){
	cout << "left se cumple para: " << node->dato << endl;
	if(data < node->left->dato)
	  node=rotateLeft(node);
	else
	  node=doubleRotateLeft(node);
      }//if height
    }//else if

    else if(data > node->dato){
      node->right = insertAVL(node->right, data);
      if((height(node->right)-height(node->left)) > 1){
	cout << "right se cumple para: " << node->dato << endl;
	if(data > node->right->dato)
	  node=rotateRight(node);
	else
	  node=doubleRotateRight(node);
      }//if height
    }//else if

    node->height = max(height(node->left), height(node->right));
    return node;
  }

  S_node * deleteAVL(S_node * node, int data){
    if(!node){
      return NULL;
    }

    if(data < node->dato)
      node->left = deleteAVL(node->left, data);
    else if(data > node->dato)
      node->right = deleteAVL(node->right, data);
    else if(node->left && node->right)
      {
	// Tiene dos hijos
	// PASO 1: Encontrar max de la rama izq
	S_node * max = node->left;
	while(max->right)
	  max = max->right;
	// PASO 2: Copiar el dato
	node->dato = max->dato;

	// PASO 3: Recursivo borrar ese nodo
	node->left = deleteAVL(node->left, max->dato);
	
      }
    else
      {
	// es hoja o tiene solo un hijo
	S_node * paux;
	paux = node->left ? node->left : node->right;
		
	if(paux == NULL){
	  // ningun hijo
	  paux = node;
	  node = NULL;
	}//if paux

	else{
	  // tiene un hijo
	  *node = *paux;
	}
	delete paux;
      }
    
    if(!node)
      return node;

    // Balancear
    if((height(node->left)-height(node->right)) > 1)
      {
	cout << "left se cumple para: "<< node->dato << endl;
	if(node->dato > node->left->dato)
	  node = rotateLeft(node);
	else
	  node = doubleRotateLeft(node);
      }
    
    if((height(node->right)-height(node->left)) > 1)
      {
	cout << "right se cumple para: "<< node->dato << endl;
	if(node->dato < node->right->dato)
	  node = rotateRight(node);
	else
	  node = doubleRotateRight(node);
      }

    
    node->height = max(height(node->left), height(node->right));
    return node;
  }
  
  S_node * rotateRight(S_node * node){
    S_node * paux = node->right;
    node->right = paux->left;
    paux->left = node;
    node->height = max(height(node->left), height(node->right));
    paux->height = max(height(paux->left), height(paux->right));
    return paux;
  }

  S_node * doubleRotateRight(S_node * node){
    node->right = rotateLeft(node->right);
    return rotateRight(node);
  }

  S_node * rotateLeft(S_node * node){
    S_node * paux = node->left;
    node->left = paux->right;
    paux->right = node;
    node->height = max(height(node->left), height(node->right));
    paux->height = max(height(paux->left), height(paux->right));
    return paux;
  }

  S_node * doubleRotateLeft(S_node * node){
    node->left = rotateRight(node->left);
    return rotateLeft(node);
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
