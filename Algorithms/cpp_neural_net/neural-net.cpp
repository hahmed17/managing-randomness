/*
This code presents an implementation of a neural network (multilayer perceptron) whose training is based on an error backpropagation algorithm.
The neural network itself is described using the Neural class. Its application is presented on the example of data on the results of diagnostics of heart disease.
The data was taken from the Kaggle machine learning forum. Link - https://www.kaggle.com/johnsmith88/heart-disease-dataset.
The neural network is able to predict heart disease with an accuracy of 84% (seen from the console output). This is far from the limit for this dataset,
however, such accuracy indicates that the neural network is indeed trained and capable of being used as intended.
*/
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>      
#include <fstream>
// #include <cstdlib>
#include <string>
//#include <strstream>
#include <stdio.h>
// #include <stdlib.h>
#include <Windows.h>
#include <direct.h>
#include "srand-rand-function.h"
#include <ostream>
#include <algorithm>

using namespace std;

class Neural {		// We begin to describe the class 
public:
	int outlayer = 1;	// The dimension of the output layer. We set the value to 1, since this example solves the problem of binary classification.
	int secondlayer = 13;	// The sizes of hidden layers can be set differently. The accuracy of the model partly depends on them, but they do not play a decisive role.
	int firstlayer = 13;	// firstlayer ? secondlayer - sizes of hidden hides
	int zerolayer = 13;		// zerolayer - the size of the entrance entrance. This value is not random, it is predetermined by the number of input parameters
	double learnrate = 2.05;	// During training, as mentioned above, the backpropagation algorithm is used.
								// The learnrate parameter determines at what local minimum the change in the bond weight will stall.
								// this parameter can also be changed, the accuracy of the presented neural network directly depends on it. 
	vector<double> input_layer;			//	Each layer will be represented as a one-dimensional vector
	vector<vector<double>> weights_0_1;	//	And the weights of the connections between the layers are in the form of a two-dimensional vector. 
	vector<double> first_layer;			//	To simplify the representation of the weight of connections - a table where two neurons correspond to one connection weight between them
	vector<double> miss_first;			//	We declare all the necessary layers and link weights
	vector<vector<double>> weights_1_2;	//	Also, I draw your attention to the fact that each layer corresponds to a vector that stores the errors of each neuron in the layer.
	vector<double> second_layer;		//	This measure makes it possible to implement the backpropagation algorithm
	vector<double> miss_second;			//	All vectors with the beginning "miss" in the name are what we are talking about.
	vector<vector<double>> miss_2_out;	//				
	vector<vector<double>> weights_2_out;// 
	vector<double> out_layer;
	vector<double> miss_out;
	Neural() {		// Let's describe the constructor of the Neural class
		input_layer.resize(zerolayer);	//	We set all layers, connection weights and vectors storing neuron errors with the appropriate sizes
		first_layer.resize(firstlayer);
		miss_first.resize(firstlayer);
		second_layer.resize(secondlayer);
		miss_second.resize(secondlayer);
		out_layer.resize(outlayer);
		miss_out.resize(outlayer);

		weights_0_1.resize(firstlayer, vector <double>(zerolayer));
		weights_1_2.resize(secondlayer, vector <double>(firstlayer));
		weights_2_out.resize(outlayer, vector <double>(secondlayer));
		// Before starting training the neural network, it is necessary to set the starting values ??of the connection weights
		// They can be random, preferably in the range from -1 to 1
		for (int i = 0; i < weights_0_1.size(); i++) {
			for (int j = 0; j < weights_0_1[0].size(); j++) {
				weights_0_1[i][j] = (1 + rand() % 200) / 100. - 1;
			}
		}
		for (int i = 0; i < weights_1_2.size(); i++) {
			for (int j = 0; j < weights_1_2[0].size(); j++) {
				weights_1_2[i][j] = (1 + rand() % 200) / 100. - 1;
			}
		}
		for (int i = 0; i < weights_2_out.size(); i++) {
			for (int j = 0; j < weights_2_out[0].size(); j++) {
				weights_2_out[i][j] = (1 + rand() % 200) / 100. - 1;
			}
		}
	}		// This completes the initialization of the neural network, proceed to the description of the auxiliary functions
	vector<double> matrix_vector(vector<vector<double>> matrix, vector<double> Vector) {
		vector <double> answer(matrix.size());	// Matrix-vector multiplication is a basic function when working with perceptrons
		double sum = 0;							// The algorithm is obvious
		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[0].size(); j++) {
				sum = sum + matrix[i][j] * Vector[j];
			}
			answer[i] = sum;
			sum = 0;
		}
		return answer;
	}
	vector <double> activation(vector<double> Vector) {	// Let's define the function of neuron activation, it is necessary in order to 
		for (int i = 0; i < Vector.size(); i++) {		// to limit the possible values ??of neurons in the range from 0 to 1 
			Vector[i] = 1 / (1 + exp(-Vector[i]));		// The sigmoid function is used as an example
		}
		return Vector;
	}
	vector<double> predict(vector<double> input) {		// The heart of the neural network is the forecasting algorithm
		input_layer = input;							// In essence, all the work of a neural network is the sequential multiplication of the connection weights by the value of each neuron
		input_layer = activation(input_layer);			// The algorithm starts by activating the input layer
		first_layer = matrix_vector(weights_0_1, input_layer);	// The values ??of the first layer are determined by multiplying the link weights by the values ??of the input layer
		first_layer = activation(first_layer);					// After multiplication, you need to activate 
		second_layer = matrix_vector(weights_1_2, first_layer);	// Then this algorithm is repeated up to the output layer
		second_layer = activation(second_layer);
		out_layer = matrix_vector(weights_2_out, second_layer);
		out_layer = activation(out_layer);
		return out_layer;
	}
	void learn_back_prop(double miss) {				// The function that makes our neural network alive			
		miss_out[0] = miss * out_layer[0] * (1 - out_layer[0]);	// In the next loops, the backpropagation algorithm is implemented.
		for (int j = 0; j < secondlayer; j++) {					// it is difficult to see the formula from these records, so I will briefly describe what is happening
			miss_second[j] = miss_out[0] * second_layer[j] * (1 - second_layer[j]) * weights_2_out[0][j];
		}														// 1) First, the errors of each layer are calculated
		for (int i = 0; i < firstlayer; i++) {
			miss_first[i] = 0;
			for (int j = 0; j < secondlayer; j++) {
				miss_first[i] = miss_first[i] + miss_second[j] * weights_1_2[j][i] * first_layer[i] * (1 - first_layer[i]);
			}
		}
		for (int i = 0; i < outlayer; i++) {
			for (int j = 0; j < secondlayer; j++) {
				weights_2_out[i][j] = weights_2_out[i][j] + miss_out[i] * second_layer[j] * learnrate;
			}
		}														// 2) Then, based on the calculated errors, the values ??of the link weights are changed
		for (int i = 0; i < secondlayer; i++) {
			for (int j = 0; j < firstlayer; j++) {
				weights_1_2[i][j] = weights_1_2[i][j] + miss_second[i] * first_layer[j] * learnrate;
			}
		}
		for (int i = 0; i < firstlayer; i++) {
			for (int j = 0; j < zerolayer; j++) {
				weights_0_1[i][j] = weights_0_1[i][j] + miss_first[i] * input_layer[j] * learnrate;
			}
		}
	}
};

template< class RandomIt >
void random_shuffle2(RandomIt trainVect, size_t start, size_t end) {
	if (start == end) {
		return;
	}
	for (int i = end - 1; i > start; --i) {
		trainVect[i].swap(trainVect[start + rand() % (i + 1)]);
	}
}


/*
Function that write the elements of a two-dimensional vector, data, to a text file, filename
*/
void write2DVector(string filename, vector<vector<double>> data) {
	ofstream general_method(filename);
	ostream_iterator<double> output_iterator(general_method, "\n");
	for (size_t i = 0; i < data.size(); ++i) {
		copy(data.at(i).begin(), data.at(i).end(), output_iterator);
		general_method << '\n';
	}
}


/*
* Checks if a line is comma delimited
*/
bool isCommaDelimited(string line) {
	return find(line.begin(), line.end(), ',') != line.end();
}


/*
* Checks if a line is space delimited
*/
bool isSpaceDelimited(string line) {
	return find(line.begin(), line.end(), ' ') != line.end();
}

/*
* Checks if a line is tab delimited
*/
bool isTabDelimited(string line) {
	return find(line.begin(), line.end(), '/t') != line.end();
}

/*
Proceses a data set from .csv
*/
vector <vector <double> > LoadData(char* data_filename) {
	ifstream datafile(data_filename);  // change to ../../data/fileName.csv if generating samples in subdirectory
	ifstream datafile_2(data_filename);
	if (!datafile.is_open()) std::cout << "ERROR: File Open" << '\n';
	vector <vector <double>> data;

	// Get number of columns in data set
	string line;
	getline(datafile, line);

	// Check file delimiter
	char delimiter = ' ';
	if (isCommaDelimited(line)) {
		delimiter = ',';
	}
	else if (isSpaceDelimited(line)) {
		delimiter = ' ';
	}
	else if (isTabDelimited(line)) {
		delimiter = '\t';
	}
	else {
		cout << "Unrecognized delimiter" << endl;
	}

	// save entries of first row to vector
	string entry;
	stringstream ss(line);

	vector<string> first_row_vec;
	while (getline(ss, entry, delimiter)) {
		first_row_vec.emplace_back(entry);
	}

	string row;
	size_t num_columns = first_row_vec.size();
	size_t rows_size = 0;
	// push each row of data set to data vector
	while (getline(datafile_2, row)) {
		data.resize(rows_size, vector<double>(num_columns));

		// get line and store entries in vector
		vector<double> row_vec;
		string row_entry;
		istringstream iss(row);

		while (getline(iss, row_entry, delimiter)) {
			if (row_entry == "?" || row_entry == "") {  // if missing value, replace with NULL
				row_vec.push_back(NULL);
			}
			else {
				row_vec.push_back(stod(row_entry));
			}
		}

		data.push_back(row_vec);
		++rows_size;
	}

	//fstream datafile_2(data_filename);  // read data again to replace first row

	// Get each column from the data set
	//size_t rows_size = 0;
	//vector<string> columns(num_columns);
	//while (datafile_2.good()) {
	//	rows_size++;
	//	data.resize(rows_size, vector <double>(num_columns));
	//	for (size_t i = 0; i < num_columns - 1; ++i) {
	//		getline(datafile_2, columns[i], delimiter);
	//	}
	//	getline(datafile_2, columns[num_columns - 1], '\n');  // \n because there is no column after
	//	data[rows_size - 1][num_columns - 1] = atof(columns[num_columns - 1].c_str());
	//}
	// write2DVector("general_method_data.txt", data);  // write data vector to file

	return data;
}


/*
* Function to train and test neural network on a loop
*/
void RunNeuralNet(char* data_filename, double training_ratio, double test_ratio) {
	Neural neural = Neural();	// Let's declare a class object and specify a constructor for it

	ofstream outputFile("out.txt");

	vector <vector <double>> data = LoadData(data_filename);	// Load data from csv file into vector
	//vector <vector <double>> data = LoadWineData();	// Load data from csv file into vector
	// Let's separate the analyzes from the diagnosis:
	vector <vector <double>> X;
	X.resize(data.size(), vector<double>(data[0].size() - 1));
	vector <vector <double>> y;
	y.resize(data.size(), vector<double>(1));

	// In this cycle, we will divide the input data into signs X and expectations y
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[0].size() - 1; j++) {
			X[i][j] = data[i][j];
		}
		y[i][0] = data[i][data[0].size() - 1];
	}
	// Divide X and y into training and test data:
	vector <vector <double>> X_train;
	X_train.resize(X.size(), vector<double>(X[0].size()));
	vector <vector <double>> X_test;
	X_test.resize(X.size(), vector<double>(X[0].size()));

	vector <vector <double>> y_train;
	vector <vector <double>> y_test;
	y_train.resize(y.size(), vector<double>(y[0].size()));
	y_test.resize(X.size(), vector<double>(y[0].size()));

	int rand_train_split = RAND_MAX * training_ratio;
	int rand_test_split = RAND_MAX * test_ratio;

	// Initialize sizes for X and y training and testing sets
	int X_train_size = 0;
	int X_test_size = 0;

	int y_train_size = 0;
	int y_test_size = 0;

	int X_validation_size = 0;
	int y_validation_size = 0;

	// generate train and test sets
	for (size_t i = 0; i < data.size(); ++i) {
		int rand_num = rand();
		if (rand_num < rand_train_split) {
			X_train[i] = X[i];
			y_train[i] = y[i];

			++X_train_size;
			++y_train_size;
		}
		else {
			int k = i - X.size() * training_ratio;
			X_test[i] = X[i];
			y_test[i] = y[i];

			// increment test set size
			++X_test_size;
			++y_test_size;
		}
	}

	// Resize x and y training and testing sets to current capacities
	X_train.resize(X_train_size, vector<double>(X[0].size()));
	X_test.resize(X_test_size, vector<double>(X[0].size()));

	y_train.resize(y_train_size, vector<double>(y[0].size()));
	y_test.resize(y_test_size, vector<double>(y[0].size()));

	vector <double> target;		// We declare auxiliary vectors
	target.resize(neural.outlayer);
	vector<double> person;
	person.resize(neural.zerolayer);
	vector <double> predict = neural.predict(person);
	double miss = 0;			// miss - the value of the miss is how much the neural network forecast differs from our expectations
	double count = 0;			// count - the number of times the model guessed the diagnosis 
	for (int i = 0; i < X_test.size(); i++) {
		person = X_test[i];
		target = y_test[i];
		predict = neural.predict(person);
		if (int(predict[0] + 0.5) == target[0]) {
			count++;
		}
	}
	double accuracy = count / X_test.size();	// Let's calculate the accuracy by dividing count by the number of patients examined in the cycle
	count = 0;
	outputFile << "Accuracy before learning: " << accuracy << endl;
	// Now let's train the neural network on the training data.
	for (int i = 0; i < X_train.size(); i++) {
		person = X_train[i];
		target = y_train[i];
		predict = neural.predict(person);	// we get a prediction
		miss = target[0] - predict[0];		// calculate the miss
		neural.learn_back_prop(miss);		// run the algorithm for backpropagation of the error from the obtained value of the miss
	}	// This completes the training of the network, then we test the calculated values ??of the link weights
	for (int i = 0; i < X_test.size(); i++) {
		person = X_test[i];
		target = y_test[i];
		predict = neural.predict(person);	// Now we will validate the network - we will calculate the accuracy on a previously unknown data network
		miss = target[0] - predict[0];
		if (int(predict[0] + 0.5) == target[0]) {
			count++;
		}
	}
	accuracy = count / X_test.size();		// Calculating the final precision
	outputFile << "Final accuracy:           " << accuracy << endl;
	outputFile << "Test predictions: ";
	// outputFile << neural.predict(X[55])[0] << " - " << y[55][0] << endl;
	// outputFile << neural.predict(X[601])[0] << " - " << y[601][0] << endl;
}

void RunNeuralNetControlledData(char* data_filename, double training_ratio, double test_ratio) {
	Neural neural = Neural();

	ofstream outputFile("out.txt");

	vector <vector <double>> data = LoadData(data_filename);
	vector <vector <double>> X;
	X.resize(data.size(), vector<double>(data[0].size() - 1));
	vector <vector <double>> y;
	y.resize(data.size(), vector<double>(1));


	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[0].size() - 1; j++) {
			X[i][j] = data[i][j];
		}
		y[i][0] = data[i][data[0].size() - 1];
	}

	vector <vector <double>> X_train;
	X_train.resize(int(X.size() * training_ratio), vector<double>(X[0].size()));
	vector <vector <double>> X_test; training_ratio;
	X_test.resize(X.size() - int(X.size() * training_ratio), vector<double>(X[0].size()));

	vector <vector <double>> y_train;
	y_train.resize(int(y.size() * training_ratio), vector<double>(y[0].size()));
	vector <vector <double>> y_test;
	y_test.resize(y.size() - int(y.size() * training_ratio), vector<double>(y[0].size()));

	int k = 0;	// ? ????? ??? ?? ???????? ?????? ?? ???????? ? ?????????????
	for (int i = 0; i < data.size(); i++) {	// ??? ????? ??? ????, ????? ??????????? ??????? ???????? ????????? ????
		if (i < int(X.size() * training_ratio)) {		// ????????????? ???? ????? ?? ??? ??????, ??????? ?? ?? ??????????? ??? ????????
			X_train[i] = X[i];
			y_train[i] = y[i];
		}
		else {
			k = i - X.size() * training_ratio;
			X_test[k] = X[k];
			y_test[k] = y[k];
		}
	}
	vector <double> target;		// ??????? ??????????????? ???????
	target.resize(neural.outlayer);
	vector<double> person;
	person.resize(neural.zerolayer);
	vector <double> predict = neural.predict(person);
	double miss = 0;			// miss - ???????? ???????, ??? ?? ?? ??????? ??????? ????????? ?????????? ?? ????? ????????
	double count = 0;			// count - ?????????? ???, ????? ?????? ??????? ??????? 
	for (int i = 0; i < X_test.size(); i++) {
		person = X_test[i];
		target = y_test[i];
		predict = neural.predict(person);
		if (int(predict[0] + 0.5) == target[0]) {
			count++;
		}
	}
	double accuracy = count / X_test.size();	// ????????? ????????, ??????? count ?? ?????????? ????????????? ? ????? ?????????
	count = 0;
	outputFile << "Accuracy before learning: " << accuracy << endl;
	// ?????? ?????? ????????? ?? ????????????? ??????
	for (int i = 0; i < X_train.size(); i++) {
		person = X_train[i];
		target = y_train[i];
		predict = neural.predict(person);	// ???????? ????????????
		miss = target[0] - predict[0];		// ????????? ??????
		neural.learn_back_prop(miss);		// ????????? ???????? ????????? ??????????????? ?????? ?? ??????????? ???????? ???????
	}	// ?? ???? ???????? ???? ?????????, ????? ???????????? ??????????? ???????? ????? ??????
	for (int i = 0; i < X_test.size(); i++) {
		person = X_test[i];
		target = y_test[i];
		predict = neural.predict(person);	// ?????? ?????????? ????????? ???? - ????????? ???????? ?? ????? ??????????? ???? ??????
		miss = target[0] - predict[0];
		if (int(predict[0] + 0.5) == target[0]) {
			count++;
		}
	}
	accuracy = count / X_test.size();		// ????????? ???????? ????????
	outputFile << "Final accuracy:           " << accuracy << endl;
	// outputFile << "Test predictions: ";
	//cout << neural.predict(X[55])[0] << " - " << y[55][0] << endl;
	//cout << neural.predict(X[601])[0] << " - " << y[601][0] << endl;
}

void RunNeuralNetControlledTrainOrTest(char* data_filename, ofstream& outputFile, int training_ratio, string randTrainOrTest) {
	Neural neural = Neural();	// Let's declare a class object and specify a constructor for it

	vector <vector <double>> data = LoadData(data_filename);	// Load data from csv file into vector
	// Let's separate the analyzes from the diagnosis:
	vector <vector <double>> X;
	X.resize(data.size(), vector<double>(data[0].size() - 1));
	vector <vector <double>> y;
	y.resize(data.size(), vector<double>(1));

	// In this cycle, we will divide the input data into signs X and expectations y
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[0].size() - 1; j++) {
			X[i][j] = data[i][j];
		}
		y[i][0] = data[i][data[0].size() - 1];
	}
	// Divide X and y into training and test data:
	vector <vector <double>> X_train;
	X_train.resize(X.size(), vector<double>(X[0].size()));
	//X_train.resize(int(X.size() * training_ratio), vector<double>(X[0].size()));
	vector <vector <double>> X_test;
	X_test.resize(X.size(), vector<double>(X[0].size()));
	//X_test.resize(X.size() - int(X.size() * training_ratio), vector<double>(X[0].size()));

	vector <vector <double>> y_train;
	//y_train.resize(int(y.size() * training_ratio), vector<double>(y[0].size()));
	vector <vector <double>> y_test;
	y_train.resize(y.size(), vector<double>(y[0].size()));
	y_test.resize(X.size(), vector<double>(y[0].size()));
	//y_test.resize(y.size() - int(y.size() * training_ratio), vector<double>(y[0].size()));

	int RAND_MAX_SPLIT = (RAND_MAX / 10) * training_ratio;

	// Initialize sizes for X and y training and testing sets
	int X_train_size = 0;
	int X_test_size = 0;

	int y_train_size = 0;
	int y_test_size = 0;

	if (randTrainOrTest == "train") {
		for (size_t i = 0; i < data.size(); ++i) {
			int randInt = rand();
			if (randInt < RAND_MAX_SPLIT) {
				X_train[i] = X[i];
				y_train[i] = y[i];

				++X_train_size;
				++y_train_size;
			}
		}
		for (size_t i = 0; i < data.size(); ++i) {
			if (i >= int(X.size() * (training_ratio / 10))) {
				int k = i - X.size() * (training_ratio / 10);
				X_test[k] = X[k];
				y_test[k] = y[k];

				++X_test_size;
				++y_test_size;
			}
		}
	}
	else if (randTrainOrTest == "test") {
		for (size_t i = 0; i < data.size(); ++i) {
			if (rand() < RAND_MAX_SPLIT) {
				X_test[i] = X[i];
				y_test[i] = y[i];

				++X_test_size;
				++y_test_size;
			}
		}
		for (int i = 0; i < data.size(); i++) {	// ??? ????? ??? ????, ????? ??????????? ??????? ???????? ????????? ????
			if (i < int(X.size() * (training_ratio / 10))) {		// ????????????? ???? ????? ?? ??? ??????, ??????? ?? ?? ??????????? ??? ????????
				X_train[i] = X[i];
				y_train[i] = y[i];

				++X_train_size;
				++y_train_size;
			}
		}
	}

	// Resize x and y training and testing sets to current capacities
	X_train.resize(X_train_size, vector<double>(X[0].size()));
	X_test.resize(X_test_size, vector<double>(X[0].size()));

	y_train.resize(y_train_size, vector<double>(y[0].size()));
	y_test.resize(y_test_size, vector<double>(y[0].size()));

	vector <double> target;		// We declare auxiliary vectors
	target.resize(neural.outlayer);
	vector<double> person;
	person.resize(neural.zerolayer);
	vector <double> predict = neural.predict(person);
	double miss = 0;			// miss - the value of the miss is how much the neural network forecast differs from our expectations
	double count = 0;			// count - the number of times the model guessed the diagnosis 
	for (int i = 0; i < X_test.size(); i++) {
		person = X_test[i];
		target = y_test[i];
		predict = neural.predict(person);
		if (int(predict[0] + 0.5) == target[0]) {
			count++;
		}
	}
	double accuracy = count / X_test.size();	// Let's calculate the accuracy by dividing count by the number of patients examined in the cycle
	count = 0;
	outputFile << "Accuracy before learning: " << accuracy << endl;
	// Now let's train the neural network on the training data.
	for (int i = 0; i < X_train.size(); i++) {
		person = X_train[i];
		target = y_train[i];
		predict = neural.predict(person);	// we get a prediction
		miss = target[0] - predict[0];		// calculate the miss
		neural.learn_back_prop(miss);		// run the algorithm for backpropagation of the error from the obtained value of the miss
	}	// This completes the training of the network, then we test the calculated values ??of the link weights
	for (int i = 0; i < X_test.size(); i++) {
		person = X_test[i];
		target = y_test[i];
		predict = neural.predict(person);	// Now we will validate the network - we will calculate the accuracy on a previously unknown data network
		miss = target[0] - predict[0];
		if (int(predict[0] + 0.5) == target[0]) {
			count++;
		}
	}
	accuracy = count / X_test.size();		// Calculating the final precision
	outputFile << "Final accuracy:           " << accuracy << endl;
	outputFile << "Test predictions: ";
	// outputFile << neural.predict(X[55])[0] << " - " << y[55][0] << endl;
	// outputFile << neural.predict(X[601])[0] << " - " << y[601][0] << endl;
}

void RunNNControlledTrainAndTest(char* data_filename, double training_ratio, double test_ratio) {
	Neural neural = Neural();	// Let's declare a class object and specify a constructor for it

	ofstream outputFile("out.txt");

	vector <vector <double>> data = LoadData(data_filename);	// Load data from csv file into vector
	// Let's separate the analyzes from the diagnosis:
	vector <vector <double>> X;
	X.resize(data.size(), vector<double>(data[0].size() - 1));
	vector <vector <double>> y;
	y.resize(data.size(), vector<double>(1));

	// In this cycle, we will divide the input data into signs X and expectations y
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[0].size() - 1; j++) {
			X[i][j] = data[i][j];
		}
		y[i][0] = data[i][data[0].size() - 1];
	}
	// Divide X and y into training and test data:
	vector <vector <double>> X_train;
	X_train.resize(X.size(), vector<double>(X[0].size()));
	//X_train.resize(int(X.size() * training_ratio), vector<double>(X[0].size()));
	vector <vector <double>> X_test;
	X_test.resize(X.size(), vector<double>(X[0].size()));
	//X_test.resize(X.size() - int(X.size() * training_ratio), vector<double>(X[0].size()));

	vector <vector <double>> y_train;
	//y_train.resize(int(y.size() * training_ratio), vector<double>(y[0].size()));
	vector <vector <double>> y_test;
	y_train.resize(y.size(), vector<double>(y[0].size()));
	y_test.resize(X.size(), vector<double>(y[0].size()));
	//y_test.resize(y.size() - int(y.size() * training_ratio), vector<double>(y[0].size()));


	// Initialize sizes for X and y training and testing sets
	int X_train_size = 0;
	int X_test_size = 0;

	int y_train_size = 0;
	int y_test_size = 0;

	int X_validation_size = 0;
	int y_validation_size = 0;


	// copy data to vectors for splitting into train and test sets
	vector<vector<double>> X_for_splitting;
	vector<vector<double>> y_for_splitting;

	// iteratively copy original vectors into vectors for splitting
	for (size_t i = 0; i < X.size(); ++i) X_for_splitting.push_back(X[i]);
	for (size_t i = 0; i < y.size(); ++i) y_for_splitting.push_back(y[i]);


	// generate train and test sets
	for (size_t i = 0; i < data.size(); ++i) {
		if (i >= int(X.size() * training_ratio)) {
			int k = i - X.size() * training_ratio;
			X_train[i] = X_for_splitting[i];
			y_train[i] = y_for_splitting[i];

			++X_train_size;
			++y_train_size;

			// remove data points from vectors for splitting
			X_for_splitting.erase(X_for_splitting.begin() + (i - 1));
			y_for_splitting.erase(y_for_splitting.begin() + (i - 1));

		}
	}

	for (size_t i = 0; i < data.size(); ++i) {
		if (i >= int(X.size() * test_ratio)) {
			int k = i - X.size() * test_ratio;
			X_test[k] = X_for_splitting[k];
			y_test[k] = y_for_splitting[k];

			// increment test set size
			++X_test_size;
			++y_test_size;

			// remove data points from vectors for splitting
			X_for_splitting.erase(X_for_splitting.begin() + (i - 1));
			y_for_splitting.erase(y_for_splitting.begin() + (i - 1));
		}
	}


	// Resize x and y training and testing sets to current capacities
	X_train.resize(X_train_size, vector<double>(X[0].size()));
	X_test.resize(X_test_size, vector<double>(X[0].size()));

	y_train.resize(y_train_size, vector<double>(y[0].size()));
	y_test.resize(y_test_size, vector<double>(y[0].size()));

	vector <double> target;		// We declare auxiliary vectors
	target.resize(neural.outlayer);
	vector<double> person;
	person.resize(neural.zerolayer);
	vector <double> predict = neural.predict(person);
	double miss = 0;			// miss - the value of the miss is how much the neural network forecast differs from our expectations
	double count = 0;			// count - the number of times the model guessed the diagnosis 
	for (int i = 0; i < X_test.size(); i++) {
		person = X_test[i];
		target = y_test[i];
		predict = neural.predict(person);
		if (int(predict[0] + 0.5) == target[0]) {
			count++;
		}
	}
	double accuracy = count / X_test.size();	// Let's calculate the accuracy by dividing count by the number of patients examined in the cycle
	count = 0;
	outputFile << "Accuracy before learning: " << accuracy << endl;
	// Now let's train the neural network on the training data.
	for (int i = 0; i < X_train.size(); i++) {
		person = X_train[i];
		target = y_train[i];
		predict = neural.predict(person);	// we get a prediction
		miss = target[0] - predict[0];		// calculate the miss
		neural.learn_back_prop(miss);		// run the algorithm for backpropagation of the error from the obtained value of the miss
	}	// This completes the training of the network, then we test the calculated values ??of the link weights
	for (int i = 0; i < X_test.size(); i++) {
		person = X_test[i];
		target = y_test[i];
		predict = neural.predict(person);	// Now we will validate the network - we will calculate the accuracy on a previously unknown data network
		miss = target[0] - predict[0];
		if (int(predict[0] + 0.5) == target[0]) {
			count++;
		}
	}
	accuracy = count / X_test.size();		// Calculating the final precision
	outputFile << "Final accuracy:           " << accuracy << endl;
	outputFile << "Test predictions: ";
	// outputFile << neural.predict(X[55])[0] << " - " << y[55][0] << endl;
	// outputFile << neural.predict(X[601])[0] << " - " << y[601][0] << endl;
}

/*
* Checks whether a number is an integer
*/
bool isInt(char number[])
{
	int i = 0;

	//checking for negative numbers
	if (number[0] == '-')
		i = 1;
	for (; number[i] != 0; i++)
	{
		//if (number[i] > '9' || number[i] < '0')
		if (!isdigit(number[i]))
			return false;
	}
	return true;
}


int main(int argc, char* argv[]) {
	/*
	* min seed for heart: 1626980399.0
	* max seed for heart: 1626980714.0
	*
	* min seed for wine: 1626979872.0
	* max seed for wine: 1626978972.0
	*/
	srand((unsigned int)time(NULL));

	char* data = argv[1];

	// save train ratio input as double 
	double train_ratio;
	if (isInt(argv[2])) {
		// If train_ratio_input is an int, convert to double and divide by 10
		int train_ratio_int = atoi(argv[2]);
		train_ratio = double(train_ratio_int) / 10;
	}
	else {
		// Else convert character to double type
		char* train_ratio_input = argv[2];
		sscanf_s(argv[2], "%lf", &train_ratio);
	}

	// save test ratio input as double
	double test_ratio;
	if (isInt(argv[3])) {
		// If train_ratio_input is an int, convert to double and divide by 10
		int test_ratio_int = atoi(argv[3]);
		test_ratio = double(test_ratio_int) / 10;
	}
	else {
		// Else convert character to double type
		char* test_ratio_input = argv[3];
		sscanf_s(argv[3], "%lf", &test_ratio);
	}
	RunNeuralNet(data, train_ratio, test_ratio);
	//RunNeuralNetControlledData(out, train);
	//RunNeuralNetControlledTrainOrTest(out, TRAIN_RATIO, "train");
	//RunNNControlledTrainAndTest(out, train);

	// To generate samples: cd to outputs subfolder and run .bat file
}
