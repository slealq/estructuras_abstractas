#include "neural_network.h"
#include "mnist_loader.h"
#include <vector>
#include <iostream>
#include <Eigen/Dense>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/eigen.hpp>

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

  VideoCapture cap(1); // capture webcam 1

  Mat save_img;
  while(1) {
    cap >> save_img;

    if(save_img.empty())
      break;

    rectangle( save_img,
	       Point(640/2-16, 480/2-16),
	       Point(640/2+16, 480/2+16),
	       Scalar(0, 255, 255),
	       1,
	       8
	       );
    
    // display the resulting frame
    imshow( "Frame", save_img );

    // Press ESC on keyboard to exit
    char c = (char)waitKey(25);
    if(c==27)
      break;
        
  }
  
  if(save_img.empty())
    {
      std::cerr << "Something is wrong with the webcam, could not get frame." << std::endl;
    }
  // show image
  imshow("picture", save_img);
  waitKey(0);

  // realease capture object
  cap.release();

  // close all frames
  destroyAllWindows();
  
  // Save the frame into a file
  imwrite("webcam.jpg", save_img); // A JPG FILE IS BEING SAVED
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

    // close all frames
    destroyAllWindows();
    
    cv::imwrite("colored_number.png", crop);
}

ArrayXXf generate_input(string pic_name) {
  // convert to char *
  const char *cstr = pic_name.c_str();

  ArrayXXf input;
  
  cv::Mat img = cv::imread(cstr);
  if (img.empty())
    {
      std::cout << "!!! imread() failed to open target image" << std::endl;
      //return input;
    }

  cv::Mat greyMat;
  cv::cvtColor(img, greyMat, cv::COLOR_BGR2GRAY);

  float threshold=128.0;
  cout << "Enter the desired threshold: ";
  cin >> threshold;

  cout << greyMat << endl;
  
  Mat img_bw = greyMat > threshold; // threshold

  MatrixXf greyMatEi;
  cv2eigen(img_bw, greyMatEi);

  //covert greyMatEi to array

  // transpose
  cout << greyMatEi; 


  ArrayXXf output(784, 1);

  for(int i=0; i<28; i++){
    for(int j=0; j<28; j++) {
      if(greyMatEi(i,j) == 0) {
	output(i*28+j, 0) = 1.0;
      }
      else{
	output(i*28+j, 0) = 0.0;
      }
      //output(i*28+j, 0) = greyMatEi(i, j);
    }
  }
  
  //Eigen::Map<ArrayXXf> output(greyMatE.data(), 784, 1);

  // normalize
  //output = output / 255.0;

  // invert 1 and 0s
  
  return output;
  
} // generate input for feedforward

void pprint(ArrayXXf image) {
  for(int y=0; y<28; ++y) {
    for(int x=0; x<28; ++x) {
      cout << ( (image(y*28+x, 0) == 0.0)? ' ' : '*' );
    }
    cout << endl;
  }
  
} // pprint an arrayxxf image

int main(void) {
  float eta;
  int hidden_layer;
  int epochs;

  //save_image();
  //crop_image("webcam.jpg");
  //auto input = generate_input("colored_number.png");
  //cout << input << endl;
  //pprint(input);
  
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

  pprint(get<0>(trainning_data[0]));
  
  net.SGD(trainning_data, epochs, 10, eta, test_data);

  int loop = 1;

  while(loop == 1) {
    cout << "Make test? : (1 for yes, otherwise for no) " << endl;
    cin >> loop;
    if( loop != 1) {
      break;
    }

    save_image();
    crop_image("webcam.jpg");
    auto input = generate_input("colored_number.png");
    //cout << input << endl;
    pprint(input);

    cout << "Neural network result: " << endl;
    cout << net.feedforward(input) << endl;
    
  }
  
} // main
