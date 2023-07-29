#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctype.h>

#include "bayesiannetwork.h"
#include "naivebayesian.h"
//#include "../srand-rand-function.h"

using namespace std;

bool isInt(char number[]);
void split_data(char* data, double train_ratio, double test_ratio);
void randomize_train_data(char* data, char* train_file, int split);
void randomize_test_data(char* data, char* test_file, int split);
void control_train_and_test_data(char* data, char* train_file, char* test_file, int split);
void control_train_data(char* data, char* train_file, int split);
void control_test_data(char* data, char* test_file, int split);

int main(int argc, char **argv) {
    // Set seed and randomly split the data
    /*
    * BC min accuracy seed: 1628519856.0
    * BC max accuracy seed: 1628519871.0
    *
    * Happiness min accuracy seed: 1628519077.0
    * Happiness max accuracy seed: 1628519462.0
    */
    srand((unsigned int)time(NULL));
    //cout << argv[1] << endl << argv[2] << endl << argv[3] << endl << argv[4] << endl << argv[5] << endl;

    int method = 0;
    char* data = argv[1];
    char *cfg = argv[4];
    clock_t begin;
    clock_t end;
    double time_spent = 0.0;
    vector<int> prediction_result;

    // convert input train ratio to double
    double train_ratio;
    if (isInt(argv[2])) {
        int train_ratio_int = atoi(argv[2]);
        train_ratio = double(train_ratio_int) / double(10);
    }
    else {
        char *train_ratio_input = argv[2];
        sscanf_s(argv[2], "%lf", &train_ratio);
    }

    // convert input test ratio to double
    double test_ratio;
    if (isInt(argv[3])) {
        int test_ratio_int = atoi(argv[3]);
        test_ratio = double(test_ratio_int) / double(10);
    }
    else {
        char* test_ratio_input = argv[3];
        sscanf_s(argv[3], "%lf", &test_ratio);
    }

    split_data(data, train_ratio, test_ratio);
    //control_test_data(data, test, split_int);
    //randomize_train_data(data, train, split_int);
    //control_train_and_test_data(data, train, test, split_int);

    begin = clock();

    machinelearning::bayesian::NaiveBayesian naive(cfg);
    naive.Train();
    prediction_result = naive.Predict(1);
    // Call function to do prediction
    // Pass second argument "1" to denote that we will provide answer/truth for
    // this prediction. Pass sencond argument "0" to do real prediction.
    

    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Time spent " << time_spent << " seconds " << std::endl;
    return 0;
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


/*
* randomly assigns data to training and testing files
*/
void split_data(char* data, double train_ratio, double test_ratio) {

    // Load data
    ifstream dataFile(data);

    // Create and open train file
    ofstream trainFile("train");
    //trainFile.open("train", ios::out);

    // Create and open test file
    ofstream testFile("test");
    //testFile.open("test", ios::out);

    // Determine train to test ration
    //string input{ argv[2] };
    //int split = stoi(input);  // command line input is an integer
    //int split = 3;
    int RAND_MAX_SPLIT = RAND_MAX * train_ratio;

    // Create a list of each line in the data file
    vector<string> lines;
    for (string line; getline(dataFile, line);) {
        lines.push_back(line);
    }

    int train_size = 0;
    // randomly assign data to train data set
    int rand_train_split = RAND_MAX * train_ratio;
    for (size_t i = 0; i < lines.size(); ++i) {
        int randomNum = rand();
        if (randomNum < rand_train_split) {
            trainFile << lines[i] << endl;
            ++train_size;
            lines.erase(lines.begin() + (i - 1));
        }
    }

    int rand_test_split = RAND_MAX * test_ratio;
    for (size_t i = 0; i < lines.size(); ++i) {
        int randomNum = rand();
        if (randomNum < rand_test_split) {
            testFile << lines[i] << endl;
        }
    }

    cout << train_size << endl;
    // Close train and test file
    //trainFile.close();
    //testFile.close();
}


/*
* randomly assigns data to train file
*/
void randomize_train_data(char* data, char* train_file, int split) {

    // Load data
    ifstream dataFile(data);

    // Create and open train file
    ofstream trainFile;
    trainFile.open(train_file, ios::out);

    // Determine train to test ration
    //string input{ argv[2] };
    //int split = stoi(input);  // command line input is an integer
    //int split = 3;
    int RAND_MAX_SPLIT = (RAND_MAX / 10) * split;

    // Create a list of each line in the data file
    vector<string> lines;
    for (string line; getline(dataFile, line);) {
        lines.push_back(line);
    }

    int train_size = 0;
    // cout << RAND_MAX*split << endl;
    for (size_t i = 0; i < lines.size(); ++i) {
        int randomNum = rand();
        if (randomNum < RAND_MAX_SPLIT) {
            trainFile << lines[i] << endl;
            ++train_size;
        }
    }

    // Close train and test file
    trainFile.close();
}


/*
* randomly assigns data to test file
*/
void randomize_test_data(char* data, char* test_file, int split) {

    // Load data
    ifstream dataFile(data);

    // Create and open train file
    ofstream testFile;
    testFile.open(test_file, ios::out);

    // Determine train to test ration
    //string input{ argv[2] };
    //int split = stoi(input);  // command line input is an integer
    //int split = 3;
    int RAND_MAX_SPLIT = (RAND_MAX / 10) * split;

    // Create a list of each line in the data file
    vector<string> lines;
    for (string line; getline(dataFile, line);) {
        lines.push_back(line);
    }

    int train_size = 0;
    // cout << RAND_MAX*split << endl;
    for (size_t i = 0; i < lines.size(); ++i) {
        int randomNum = rand();
        if (randomNum >= RAND_MAX_SPLIT) {
            testFile << lines[i] << endl;
            ++train_size;
        }
    }

    // Close train and test file
    testFile.close();
}


/*
* splits a data file into training and test file given a split ratio
*/
void control_train_and_test_data(char* data, char* train_file, char* test_file, int split) {
    // Load data
    ifstream dataFile(data);

    // Create and open train file
    ofstream trainFile;
    trainFile.open(train_file, ios::out);

    // Create and open test file
    ofstream testFile;
    testFile.open(test_file, ios::out);
    //testFile << "test" << endl;  // worked; written to test file
    double train_split = double(split) / 10;

    // Create a list of each line in the data file
    vector<string> lines;
    for (string line; getline(dataFile, line);) {
        lines.push_back(line);
    }

    for (size_t i = 0; i < lines.size(); ++i) {
        if (i < lines.size() * train_split) {
            trainFile << lines[i] << endl;
        }
        else {
            testFile << lines[i] << endl;
        }
    }

    // Close train and test files
    trainFile.close();
    testFile.close();
}

/*
* splits a data file test file given a split ratio
*/
void control_train_data(char* data, char* train_file, int split) {
    // Load data
    ifstream dataFile(data);

    // Create and open train file
    ofstream trainFile;
    trainFile.open(train_file, ios::out);

    double train_split = double(split) / 10;

    // Create a list of each line in the data file
    vector<string> lines;
    for (string line; getline(dataFile, line);) {
        lines.push_back(line);
    }

    for (size_t i = 0; i < lines.size(); ++i) {
        if (i < lines.size() * train_split) {
            trainFile << lines[i] << endl;
        }
    }

    // Close train file
    trainFile.close();
}

/*
* splits a data file into training file given a split ratio
*/
void control_test_data(char* data, char* test_file, int split) {
    // Load data
    ifstream dataFile(data);

    // Create and open test file
    ofstream testFile;
    testFile.open(test_file, ios::out);
    //testFile << "test" << endl;  // worked; written to test file
    double train_split = double(split) / 10;

    // Create a list of each line in the data file
    vector<string> lines;
    for (string line; getline(dataFile, line);) {
        lines.push_back(line);
    }

    for (size_t i = 0; i < lines.size(); ++i) {
        if (i >= lines.size() * train_split) {
            testFile << lines[i] << endl;
        }
    }

    // Close test file
    testFile.close();
}