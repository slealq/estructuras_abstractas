#include "neural_network.h"
#include <vector>
#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

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
  
} // main
