#include <vector>
#include <queue>
#include <iostream>

int sumar(int a, int b){
  return a + b;
}

int factorial(std::vector<int> &resultados, int n){

  if(resultados[n]!=0){
    return resultados[n];
  }//if

  if(n==0){
    return resultados[n] = 1;
  }//n=0

  if(n==1){
    return resultados[n] = 1;
  }//n=1

  return resultados[n] = n * factorial(resultados, n-1);
  
}//factorial

int main(void) {
  std::vector<int> v {10, 5, 100, 50, 20, 15};
  std::priority_queue<int, std::vector<int>, std::greater<int>> pqMIN;

  for(int i = 0; i<v.size(); i++){
    std::cout << "metiendo el valor: " << v[i] << std::endl;
    pqMIN.push(v[i]);
  }//for

  std::cout << "Se inicializo el vector con los valores de prueba" << std::endl;

  // se suman los primeros minimos, y luego se va sumando con el siguiente

  int total=0;
  int anterior;
  int actual;
  std::vector<int> resultados;
  resultados.resize(200, 0);

  anterior = pqMIN.top();
  pqMIN.pop();
  
  while(!pqMIN.empty()){
    actual = pqMIN.top();
    pqMIN.pop();
    std::cout << "valor anterior " << anterior << std::endl;
    std::cout << "valor actual " << actual << std::endl;
    anterior = sumar(actual, anterior);
    total+= anterior;
    //anterior = pqMIN.top();
    //pqMIN.pop();
  }

  std::cout << "El total seria: " << total << std::endl;

  for(int i=0; i<10; i++) {
    std::cout << "El factorial de " << i << " es : " << factorial(resultados, i) << std::endl; 
  }
} //main
