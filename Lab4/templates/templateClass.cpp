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

	private:
		T a, b;	
	public:
		C_max(T n1, T n2) : a(n1),b(n2){}
		~C_max() {cout<<"Destructor "<<typeid(T).name()<<endl;}

		T max (void);
};

template <class T>
T C_max<T>::max (void) { 
   return this->a < this->b ? this->b:this->a; 
}

/*template <class T>
 ostream& operator<< <T>(ostream &Output,const C_max<T> &x){
 	Output<<"N1= "<<x.a;
 	return Output;
 }*/

int main () {
	C_max<int> enteros(39000,20000);
   	cout <<"\nEnteros\n"<<enteros  <<" \t=> enteros.max(): " << enteros.max() << endl; 

   	C_max<double> flotantes(13.5,20.7);
   	cout << "\nFlotantes\n" << flotantes << " \t=> flotantes.max(): " << flotantes.max() << endl; 

   	C_max<string> caracteres("Hello","World");
   	cout << "\nstrings\n"<< caracteres <<" \t=> caracteres.max(): " << caracteres.max() <<"\n\n"<< endl; 

   	return 0;
}