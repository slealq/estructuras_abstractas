#include "base.h"

#ifndef CLASECOLA
#define CLASECOLA

template <typename T>
class C_cola2 : public C_base<T>{
 public:
  C_cola2(void);
  ~C_cola2(void);
  bool push(T);
  T pull(void);
  bool agregar(T);
  T quitar(void);
  bool agregar(T, int);
  T quitar(int);

};

template <typename T>
C_cola2<T>::C_cola2(void) : C_base<T>()
{
  //ultimo_elemento = NULL;
}

template <typename T>
C_cola2<T>::~C_cola2(void) 
{
   cout << "Destructor de cola2" << endl;
   while(this->primer_elemento != NULL)
   	quitar();
}


template <typename T>
bool C_cola2<T>::agregar(T mi_dato)
{

  this->contador+=1;
  S_celda<T> *paux;
  paux = new S_celda<T>;
  
  paux->dato=mi_dato;
  paux->proximo=NULL;
  
  if(this->primer_elemento==NULL){
    this->primer_elemento=paux;
    this->ultimo_elemento=paux;
  }
  
  else{
    this->ultimo_elemento->proximo=paux;
    this->ultimo_elemento=paux;
  }
  
  return true;
}

template <typename T>
T C_cola2<T>::quitar(void)
{
  this->contador -=1;
  int tdato=0;
  S_celda<T> *paux;
  
  if(this->primer_elemento!=NULL){
    paux=this->primer_elemento;
    
    tdato=this->primer_elemento->dato;
    this->primer_elemento=this->primer_elemento->proximo;
    delete paux;
  }
  return tdato;
}

template <typename T>
T C_cola2<T>::quitar(int pos)
{
  int dato;

  S_celda<T> *paux1;
  S_celda<T> *paux2;

  paux1 = this->primer_elemento;
  paux2 = this->primer_elemento->proximo;
 
  if(pos > this->count()){
    return (T) 0;
  }
  else {
    for(int i = 0; i<pos-2; i++){
      paux1 = paux2;
      paux2 = paux2 -> proximo;
    } 
  }

  dato = paux2->dato;
  paux1->proximo = paux2->proximo;
  delete paux2;
  
  return dato;

}

template <typename T>
bool C_cola2<T>::agregar(T mi_dato, int pos)
{
  S_celda<T> *paux1;
  S_celda<T> *paux2;

  paux1 = this->primer_elemento;
  paux2 = this->primer_elemento->proximo;
  
  if(pos > this->count()+1){
    return false;
  }
  else{
    for(int i = 0; i<=pos; i++){
      paux1 = paux2;
      paux2 = paux2->proximo;
    }
  }

  S_celda<T> *paux;
  paux = new S_celda<T>;

  paux->dato = mi_dato;
  paux->proximo = paux1->proximo;
  paux1->proximo = paux;
}

#endif
