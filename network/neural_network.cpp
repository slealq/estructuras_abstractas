#include "neural_network.h"
#include <Eigen/Dense>
#include <vector>
#include <iostream>
#include <tuple>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace Eigen;

// HEPER FUNCTION ------------------------------------->
template<typename T>
std::vector<std::vector<T>> SplitVector(const std::vector<T>& vec, size_t n)
{
  std::vector<std::vector<T>> outVec;
  
  size_t length = vec.size() / n;
  size_t remain = vec.size() % n;
  
  size_t begin = 0;
  size_t end = 0;
  
  for (size_t i = 0; i < std::min(n, vec.size()); ++i)
    {
      end += (remain > 0) ? (length + !!(remain--)) : length;
      
      outVec.push_back(std::vector<T>(vec.begin() + begin, vec.begin() + end));
      
      begin = end;
    }

  return outVec;
}

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

int neural_network::evaluate(vector<tuple<ArrayXXf, int>> test_data) {
  /* Evaluates which number is the output, and returns 
     the sum of outputs x which are equal to the desired y */

  vector<tuple<int, int>> test_results; // the x, y ints are saved here.

  for(int i=0; i<test_data.size(); i++) {
    ArrayXXf act_output =
      neural_network::feedforward(get<0>(test_data[i]));

    //get location of maximum
    ArrayXXf::Index maxRow, maxCol;
    float max = act_output.maxCoeff(&maxRow, &maxCol);

    //new tuple - maxRow is the number whose score is the highest.
    tuple<int, int> pair = make_tuple( maxRow,
				       get<1>(test_data[i]) );

    //append test results
    test_results.push_back(pair);
  } // for

  // sum the ones that are equal
  int assertions = 0;

  for(int i=0; i<test_results.size(); i++) {
    if(get<0>(test_results[i]) == get<1>(test_results[i])) {
      assertions += 1;
    }
  } // for
  
  return assertions;

} // test data

tuple< vector<ArrayXXf>, vector<ArrayXXf> >
neural_network::backprop(ArrayXXf &x, ArrayXXf &y) {
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

  //  cout << "BIG PRINT X in backprop" << x << endl;

  
  vector<ArrayXXf> activations; // store all the activations
  vector<ArrayXXf> zs; // all z vectors

  // put the first activation layer
  activations.push_back(x);

  //cout << "Backprop 0" << endl;

  // define z vector
  ArrayXXf z;
  // get all activations and zs
  for(int i=1; i<num_layers; i++) {
    //    cout << "BIG PRINT WEIGHTS[I] in backprop" << weights[i] << endl;
    z = ( (
		    weights[i].matrix() *
		    activation.matrix()
		    ).array()
			   + biases[i] );
    //cout << "Backprop 1" << endl;
 
    
    zs.push_back(z);
    activation = neural_network::sigmoid(z);
    activations.push_back(activation);
  } // for

  // backward pass
  ArrayXXf delta =
    neural_network::cost_derivative(activations.back(), y)
    * neural_network::sigmoid_prime(zs.back()); 

  nabla_b[nabla_b.size()-1] = delta;
  nabla_w[nabla_w.size()-1] = ( delta.matrix()
			       * activations[activations.size()-2].
			       matrix().transpose() ).array();
    
  // for loop going backwards
  
  // define sp
  ArrayXXf sp;
  
  for(int i=2; i<num_layers; i++) {
    z = zs[zs.size()-i];
    sp = neural_network::sigmoid_prime(z);
    delta = (
	     weights[weights.size()-i+1].matrix().transpose()
	     *delta.matrix()).array() * sp;
    nabla_b[nabla_b.size()-i] = delta;
    nabla_w[nabla_b.size()-i] = (
				 delta.matrix() *
				 activations[activations.size()-i-1].
				 matrix().
				 transpose()
				 ).array(); 
  } // for

  return make_tuple(nabla_b, nabla_w);
  
} // back propagation function

void neural_network::update_mini_batches(vector<tuple<ArrayXXf,
					 ArrayXXf>> mini_batch,
					 float eta) {
  /* Takes the mini batches and updates biases and weights */

  vector<ArrayXXf> nabla_b(num_layers);
  vector<ArrayXXf> nabla_w(num_layers);

  // initialize as zero arrays with sizes like biases
  // and weights
  
  //cout << "UPDMINI 0" << endl;

  for(int i=1; i<num_layers; i++) {
    nabla_b[i] = ArrayXXf::Zero(biases[i].rows(),
				 biases[i].cols());

    nabla_w[i] = ArrayXXf::Zero(weights[i].rows(),
				weights[i].cols());
  } // for

  // for each tuple in the mini batch

  for(int i=0; i<mini_batch.size(); i++) {
    auto x = get<0>(mini_batch[i]);
    auto y = get<1>(mini_batch[i]);

    //cout << "UPDMINI 2" << endl;
    auto deltas = neural_network::backprop(x, y);
    //cout << "UPDMINI 3" << endl;
    auto delta_nabla_b = get<0>(deltas);
    auto delta_nabla_w = get<1>(deltas);

    //cout << "UPDMINI 2" << endl;
    
    // reconstruct nabla_b
    for(int j=0; j<delta_nabla_b.size(); j++) {
      nabla_b[j] = nabla_b[j] + delta_nabla_b[j];
    } // for

    // reconstruct nabla_w
    for(int j=0; j<delta_nabla_w.size(); j++) {
      nabla_w[j] = nabla_w[j] + delta_nabla_w[j];
    } // for

    //cout << "UPDMINI 1" << endl;
	
    
  } // for

  // update weights and biases
  for(int i=0; i<weights.size(); i++) {
    auto w = weights[i];
    auto nw = nabla_w[i];
    auto mini_len = float(mini_batch.size());
    weights[i] = w - (eta/mini_len)*nw;
  } // for weights

  // biases
  for(int i=0; i<biases.size(); i++) {
    auto b = biases[i];
    auto nb = nabla_b[i];
    auto mini_len = float(mini_batch.size());
    biases[i] = b - (eta/mini_len)*nb;
  } // for biases

} // update mini batches function

void pprint(vector<tuple<ArrayXXf, ArrayXXf>> &trainning_data) {
  ArrayXXf x;
  ArrayXXf y;

  cout << "trainning data size" << trainning_data.size() << endl;
  
  x = get<0>(trainning_data[0]);
  y = get<1>(trainning_data[0]);
  
  cout << "X: " << endl;
  cout << x << endl;
  
  cout << "Y: " << endl;
  cout << y << endl;
 
} // pprint

void neural_network::SGD(
	   vector< tuple< ArrayXXf, ArrayXXf > >
	   trainning_data,
	   int epochs,
	   int mini_batch_size,
	   int eta,
	   vector< tuple< ArrayXXf, int > >
	   test_data ) {
  // debug trainning data
  //pprint(trainning_data);

  srand( unsigned (time(0) ) );
  int n_test = 0;
  if( !test_data.empty() ) {
    n_test = test_data.size();
  } // if

  int n = trainning_data.size();

  for(int j=0; j<epochs; j++) {
    // shuffle the trainning data
    random_shuffle(trainning_data.begin(),
		   trainning_data.end()
		   );

    //    cout << "DBUG 0" << endl;
    
    // split the mini batches
    auto mini_batches = SplitVector(trainning_data, mini_batch_size);

    //    cout << "DBUG 1" << endl;
    
    // iterate for each mini batch
    for(int i=0; i<mini_batches.size(); i++) {
      neural_network::update_mini_batches(mini_batches[i], eta);
    } // for

    //    cout << "DBUG 2" << endl;

    if(n_test != 0) {
      cout << " Epoch: "
	   << j
	   << " "
	   << neural_network::evaluate(test_data)
	   << " / "
	   << n_test
	   << endl;
    } // if ntest
    else{
      cout << "Epoch: " << j << " completed" << endl;
    }
  } // for
  
  
} // Gradient descent function for learning

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
