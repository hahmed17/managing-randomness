#ifndef NAIVEBAYESIAN_H_
#define NAIVEBAYESIAN_H_

#include <vector>

#include "bayesian.h"

namespace machinelearning {
namespace bayesian {

class NaiveBayesian : public Bayesian {
 public:
  NaiveBayesian(char*);
  // initialize all the information we need from training data
  void Train();
  std::vector<int> Predict(bool);
  // calculate the probability of each choice
  // and choose the greatest one as our prediction
 private:
  std::vector<std::vector<long double> > probabilityTable;
};

}  // namespace baysian
}  // namespace machinelearning
#endif
