#include <Eigen/Dense>
#include <vector>
#include <tuple>

#ifndef NEURAL_NETWORK
#define NEURAL_NETWORK

using namespace Eigen;
using namespace std;

class neural_network {
 private:
  int num_layers;
  // sizes: list containing number of neurons
  // on respective layer
  // biases and weights should be randmonly
  // initialized, using Gaussian distribution, mean 0 and variance 1
  // first layer, the input layer, doesn't have biases.
  vector<int> sizes_;
  vector<ArrayXXf> biases;
  vector<ArrayXXf> weights;
  ArrayXXf sigmoid(ArrayXXf z);
  
 public:
  neural_network(vector<int> sizes);
  ArrayXXf feedforward(ArrayXXf input);
  tuple< vector<ArrayXXf>, vector<ArrayXXf> >
    backprop(ArrayXXf x, ArrayXXf y); 
  void print_biases_dbg(void);
  void print_weights_dbg(void);
  void print_sigmoid_dbg(ArrayXXf z);
  void print_feedforward_dbg(ArrayXXf input);
    
}; // neural network class

#endif // NEURAL_NETWORK
