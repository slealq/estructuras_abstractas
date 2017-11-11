#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>

#ifndef CLASEHASH
#define CLASEHASH

using namespace std;

struct S_celda{
  int dato;
  S_celda *proximo;
  std::string value;
};

class C_Hash{
 protected:
  vector<S_celda*> tabla;
  int elementos;
  int capacidad;
  
 public:
  C_Hash(void);
  virtual ~C_Hash(void);
  virtual int hash_search(int cedula);
  virtual void hash_insert(int cedula, std::string value);
  virtual string hash_delete(int cedula);
  virtual float load_factor(void);
  virtual int hash(int number);
};

C_Hash::C_Hash(void)
{
  int capacidad = 101; //numero primo
  tabla.resize(capacidad, NULL);
}//contructor

C_Hash::~C_Hash(void)
{
  S_celda * paux;
  S_celda * siguiente;
  for(int i=0; i<capacidad; i++)
    {
      paux = tabla[i];
      while(paux){
	cout << paux << endl;
	siguiente = paux->proximo;
	delete paux;
	paux = siguiente;
      }//if
    }//for
}//destructor

int C_Hash::hash_search(int cedula)
{
  
}//hash search

void C_Hash::hash_insert(int cedula, string value)
{
  if(load_factor() > 0.9){
    // algo
  }
  
  int pos = hash(cedula);
  S_celda * primero = tabla[pos];

  S_celda * nuevo = new S_celda;
  nuevo->dato = cedula;
  nuevo->proximo = NULL;
  nuevo->value = value;
  
  if(!primero){
    tabla[pos] = nuevo;
  }//if

  S_celda * paux;
  
  if(primero){
    paux = primero;
    while(paux){
      paux = primero->proximo;
    }//while
    // paux es el ultimo
    paux = nuevo;
  }
}//hash insert

string C_Hash::hash_delete(int cedula)
{

}//hash delete

float C_Hash::load_factor(void)
{
  return elementos/capacidad;
}// load factor

int C_Hash::hash(int number)
{

  int total;
  vector<int> digits;

  while(number)
    {
      digits.push_back(number%10);
      number /= 10;

      std::reverse(digits.begin(), digits.end());
      total = std::accumulate(digits.begin(), digits.end(), 0);
    }

  return total%capacidad;
}// hash


#endif
