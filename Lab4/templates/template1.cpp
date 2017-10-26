#include <iostream>
#include <string>

using namespace std;

template <typename T>
inline T const& Max (T const& a, T const& b) { 
   return a < b ? b:a; 
}

int main () {
   int i = 39000;
   int j = 20000;
   cout << "i=" << i << " \tj=" << j <<" \t=> Max(i, j): " << Max(i, j) << endl; 

   double f1 = 13.5; 
   double f2 = 20.7; 
   cout << "f1=" << f1 << " \tf2=" << f2 << " \t=> Max(f1, f2): " << Max(f1, f2) << endl; 

   string s1 = "Hello"; 
   string s2 = "World"; 
   cout << "s1=" << s1 << " \ts2=" << s2 << " \t=> Max(s1, s2): " << Max(s1, s2) << endl; 

   return 0;
}