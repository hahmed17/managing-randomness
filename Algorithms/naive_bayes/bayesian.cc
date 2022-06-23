#include "bayesian.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

namespace machinelearning {
namespace bayesian {

void Bayesian::ParseConfiguration(char *cfg_file) {
  std::ifstream configure;
  configure.open(cfg_file);
  if (!configure) {
    std::cout << "Can't open configuration file!" << std::endl;
    return;
  }

  configure >> num_train_instances_ >> num_test_instances_ >> num_attributes_;
  // read the number of training instances and attributes

  num_train_instances_ = 0;
  num_test_instances_ = 0;
  // Get number of training instances
  ifstream trainingDataFile("train");
  //ifstream train_file("./breast_cancer_data/breast-cancer-wisconsin-400-records-train");
  for (string train_line; getline(trainingDataFile, train_line);) {
      num_train_instances_ += 1;
  }

  ifstream testDataFile("test");
  //ifstream test_file("./breast_cancer_data/breast-cancer-wisconsin-299-records-test");
  for (string test_line; getline(testDataFile, test_line);) {
      num_test_instances_ += 1;
  }

  cout << num_train_instances_ << endl;
  cout << num_test_instances_ << endl;

  is_discrete_.resize(num_attributes_);
  // this array store the information about each attribute is continuous or not
  for (int i = 0; i < num_attributes_; ++i) configure >> is_discrete_[i];
  //  read the information about continuous or not

  num_class_for_each_attribute_.resize(num_attributes_);
  // this array store the number of classes of each attribute

  for (int i = 0; i < num_attributes_; ++i) {  // read the number of classes
    configure >> num_class_for_each_attribute_[i];
  //  if (i != num_attributes_ &&  is_discrete_[i])  // set num_class_for_each_attribute_ as 2 for
  //                        // continuous data
  //    num_class_for_each_attribute_[i] = 2;
  }

  num_output_class_ = num_class_for_each_attribute_[num_attributes_-1];
  output_class_cnt_.resize(num_output_class_, 0);

  configure.close();
}

}  // namespace baysian
}  // namespace machinelearning
