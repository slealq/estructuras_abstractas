#include "graphs.h"

void prueba(void){
  C_Graph<int> grafo = C_Graph<int>(10);
  cout << "Agregando en enlace 0->1" << endl;
  grafo.edge(0,1);
  grafo.edge(0,3);
  grafo.edge(0,7);
  grafo.edge(7,8);
  grafo.edge(8,9);
  grafo.edge(3,9);
  grafo.pprint();

  cout << endl;
  cout << "Probando el metodo dfs en 0" << endl;
  grafo.dfs(0);

  cout << endl;
  cout << "Probando el metodo BFS en 0" << endl;
  grafo.bfs(0);
  
  cout << endl;
  cout << "Probando el metodo dfs en 2" << endl;
  grafo.dfs(2);

  cout << endl;
  cout << "Probando el metodo BFS en 2" << endl;
  grafo.bfs(2);
  
  cout << endl;
  cout << "Probando el metodo dfs en 3" << endl;
  grafo.dfs(3);

  //cout << "Probando el metodo de enlace con peso en 0->4" << endl;
  //grafo.edge(0,4,10);

  grafo.pprint();

  cout << "Weightless distance : " << endl;
  grafo.weightless_distance(0);
  
  // PRUEBA DE WEIGHTED GRAPH
  grafo.edge(0, 1, 3);
  grafo.edge(0, 3, 5);
  grafo.edge(0, 7, 8);
  grafo.edge(7, 8, 1);
  grafo.edge(8, 9, 2);
  grafo.edge(3, 9, 3);
  grafo.edge(1, 3, 1);
  grafo.edge(0, 8, 4);
  grafo.pprint();

  cout << "Weighted distance: " << endl;
  grafo.weighted_distance(0);
    
  cout << endl;
}

int main(void){

  prueba();
  
};
