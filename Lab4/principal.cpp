#include "pila.h"
#include "cola2.h"

int main (void)
{

  C_pila<int> vpila;
  C_cola2<int> vcola;
  C_base<int> *pBase;
  C_base<int> *pBase_C;
  
  pBase = &vpila;
  pBase_C = &vcola;

  for (int i=100; i<110; ++i)
  {
  	pBase->agregar(i);
  }

    for (int i=100; i<110; ++i)
  {
  	pBase_C->agregar(i);
  }

    pBase_C->agregar(100, 4);
    pBase_C->quitar(5);
    

  cout <<"\n Resultado para la pila"<<endl;
  for (int i=0; i<10; ++i)
    {
      cout << i <<"-) " << pBase->quitar() << endl;
    }

  pBase_C->count();
  pBase_C->invert();

  cout <<"\n Resultado para la cola"<<endl;
  for (int i=0; i<10; ++i)
    {
      cout << i <<"-) " << pBase_C->quitar() << endl;
    }



  for (int i=100; i<110; ++i)
  {
        pBase->agregar(i);
  }
  
  pBase -> invert();

  cout <<"\n Hay "<<pBase->count() << " elementos"<<endl;
  
  cout <<"\n Resultado para la pila invertida"<<endl;
  for (int i=0; i<10; ++i)
    {
      cout << i <<"-) " << pBase->quitar() << endl;
    }

}

