#include<vector>
//#include<queue>
#include<iostream>
#include<utility>
#include<functional>
#include<bits/stdc++.h>

using namespace std;

#ifndef CLASEGRAFO
#define CLASEGRAFO

template <typename T>
class C_Graph{
 protected:
  vector<vector<int>> adyacencia;
  vector<int> lista_dfs;
  int size = 0;
  
 public:
  C_Graph(int vertice);
  virtual ~C_Graph(void);
  virtual void edge(int vertice1, int vertice2);
  virtual void edge(int vertice1, int vertice2, int peso);
  virtual void pprint(void);
  virtual void pprint(vector<vector<int>>);
  virtual void dfs(int node);
  virtual void dfs_re(int node);
  virtual void bfs(int node);
  virtual vector<vector<int>> weightless_distance(int node);
  virtual vector<vector<int>>  weighted_distance(int node);
  
};//class


// IMPLEMENTACION ++

template <typename T>
C_Graph<T>::C_Graph(int vertices)
{
  size = vertices;
  adyacencia.resize(vertices);
  for(int i=0; i<vertices; i++){
    adyacencia[i].resize(vertices);
  }//for
}//Constructor de graph

template <typename T>
C_Graph<T>::~C_Graph(void){
  cout << "FIN" << endl;
}//desctructor de graph

template <typename T>
void C_Graph<T>::edge(int vertice1, int vertice2)
{
  adyacencia[vertice1][vertice2] = 1;
}

template <typename T>
void C_Graph<T>::edge(int vertice1, int vertice2, int peso)
{
  adyacencia[vertice1][vertice2] = peso;
}

template <typename T>
void C_Graph<T>::pprint(void){
  pprint(adyacencia);
}

template <typename T>
void C_Graph<T>::pprint(vector<vector<int>> adyacencia){
  cout << "Matrix: " << endl;
  for(int i=0; i<adyacencia.size(); i++){
    for(int j=0; j<adyacencia[i].size(); j++){
      cout << " " << adyacencia[i][j];
    }//for j
    cout << endl;
  }
}

template <typename T>
void C_Graph<T>::dfs(int node)
{
  // Realizar un resize de la lista
  lista_dfs.resize(size);

  // Limpiarla
  for(int i =0; i<size; i++)
    {
      lista_dfs[i] = 0;
    }

  // Ahora, de la matriz de donde estoy 
  // hacer la recusion de esta pos.

  // Agregar el nodo en el que estoy
  lista_dfs[node] = 1;

  
  dfs_re(node);
  
  // Los nodos adyacentes son:
  cout << "Nodos unidos: ";
  
  // recorrer la lista para saber cuales imprimir
  for(int i=0; i<size; i++)
    {
      if(lista_dfs[i] == 1)
	{
	  cout << i << " ";
	}//if
    }//for
  // Imprimir un espacio
  cout << endl;
}//dfs

template <typename T>
void C_Graph<T>::dfs_re(int node)
{
  // del nodo donde estoy, revisar
  // cada
  for(int i=0; i<size; i++)
    {
      if(adyacencia[node][i]==1){
	// Si esta enlazada al nodo 1
	lista_dfs[i] = 1;
	dfs_re(i);
      }//if
    }//for
}

template <typename T>
void C_Graph<T>::bfs(int node)
{
  queue<int> cola;
  cola.push(node);

  int nodo;
  
  while(cola.empty() == false){
    nodo = cola.front();
    cola.pop();
    cout << nodo ;
    cout << " ";
    for(int i=0; i<size; i++)
      {
	if(adyacencia[nodo][i]==1)
	  {
	    cola.push(i);
	  }
      }//for
  }//while
  cout << endl;
}

template <typename T>
vector<vector<int>> C_Graph<T>::weightless_distance(int node)
{
  vector<vector<int>> respuesta;
  // Redimensionar para tener tres columnas 
  respuesta.resize(size);
  for(int i=0; i<size; i++)
    {
      respuesta[i].resize(2);
      respuesta[i][0] = -1;
    }

  // Limpiar el inicial
  respuesta[node][0] = 0;

  // Ya a este punto tengo la matriz
  pprint(respuesta);

  // defino una nueva cola
  queue<int> cola;
  cola.push(node);

  int nodo;

  while(cola.empty() == false){
    nodo = cola.front();
    cola.pop();
    for(int i = 0; i<size; i++){
      if(adyacencia[nodo][i] != 0){
	// adjacent to v
	if(respuesta[i][0] == -1){
	  respuesta[i][0] = respuesta[nodo][0] + 1;
	  respuesta[i][1] = nodo;
	  cola.push(i);
	}
      }
    }
    
  }
  
  // volver a imprimir el resultado
  pprint(respuesta);

  
  return respuesta;
}

template <typename T>
vector<vector<int>> C_Graph<T>::weighted_distance(int node)
{
  vector<vector<int>> respuesta;
  // Redimensionar para tener tres columnas
  respuesta.resize(size);
  for(int i=0; i<size; i++)
    {
      respuesta[i].resize(2);
      respuesta[i][0] = -1;
    }

  // Limpiar el inicial
  respuesta[node][0] = 0;

  // A este punto tengo la matriz
  pprint(respuesta);
  
  // defino la cola
  priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> cola;

  // Definir el primer elemento
  pair<int, int> p;
  p = make_pair(node, 0);

  cola.push(p);

  // Variables de ayuda
  pair<int, int> pair;
  int nodo;
  int peso;
  int distancia;
  
  while(cola.empty() == false)
    {
      pair = cola.top();
      nodo = pair.first;
      cola.pop();
      for(int i=0; i<size; i++)
	{
	  // OJO: v = nodo
	  // n = i
	  // respuesta[x][0] = distancia[x]
	  // respuesta[x][1] = path
	  
	  if(adyacencia[nodo][i] !=0 )
	    {
	      distancia = respuesta[nodo][0] + adyacencia[nodo][i];
	      if(respuesta[i][0] == -1)
		{
		  respuesta[i][0] = distancia;
		  pair = make_pair(i, respuesta[i][0]);
		  cola.push(pair);
		  respuesta[i][1] = nodo;
		}//if
	      if(respuesta[i][0] > distancia)
		{
		  respuesta[i][0] = distancia;
		  pair = make_pair(i, respuesta[i][0]);
		  cola.push(pair);
		  respuesta[i][1] = nodo;
		}//if
	    }//if
	}//for
    }//while

  // volver a imrpimir el resultado
  pprint(respuesta);
    
  return respuesta;
}

#endif


