#include <iostream>
#include <string>
#include <typeinfo>


using namespace std;

template <class T>
class C_max{
	friend  ostream& operator<<(ostream &Output,const C_max<T> & x){
		Output<<"N1= "<<x.a<<" N2= "<<x.b;
 		return Output;
	} 
	protected:
		T a, b;	
	public:
		C_max(T n1, T n2) : a(n1),b(n2){}
		~C_max() {cout<<"Destructor padre "<<typeid(T).name()<<endl;}

		T max (void);
};

template <class T>
T C_max<T>::max (void) { 
   return this->a < this->b ? this->b:this->a; 
}


template<class T>
class C_updater : public C_max<T>
{
	public:
		C_updater(T x, T y) : C_max<T>(x,y){}
		~C_updater() {cout<<"Destructor hijo"<<endl;}

		bool updateVals(T x, T y);
};
template<class T>
bool C_updater<T>::updateVals(T x, T y){
	this->a=x;
	this->b=y;
}



int main () {
	C_updater<int> enteros(39000,20000);
   	cout <<"\nEnteros\n"<<enteros  <<" \t=> enteros.max(): " << enteros.max() << endl; 

   	enteros.updateVals(51000,77000);
   	cout <<"\nEnteros\n"<<enteros  <<" \t=> enteros.max(): " << enteros.max() << endl; 

   	C_updater<double> flotantes(13.5,20.7);
   	cout << "\nFlotantes\n" << flotantes << " \t=> flotantes.max(): " << flotantes.max() << endl; 

   	C_updater<string> caracteres("Hello","World");
   	cout << "\nstrings\n"<< caracteres <<" \t=> caracteres.max(): " << caracteres.max() <<"\n\n"<< endl; 

   	return 0;
}