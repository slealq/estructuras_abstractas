#include "neural_network.h"
#include "mnist_loader.h"
#include <vector>
#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

void pprint(vector<ArrayXXf> vector) {
  for(int i=0; i<vector.size(); i++) {
    cout << "Vector pos: " << i << endl;
    cout << vector[i] << endl;
  } // for
} // vector pprint

vector < tuple < ArrayXXf, ArrayXXf > > trainning_data_loader (void) {

  mnist_loader train("dataset/train-images-idx3-ubyte",
		     "dataset/train-labels-idx1-ubyte", 50000);

  vector< tuple < ArrayXXf, ArrayXXf > > output_v;

  int size = train.size();

  for(int i = 0; i < size; i++) {
    int label = train.labels(i);
    std::vector<double> image = train.images(i);
    
    // image - entry arrayxxf
    ArrayXXf input = ArrayXXf::Zero(784, 1);

    // save the image:
    for(int j=0; j<784; j++) {
      input(j, 0) = image[j];
    } // for j

    // output - 10th dimensional array
    ArrayXXf output = ArrayXXf::Zero(10, 1);

    // save the number in the label-th position
    output(label, 0) = 1.0;

    // create a tuple
    auto tuple = make_tuple(input, output);

    output_v.push_back(tuple);
    
  } // for i

  return output_v;
} // trainning data loader

vector < tuple < ArrayXXf, int > > test_data_loader (void) {

  mnist_loader test("dataset/t10k-images-idx3-ubyte",
                    "dataset/t10k-labels-idx1-ubyte", 10000);
  
  vector< tuple < ArrayXXf, int > > output_v;

  int size = test.size();

  for(int i = 0; i < size; i++) {
    int label = test.labels(i);
    std::vector<double> image = test.images(i);
    
    // image - entry arrayxxf
    ArrayXXf input = ArrayXXf::Zero(784, 1);

    // save the image:
    for(int j=0; j<784; j++) {
      input(j, 0) = image[j];
    } // for j

    // output - 10th dimensional array
    int output = label;

    auto tuple = make_tuple(input, output);

    output_v.push_back(tuple);
    
  } // for i

  return output_v;
} // test data loader

void test_mnist_loader(void) {

  mnist_loader train("dataset/train-images-idx3-ubyte",
                     "dataset/train-labels-idx1-ubyte", 100);
  mnist_loader test("dataset/t10k-images-idx3-ubyte",
                    "dataset/t10k-labels-idx1-ubyte", 100);
  
  int rows  = train.rows();
  int cols  = train.cols();
  int label = train.labels(1);
  std::vector<double> image = train.images(1);

  std::cout << "label: " << label << std::endl;
  std::cout << "image: " << std::endl;
  for (int y=0; y<rows; ++y) {
    for (int x=0; x<cols; ++x) {
      std::cout << ((image[y*cols+x] == 0.0)? ' ' : '*');
    }
    std::cout << std::endl;
  }
  
} // test mnist loader



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

  cout << "output array: " << output << endl;
  
  auto tuple = netw.backprop(input, output);
  auto vect1 = get<0>(tuple);
  auto vect2 = get<1>(tuple);

  cout << "\tNabla B: " << endl;
  pprint(vect1);
  cout << "\tNabla W: " << endl;
  pprint(vect2);

  auto test = float(vect1.size());

  //cout << test*3.99 << endl;

  //test_mnist_loader();

  //trainning_data_loader();

  vector<int> size {784, 100, 10};
  neural_network net(size);

  auto trainning_data = trainning_data_loader();
  auto test_data = test_data_loader();
  
  net.SGD(trainning_data, 30, 10, 3.0, test_data);
  
} // main
