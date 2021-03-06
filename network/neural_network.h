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
  vector<int> sizes_;
  vector<ArrayXXf> biases;
  vector<ArrayXXf> weights;
  ArrayXXf sigmoid(ArrayXXf z);
  ArrayXXf sigmoid_prime(ArrayXXf z);
  ArrayXXf cost_derivative(ArrayXXf output_activations,
			   ArrayXXf y);
  void update_mini_batches(vector<tuple<ArrayXXf,
			   ArrayXXf>> mini_batch,
			   float eta);
  int evaluate(vector<tuple<ArrayXXf, int>> test_data);
  
 public:
  neural_network(vector<int> sizes);
  ArrayXXf feedforward(ArrayXXf input);
  void print_biases_dbg(void);
  void print_weights_dbg(void);
  void print_sigmoid_dbg(int layer, ArrayXXf input);
  void print_sigmoid_prime_dbg(int layer, ArrayXXf input);
  void print_feedforward_dbg(ArrayXXf input);
  tuple< vector<ArrayXXf>, vector<ArrayXXf> >
    backprop(ArrayXXf &x, ArrayXXf &y);  // only public for testing
  void SGD(
	   vector< tuple< ArrayXXf, ArrayXXf > >
	   trainning_data,
	   int epochs,
	   int mini_batch_size,
	   int eta,
	   vector< tuple< ArrayXXf, int > >
	   test_data = {} );
  
}; // neural network class

#endif // NEURAL_NETWORK
