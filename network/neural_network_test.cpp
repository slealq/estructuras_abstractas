#include "neural_network.h"
#include "mnist_loader.h"
#include <vector>
#include <iostream>
#include <Eigen/Dense>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace Eigen;
using namespace cv;

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
      input(j, 0) = abs(image[j]);
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
      input(j, 0) = abs(image[j]);
    } // for j

    // output - 10th dimensional array
    int output = label;

    auto tuple = make_tuple(input, output);

    output_v.push_back(tuple);
    
  } // for i

  return output_v;
} // test data loader

void save_image(void) {

  VideoCapture cap(0);
  
  // Get the frame
  Mat save_img; cap >> save_img;
  
  if(save_img.empty())
    {
      std::cerr << "Something is wrong with the webcam, could not get frame." << std::endl;
    }
  // show image
  imshow("picture", save_img);
  waitKey(0);

  // Save the frame into a file
  imwrite("test.jpg", save_img); // A JPG FILE IS BEING SAVED
}

void crop_image(string string) {
  // convert to char *
  const char *cstr = string.c_str();
  
  cv::Mat img = cv::imread(cstr);
    if (img.empty())
    {
        std::cout << "!!! imread() failed to open target image" << std::endl;
        return;        
    }

    /* Set Region of Interest */

    int offset_x = 640/2-14;
    int offset_y = 480/2-14;

    cv::Rect roi;
    roi.x = offset_x;
    roi.y = offset_y;
    roi.width = 28;
    roi.height = 28;

    /* Crop the original image to the defined ROI */

    cv::Mat crop = img(roi);
    cv::imshow("crop", crop);
    cv::waitKey(0);

    cv::imwrite("noises_cropped.png", crop);

}

int main(void) {
  int eta;
  int hidden_layer;
  int epochs;

  save_image();
  crop_image("test.jpg");
  
  cout << "Choose network hidden layer n: ";
  cin >> hidden_layer;

  cout << "\nChoose how many epochs: ";
  cin >> epochs;
  
  cout << "\nChoose network learning rate: ";
  cin >> eta;
  
  cout << "\nBeginning learning process ..." << endl;
  
  vector<int> size {784, hidden_layer, 10};
  neural_network net(size);

  auto trainning_data = trainning_data_loader();
  auto test_data = test_data_loader();

  net.SGD(trainning_data, epochs, 10, eta, test_data);
  
} // main
