#include "neural_network.h"
#include <vector>
#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

void pprint(vector<ArrayXXf> vector) {
  for(int i=0; i<vector.size(); i++) {
    cout << vector[i] << endl;
  } // for
} // vector pprint

int main(void) {
  vector<int> sizes {2, 3, 1};
  neural_network netw(sizes);
  netw.print_biases_dbg();
  netw.print_weights_dbg();

  // test z vector
  ArrayXXf input = ArrayXXf::Random(2,1);
  cout << "Test vector: " << input << endl;

  // test feedforward function
  //cout << "FeedForward Z: " << netw.feedforward(z) << endl;
  netw.print_feedforward_dbg(input);

  // test sigmoid function
  netw.print_sigmoid_dbg(1, input);
  netw.print_sigmoid_prime_dbg(1, input);

  // test back propagation
  ArrayXXf output = ArrayXXf::Random(1,1);

  cout << "output array" << output << endl;
  
  auto tuple = netw.backprop(input, output);
  auto vect1 = get<0>(tuple);
  auto vect2 = get<1>(tuple);

  cout << "Nabla B: " << endl;
  pprint(vect1);
  cout << "Nabla W: " << endl;
  pprint(vect2);
  
  
} // main
