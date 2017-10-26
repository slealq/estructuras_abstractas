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
  //cout << "Destructor de cola2" << endl;
  while(this->primer_elemento != this->primer_elemento)
    quitar();
}


template <typename T>
bool C_cola2<T>::agregar(T mi_dato)
{

  this->contador+=1;
  S_celda<T> *paux;
  paux = new S_celda<T>;
  
  paux->dato=mi_dato;
  //  paux->proximo=this->primer_elemento;;
  //paux->anterior=
    
  if(this->primer_elemento==NULL){
    //this->primer_elemento->proximo = paux;
    //this->primer_elemento->anterior = paux;
    
    paux->proximo = paux;
    paux->anterior = paux;
    this->primer_elemento=paux;

  }
  else
    {
      paux->proximo = this->primer_elemento;
      paux->anterior = this->primer_elemento->anterior;
      this->primer_elemento->anterior->proximo = paux;
      this->primer_elemento->anterior = paux;
    }
  
  return true;
}

template <typename T>
T C_cola2<T>::quitar(void)
{
  this->contador -=1;
  int tdato=0;
  S_celda<T> *paux;

  if(this->primer_elemento!=this->primer_elemento->proximo){
    paux = this->primer_elemento;
    paux->anterior->proximo = paux->proximo;
    paux->proximo->anterior = paux->anterior;
    tdato = paux->dato;
    this->primer_elemento = paux->anterior;

    delete paux;
  }
  else
    {
      tdato = this->primer_elemento->dato;
      this->primer_elemento = NULL;
    }
  return tdato;
}

template <typename T>
T C_cola2<T>::quitar(int pos)
{
  int dato;

  S_celda<T> *paux1;
  S_celda<T> *paux2;
  //  S_celda<T> *paux3;
  
  paux1 = this->primer_elemento;
  paux2 = this->primer_elemento->proximo;
  //paux3 = this->primer_elemento->anterior;
  
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
  paux2->proximo->anterior = paux1;
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
  paux->proximo->anterior = paux;
  paux1->proximo = paux;
}

#endif
