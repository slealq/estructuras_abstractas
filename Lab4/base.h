/*********************************************************************
*
C_base.h
*********************************************************************
*/
#include<string>
#include<iostream>

using namespace std;

#ifndef CLASEBASE
#define CLASEBASE

template <typename T>
struct S_celda{
	T dato;
	S_celda *proximo;
};

template <typename T>
class C_base {
 protected:
  S_celda<T>* ultimo_elemento;
  S_celda<T>* primer_elemento;
  int contador;
 public:
  C_base(void);
  virtual ~C_base(void){
    cout << "Destructor de base" << endl;
  }
  virtual bool agregar(T){
    return false;
  }

  virtual bool agregar(T, int){
    return false;
  }

  virtual T quitar(int){
    return (T)0;
  }
    
  virtual T quitar(void){
    return (T)0;
  }
  
  virtual bool clear(void){
    while (this->primer_elemento != NULL)
      {
	quitar();
      }
    return true;
  }
  
  virtual bool invert(void){
    S_celda<T>* paux;
    S_celda<T>* prev_mem;
    S_celda<T>* pos_mem;
    
    prev_mem = NULL;
    pos_mem = this->primer_elemento;
    
    while(pos_mem != NULL){
      paux = pos_mem;
      pos_mem = paux->proximo;
      paux->proximo = prev_mem;
      prev_mem = paux;
    }
    
    this->primer_elemento = prev_mem;
    
    return true;
  }
  
  virtual int count(void){
    return contador;
  }
};

template <typename T>
C_base<T>::C_base(void)
{
  this->primer_elemento=NULL;
  this->ultimo_elemento=NULL;
  contador = 0;
}

#endif
