#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "elapsed_time.h"

using namespace std;

void copiar(vector<int> &original, vector<int> &copia)
{
  copia.resize(original.size());
  for(int i=0; i<original.size(); i++){
    copia[i] = original[i];
  }
}

void bubble_sort(vector<int> &respuesta)
{
  int n = respuesta.size();

  bool swapped=true;
  int temp;
  while(swapped)
    { 
      swapped = false;
      for(int i=1; i<n; i++)
	{
	  // si esta fuera de orden
	  if(respuesta[i-1] > respuesta[i])
	    {
	      temp = respuesta[i-1];
	      respuesta[i-1] = respuesta[i];
	      respuesta[i] = temp;
	      swapped = true;
	    }//if
	}//for
    }//while
}//bubble sort

void insertion_sort(vector<int> &array)
{
  int n = array.size();
  int i = 1;
  int j;
  int temp;
  while(i < n)
    {
      j = i;
      while( (j>0) && (array[j-1] > array[j]))
	{
	  temp = array[j-1];
	  array[j-1] = array[j];
	  array[j] = temp;
	  j-=1;
	}//while
      i+=1;
    }//while
}

void counting_sort(vector<int> &array)
{
  int n = array.size();

  vector<int> output;
  vector<int> count;
  count.resize(10000);
  output.resize(n);

  // contar cada elemento
  for(int i=0; i<n; i++)
    {
      count[array[i]] += 1;
    }

  // Ir sumando el anterior
  for(int i=1; i<10000; i++)
    {
      count[i] += count[i-1];
    }

  // Ahora contruir la respuesta
  for(int i=0; i<n; i++)
    {
      output[count[array[i]]-1] = array[i];
      count[array[i]] -= 1;
    }

  // copiar
  copiar(output, array);
  
}//couting sort

vector<int> probar_algoritmo(vector<int> &array, int selection)
{
  // 0 = Bubble sort
  // 1 = Insertion Sort
  // 2 = Counting sort
  // 3 = Heap Sort
  // 4 = Radix Sort
  // 5 = Quick Sort
  vector<int> respuesta;
  E_time tiempo;
  copiar(array, respuesta);

  tiempo.start();

  switch(selection)
    {
    case 0 :
      bubble_sort(respuesta);
      break;
    case 1 :
      insertion_sort(respuesta);
      break;
    case 2:
      counting_sort(respuesta);
      break;
    }
  
  tiempo.stop();
  cout << "Duración en ms: " ;
  cout << tiempo.elapsed().count() << endl;

  return respuesta;
  
}

void pprint(vector<int> array)
{
  int n = array.size();
  for(int i=0; i<n; i++)
    {
      cout << array[i];
      cout << " ";
    }
  cout << endl;
  
}

void comparar(vector<int> original, vector<int> respuesta)
{
  cout << "Vector original: " << endl;
  pprint(original);
  cout << "Vector respuesta: " << endl;
  pprint(respuesta);
}


void random_fill(vector<int> &array, int size)
{
  array.resize(size);
  for(int i=0; i<size; i++)
    {
      array[i] = rand() % 100;
    }//for
}

int main(void)
{
  // NOTA:
  // LOS COMPARAR SE PUEDEN USAR PARA
  // VER QUE LAS RESPUESTAS SEAN CORRECTAS
  vector<int> array;
  vector<int> response;

  random_fill(array, 10);

  // pruebas de funcionamiento ================================
  cout << " \t \t Pruebas de funcionamiento: " << endl << endl;
  
  // prueba del bubble
  cout << "BUBBLE SORT" << endl;
  response = probar_algoritmo(array, 0);
  comparar(array, response);

  // Enter
  cout << endl;
  
  // prueba del insertion
  cout << "INSERTION SORT" << endl;
  response = probar_algoritmo(array, 1);
  comparar(array, response);

  // Enter
  cout << endl;
  
  // prueba del counting
  cout << "COUNTING SORT" << endl;
  response = probar_algoritmo(array, 2);
  comparar(array, response);

  
  // pruebas de tiempo ========================================
  cout << endl << " \t \t Pruebas de tiempo con 10k números: " << endl << endl;

  random_fill(array, 10000);
  
  // prueba del bubble
  cout << "BUBBLE SORT" << endl;
  response = probar_algoritmo(array, 0);
  //comparar(array, response);

  // Enter
  cout << endl;
  
  // prueba del insertion
  cout << "INSERTION SORT" << endl;
  response = probar_algoritmo(array, 1);
  //comparar(array, response);

  // Enter
  cout << endl;
  
  // prueba del counting
  cout << "COUNTING SORT" << endl;
  response = probar_algoritmo(array, 2);
  //comparar(array, response);

  // Enter
  cout << endl;
};
