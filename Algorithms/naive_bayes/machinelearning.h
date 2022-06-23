#ifndef ML_H_
#define ML_H_

#include <vector>
#include <fstream>
#include <iostream>
#include <ostream>


using namespace std;

namespace machinelearning {

class MachineLearning {
 public:
  virtual void Train() = 0;
  virtual std::vector<int> Predict(bool) = 0;
  void Accuracy(std::vector<int> &, std::vector<int> &) const;

  int num_train_instances_; // store the number of training instances
  int num_test_instances_;   // store the number of testing instances

 protected:
  virtual void ParseConfiguration(char*) = 0;

};

}  // namespace machinelearning
#endif
