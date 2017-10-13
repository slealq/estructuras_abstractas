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
  S_celda *anterior;
};

template <typename T>
class C_base {
 protected:
  //S_celda<T>* ultimo_elemento;
  S_celda<T>* primer_elemento;
  int contador;
 public:
  C_base(void);
  virtual ~C_base(void){
    //cout << "Destructor de base" << endl;
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
    S_celda<T> *paux;
    paux = this->primer_elemento; // Guardar el valor de primer elemento en una variable auxiliar
    while (this->primer_elemento != paux)
      {
	quitar();
      }
    this->primer_elemento = NULL;
    //this->ultimo_elemento = NULL;
    contador = 0;
    return true;
  }
  
  virtual bool invert(void){
    S_celda<T>* paux;
    S_celda<T>* prev_mem;
    S_celda<T>* pos_mem;
    
    prev_mem = this->primer_elemento->anterior;
    pos_mem = this->primer_elemento; // Este es el actual básciamente

    // Hasta que el siguiente elemento sea de nuevo primer elemento
    do {  // Iniciar el primer ciclo
      // Paux el el siguiente elemento
      paux = pos_mem;
      // siguiente elemento va a ser el interior de paux
      pos_mem = paux->proximo;
      // Ahora el elemento prev es el elemento proximo
      paux->proximo = prev_mem;
      // Esto debería de apuntar el anterior al proximo
      paux->anterior = pos_mem;
      prev_mem = paux;
    } while(pos_mem != this->primer_elemento);
    
    
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
  //this->ultimo_elemento=NULL;
  contador = 0;
}

#endif
