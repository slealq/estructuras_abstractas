#include <vector>
#include <iostream>
#include <time.h>
#include "elapsed_time.h"

using namespace std;

vector<int> bubble_sort(vector<int>)
{
  vector<int> respuesta;
  E_time tiempo;
  tiempo.start();
  // aqui se implementa el bubble sort
  cout << "Bubble sort" << endl;
  tiempo.stop();
  cout << tiempo.elapsed() << endl;

  return respuesta;
}

int main(void)
{
  vector<int> array;
  bubble_sort(array);
};
