#include "neural_network.h"
#include <Eigen/Dense>
#include <vector>
#include <iostream>
#include <tuple>

using namespace std;
using namespace Eigen;

neural_network::neural_network(vector<int> sizes) {
  num_layers = sizes.size();
  sizes_ = sizes;
  // random fill biases and weights
  biases.resize(num_layers);
  for(int i=1; i<num_layers; i++) {
    biases[i] = ArrayXXf::Random(sizes_[i], 1);
  } // for

  weights.resize(num_layers);
  for(int i=1; i<num_layers; i++) {
    weights[i] = ArrayXXf::Random(sizes_[i], sizes[i-1]);
  } // for
  
} // neural network constructor

// NETWORK FUNCTIONS ---------------------------------->

ArrayXXf neural_network::sigmoid(ArrayXXf z) {
  /* Basic multi-dimensional sigmoid function */
  return 1.0 / (1.0 + exp(-z));
  
} // sigmoid function

ArrayXXf neural_network::feedforward(ArrayXXf input) {
  /* This function is meant to get the output of
     the network given an input */
  ArrayXXf output = input;
  for(int i=1; i<num_layers; i++) {
    output = sigmoid(
		     (weights[i].matrix()
		      * output.matrix()).array()
		     + biases[i]);
  } // for
  return output;
} // feed forward

tuple< vector<ArrayXXf>, vector<ArrayXXf> >
neural_network::backprop(ArrayXXf x, ArrayXXf y) {
  /* Returns the bakpropagation result for a given tuple
   of input and output */

  vector<ArrayXXf> nabla_b(num_layers);
  vector<ArrayXXf> nabla_w(num_layers);

  // initialize as zero arrays with sizes like biases
  // and weights

  for(int i=1; i<num_layers; i++) {
    nabla_b[i] = ArrayXXf::Zero(biases[i].rows(),
				 biases[i].cols());

    nabla_w[i] = ArrayXXf::Zero(weights[i].rows(),
				weights[i].cols());
  } // for

  // feed forward part


  return make_tuple(nabla_b, nabla_w);
  
} // back propagation function

// DEBUGGER FUNCTIONS ---------------------------------->

void neural_network::print_biases_dbg(void) {
  for(int i=0; i<num_layers; i++) {
    cout << "Biases of the network; Layer: "
	 << i
	 << "\n"
	 << biases[i]
	 << endl;
  }
} // print biases

void neural_network::print_weights_dbg(void) {
  for(int i=0; i<num_layers; i++) {
    cout << "Weights of the network; Layer: "
	 << i
	 << "\n"
	 << weights[i]
	 << endl;
  }
} // print weights

void neural_network::print_sigmoid_dbg(ArrayXXf z) {
  cout << "Sigmoid function for input: "
       << neural_network::sigmoid(z)
       << endl;
  
} // print sigmoid

void neural_network::print_feedforward_dbg(ArrayXXf input) {
  cout << "FeedForward z: "
       << neural_network::feedforward(input)
       << endl;
} // print the feedforward result
