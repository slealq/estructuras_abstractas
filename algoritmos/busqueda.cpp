#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "elapsed_time.h"

using namespace std;

// METODOS PARA EL HEAP SORT

int leftChild(int i, int n){
  //devuelve la pos del left child                                            
  int resultado = 2*i+1;
  if(resultado<n){
    return resultado;
    
  }
  
  else{
    return -1;
  }
  
}

int rightChild(int i, int n){
  //devuleve la pos del right child                                           
  int resultado = 2*i+2;
    if(resultado<n){
      return resultado;
    }
    
    else{
      return -1;
    }
}

int percolate_down(int ipos, vector<int> &heap, int n, int htype=0){
  if(leftChild(ipos, n)==-1||rightChild(ipos, n)==-1){
    //return 0;
  }
  
  if(htype == 0){
    // max heap type                                             
    int mayor = ipos; // se supone el nodo como el mayor          
    if(heap[leftChild(ipos, n)] > heap[mayor]){
      // si el hijo izquierdo es mayor                           
      mayor = leftChild(ipos, n);
    }//if left child                                            
    if(heap[rightChild(ipos, n)] > heap[mayor]){
      mayor = rightChild(ipos, n);
    }// if right child                                          
    if(mayor == ipos){
      // no hice nada entonces me devuelvo                       
      return 0;
    }
    else{
      int temp = heap[ipos];
      heap[ipos] = heap[mayor];
      heap[mayor] = temp;
      percolate_down(mayor, heap, n);
    }//else                                        
  }// htype == 0                                                
  if(htype == 1){
    int menor = ipos; // se supone el nodo como el menor        
    if(heap[leftChild(ipos, n)] < heap[menor]){
        // si el hijo izquierdo es mayor                         
      if(heap[leftChild(ipos, n)]!=-1){
	menor = leftChild(ipos, n);
        }
      }//if left child                                           
      
    if(heap[rightChild(ipos, n)] < heap[menor]){
      if(heap[rightChild(ipos, n)]!=-1){
	menor = rightChild(ipos, n);
        }
      }// if right child                                     
      
      if(menor == ipos){
        // no hice nada entonces me devuelvo                     
        return 0;
      }
      else{
        int temp = heap[ipos];
        heap[ipos] = heap[menor];
        heap[menor] = temp;
        percolate_down(menor, heap, n);
      }//else
  }// htype == 1                                        
}

void heapify(vector<int> &heap,int n)
{
  for(int i = n/2 -1; i>=0; i--){
    percolate_down(i, heap, n);
  }
}

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

void heap_sort(vector<int> &heap)
{
  int temp;
  int n = heap.size();
  heapify(heap, n);
  int end = n-1;
  while(end>0)
    {
      temp = heap[0];
      heap[0] = heap[end];
      heap[end] = temp;
      end -=1;
      n-=1;
      percolate_down(0, heap, n);
    }//while
}//heap sort

// método de ayuda para el radix.
void list_to_buckets(vector<vector<int>> &bucket, vector<int> &array, int iteration, int base=10)
{
  //vector<vector<int>> bucket;
  bucket.resize(base);
  for(int i=0; i<array.size(); i++)
    {
      int number = array[i];
      //cout << "NUMBER: " << number << endl;
      int digit = (int)floor(number / pow(base, iteration)) % base;
      //cout << "DIGIT: " << digit << endl;
      // Drop the number to the correct bucket
      bucket[digit].push_back(number);
    }//for
}// list to buckets

void bucket_to_list(vector<vector<int>> &bucket, vector<int> &array)
{
  vector<int> respuesta;
  for(int i=0; i<bucket.size(); i++)
    {
      for(int j=0; j<bucket[i].size(); j++)
	{
	  //cout << "\t\t BUCKET i: " << i << " j : " << j << " valor: " << bucket[i][j] << endl;
	  respuesta.push_back(bucket[i][j]);
	}//for 
    }//for

  copiar(respuesta, array);

  // limpiar el bucket
  bucket.clear();
  
}//bucket to list

void radix_sort(vector<int> &array, int base=10)
{
  //Encontrar el valor más grande
  vector<vector<int>> bucket;
  int maxval;
  maxval = array[0];
  for(int i=0; i<array.size(); i++){
    if(array[i] > maxval){
      maxval = array[i];
    }// if
  }// for

  int it = 0;
  while(pow(base, it) < maxval)
    {
      list_to_buckets(bucket, array, it);
      bucket_to_list(bucket, array);
      it+=1;
    }// while
}//radix sort

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
    case 3:
      heap_sort(respuesta);
      break;
    case 4:
      radix_sort(respuesta);
      break;
    }
  
  tiempo.stop();
  cout << "Duración en us: " ;
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

    // Enter
  cout << endl;
  
  // prueba del heap
  cout << "HEAP SORT" << endl;
  response = probar_algoritmo(array, 3);
  comparar(array, response);

  // Enter
  cout << endl;
  
  // prueba del radix
  cout << "RADIX SORT" << endl;
  response = probar_algoritmo(array, 4);
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
  
  // prueba del heap
  cout << "HEAP SORT" << endl;
  response = probar_algoritmo(array, 3);
  //comparar(array, response);

  // Enter
  cout << endl;
  
  // prueba del radix
  cout << "RADIX SORT" << endl;
  response = probar_algoritmo(array, 4);
  //comparar(array, response);
  
  // Enter
  cout << endl;
};
