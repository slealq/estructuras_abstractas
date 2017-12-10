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

ArrayXXf neural_network::sigmoid_prime(ArrayXXf z) {
  /* Basic multi-dimensional sigmoid prime function */
  return sigmoid(z)*(1-sigmoid(z));
  
} // sigmoid prime function

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

ArrayXXf neural_network::cost_derivative(ArrayXXf output_activations,
			 ArrayXXf y) {
  return output_activations - y;
  
} // cost derivative function

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
  ArrayXXf activation = x;
  vector<ArrayXXf> activations; // store all the activations
  vector<ArrayXXf> zs; // all z vectors

  // put the first activation layer
  activations.push_back(x);

  // get all activations and zs
  for(int i=1; i<num_layers; i++) {
    ArrayXXf z = ( (
		    weights[i].matrix() *
		    activation.matrix()
		    ).array()
			   + biases[i] );
    zs.push_back(z);
    activation = neural_network::sigmoid(z);
    activations.push_back(activation);
  } // for

  // backward pass
  ArrayXXf delta =
    neural_network::cost_derivative(activations.back(), y)
    * neural_network::sigmoid_prime(zs.back()); 

  cout << "ALL GOOD SO FAR 0" << endl;
  cout << "delta: " << delta << endl;
  
  nabla_b[nabla_b.size()-1] = delta;
  nabla_w[nabla_w.size()-1] = ( delta.matrix()
			       * activations[activations.size()-2].
			       matrix().transpose() ).array();
  cout << "ALL GOOD SO FAR 1" << endl;
    
  // for loop going backwards

  for(int i=2; i<num_layers; i++) {
    ArrayXXf z = zs[zs.size()-i];
    ArrayXXf sp = neural_network::sigmoid_prime(z);
    cout << "weights " << weights[weights.size()-i+1].
      matrix().
      transpose() << endl;
    cout << "delta " << delta.matrix() << endl;
    cout << "weights dot delta: "
      << (
	  weights[weights.size()-i+1].
	  matrix().
	  transpose()
	  * delta.matrix()
	  ).array()
      << endl;
    cout << "sp " << sp << endl; 
    delta = (weights[weights.size()-i+1].matrix().transpose()*delta.matrix()).array() * sp;
    cout << "ALL GOOD SO FAR 2" << endl;

    nabla_b[nabla_b.size()-i] = delta;
    nabla_w[nabla_b.size()-i] = (
				 delta.matrix() *
				 activations[activations.size()-i-1].
				 matrix().
				 transpose()
				 ).array(); 
    cout << "ALL GOOD SO FAR 3" << endl;    
  } // for
  
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

void neural_network::print_sigmoid_dbg(int layer,
				       ArrayXXf input) {
  cout << "Sigmoid function for input: "
       << neural_network::sigmoid(
				  (weights[layer].matrix()
				   * input.matrix()).array()
				  + biases[layer])
       << endl;
  
} // print sigmoid

void neural_network::print_sigmoid_prime_dbg(int layer,
					     ArrayXXf input) {
  cout << "Sigmoid prime function for input: "
       << neural_network::sigmoid_prime(
				  (weights[layer].matrix()
				   * input.matrix()).array()
				  + biases[layer])
       << endl;
} // print sigmoid prime

void neural_network::print_feedforward_dbg(ArrayXXf input) {
  cout << "FeedForward z: "
       << neural_network::feedforward(input)
       << endl;
} // print the feedforward result
