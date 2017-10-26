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
		S_celda<T>* primer_elemento;
	public:
	C_base(void);
		virtual ~C_base(void){
			cout << "Destructor de base" << endl;
		}
		virtual bool agregar(T){
			return false;
		}
		virtual T quitar(void){
			return 0;
		}
};

template <typename T>
C_base<T>::C_base(void)
{
	this->primer_elemento=NULL;
}
#endif