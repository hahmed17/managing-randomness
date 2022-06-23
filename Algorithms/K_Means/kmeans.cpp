/*

	Programmer:	Adam Mischke

	K means Algorithm:
	1. Given a set of N training examples each consisting of a vector of continuous attributes,
	   select K training examples to be a set of initial cluster means (centers)

	2. Determine the distance (many options to choose from here) between each training example
	   and each of the K cluster means

	3. Assign each training example to the closest cluster mean

	4. Calculate the average of the training examples assigned to each cluster mean (creates a new mean)

	5. Go back to step 2 until the cluster means do not change
	   (i.e. all training examples are assigned to the same cluster mean as on the previous iteration)


*/

#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <random>
#include <limits>
#include <sstream>
#include <iterator>
#include <set>
#include <iterator>
#include "srand-rand-function.h"

using std::vector;
using std::cout;
using std::string;
using std::cin;
using std::endl;
using std::ostream;
using namespace std;

/* typedeffing for ease of use */
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<int> vi;
typedef vector<vector<int > > vvi;

// checks whether a char type is an integer
bool isInt(char number[]);

// counts number of columns in a data set
size_t getNumFeatures(char* data_filename);

// Checks if string is comma delimited
bool isCommaDelimited(string line);

// Checks if string is space delimited
bool isSpaceDelimited(string line);

// Checks if string is tab delimited
bool isTabDelimited(string line);

// handles fstream from the filename into the 2d vector of doubles
void handleFile(const string fn, vvd& v);

// shuffles the traintable and initializes the centroid table with how ever many cluster we have
void initKmeans(vvd& centroidTable, vvd trainTable);

// returns true if centroids have not moved
// calculates the distances between the clusters and the points
bool calculateDistances(const vvd& train, vvd& centroid, vi& clusterTags);

// returns the euclidean distance of a particular vector
double calculateDistance(const vd& train, const vd& center);

// returns true if centroids have not moved
// moves the clusters means based on the number of rows in a cluster (avg)
bool updateClusters(const vvd& trainTable, vvd& centroidTable, const vi& clusterTags);

// goes through the training table and majority votes on which cluster goes with which class label
vi findLabels(const vvd& trainTable, const vi& clusterTags);

// returns how many are right
// tests our assigned labels of test with their actual from the testtable
int testLabels(const vvd& trainTable, const vvd& testTable, const vi& clusterTags, const vi& actualTable);

// returns which row it's in
// finds the closest point from the test table to the train table
int findClosestPoint(const vvd& trainTable, const vd& test);

// comparison of two vectors
bool equal(const vvd& oldCentroids, const vvd& newCentroids);

// random shuffle a vector
template< class RandomIt >
void random_shuffle2(RandomIt trainVect, size_t start, size_t end);

// Split data file into training and testing
void splitData(char* data_filename);

// Randomly split data file into training and testing
void randSplitData(char* data_filename, double train_ratio, double test_ratio);

// Randomize either train or test data set
void randomizeTrainOrTest(ifstream& dataFile, string trainOrTest, double split);

// Cnrol both train and test data sets
void controlTrainAndTest(ifstream& dataFile, double split);

/* PRINTING */
template <typename t> void print(vector<vector< t > >  v);
template <typename t> void print(vector< t >   v);

int NUM_CLUSTERS, NUM_FEATURES, NUM_CLASSIFICATIONS;


int main(int argc, char* argv[]) {
	/*
	* min seed for iris: 1626822009
	* max seed for iris: 1626822104
	*
	* min seed for breast tissue: 1626823074
	* max seed for breast tissue: 1626822789
	*
	*/

	srand((unsigned int)time(NULL));  // seed rand()

	// save command line arguments to variables 
	char* data_filename = argv[1];
	NUM_CLUSTERS = atoi(argv[4]);


	// save train ratio input as double 
	double train_ratio;
	if (isInt(argv[2])) {
		// If train_ratio_input is an int, convert to double and divide by 10
		int train_ratio_int = atoi(argv[2]);
		train_ratio = double(train_ratio_int) / double(10);
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
		test_ratio = double(test_ratio_int) / double(10);
	}
	else {
		// Else convert character to double type
		char* test_ratio_input = argv[3];
		sscanf_s(argv[2], "%lf", &test_ratio);
	}


	NUM_FEATURES = getNumFeatures(data_filename); // calculate number of features for data set
	randSplitData(data_filename, train_ratio, test_ratio);  // randomly shuffle and split data into train and test data set


	/*
	*	Kmeans initialization, training, testing starts here
	*/
	int numRight = 0;

	// string: input training data filename, 
	string trainFilename = "train";  // 

	// string: input testing data filename
	string testFilename = "test";  // 

	//cout << "initializing..\n";
	//cout << "seed: " << SEED << " num of clusters: " << NUM_CLUSTERS << " num of features: " << NUM_FEATURES << "\n";
	//cout << "training filename: " << trainFilename << " testing filename: " << testFilename << "\n";


	vvd trainTable;		// 2d vector of doubles
	vvd testTable;		// same
	vvd centroidTable;	// same

	vi clusterTags;		// 1d vector of clusters
	vi actualTable;		// actual classification of test table

	// read in the training data into the training table
	handleFile("train", trainTable);
	/*std::set<int> result;
	for (int i = 0; i < trainTable.size(); ++i) {
		result.insert(trainTable[i][NUM_FEATURES - 1]);
	}*/
	NUM_CLASSIFICATIONS = trainTable.size();
	// cout << NUM_CLASSIFICATIONS << "\n";

	// same with the testing data
	handleFile(testFilename, testTable);

	// inaitialize the centroid table with random doubles
	initKmeans(centroidTable, trainTable);

	int moves = 0;	// iterator

	// we need the last cluster tags to help finding and classifying labels 
	while (!calculateDistances(trainTable, centroidTable, clusterTags))
	{
		moves++;
	}


	//cout << "num of moves: " << moves << "\n";

	// assign the cluster means to an actual class label
	actualTable = findLabels(trainTable, clusterTags);

	// Create output file
	ofstream out("./out.txt");

	// returns how many are right
	numRight = testLabels(trainTable, testTable, clusterTags, actualTable);
	int numTotal = testTable.size();
	double accuracy = (float)numRight / (float)numTotal;

	// Send outputs to out file
	out << "Correct: " << numRight << endl;
	out << "Total: " << numTotal << endl;
	out << "Accuracy: " << accuracy << endl;

	out.close();
}

template< class RandomIt >
void random_shuffle2(RandomIt trainVect, size_t start, size_t end) {
	if (start == end) {
		return;
	}
	for (int i = end - 1; i > start; --i) {
		trainVect[i].swap(trainVect[start + rand() % (i + 1)]);
	}
}

size_t getNumFeatures(char* data_filename) {
	ifstream datafile(data_filename);

	// Get number of columns in data set
	string line;
	getline(datafile, line);

	// save entries of first row to vector
	string entry;
	stringstream ss(line);

	char delimiter = ' ';
	// Check file delimiter
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
		cout << "Unrecognized delimiter. Enter a comma, space, or tab delimited file." << endl;
	}

	vector<string> first_row_vec;
	while (getline(ss, entry, delimiter)) {
		first_row_vec.push_back(entry);
	}

	// The number of features is the number of columns, i.e. the number of entries in the first row
	size_t numFeatures = first_row_vec.size();
	return numFeatures;
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

void splitData(char* data_filename) {
	ifstream dataFile(data_filename);
	ofstream trainFile("../train");
	ofstream testFile("../test");

	// Create a list of each line in the data file
	vector<string> lines;
	for (string line; getline(dataFile, line);) {
		lines.push_back(line);
	}
	// random_shuffle2(lines, 0, lines.size());

	 // Determine train to test ration
	double split = .3;  // Percentage of dataset that goes to training file
	int split_index = lines.size() * split;

	for (size_t i = 0; i < split_index; ++i) {
		trainFile << lines[i] << endl;
	}
	for (size_t i = split_index; i < lines.size(); ++i) {
		testFile << lines[i] << endl;
	}

	trainFile.close();
	testFile.close();
}

void randomizeTrainOrTest(ifstream& dataFile, string trainOrTest, double split) {
	// Create a list of each line in the data file
	vector<string> lines;
	for (string line; getline(dataFile, line);) {
		lines.push_back(line);
	}

	// train/test ratio
	int split_index = lines.size() * split;
	int int_split = split * 10;
	int RAND_MAX_SPLIT = (RAND_MAX / 10) * int_split;

	ofstream trainFile("train");
	ofstream testFile("test");

	if (trainOrTest == "train") {
		for (size_t i = 0; i < lines.size(); ++i) {
			int randomNum = rand();
			if (randomNum < RAND_MAX_SPLIT) {
				trainFile << lines[i] << endl;
			}
		}
		for (size_t i = split_index; i < lines.size(); ++i) {
			testFile << lines[i] << endl;
		}
	}
	else if (trainOrTest == "test") {
		for (size_t i = 0; i < lines.size(); ++i) {
			int randomNum = rand();
			if (randomNum >= RAND_MAX_SPLIT) {
				testFile << lines[i] << endl;
			}
		}
		for (size_t i = 0; i < split_index; ++i) {
			trainFile << lines[i] << endl;
		}
	}

	trainFile.close();
	testFile.close();
}


void randSplitData(char* data_filename, double train_ratio, double test_ratio) {
	ifstream dataFile(data_filename);
	ofstream trainFile("train");
	ofstream testFile("test");

	// Create a list of each line in the data file
	vector<string> lines;
	for (string line; getline(dataFile, line);) {
		lines.push_back(line);
	}

	// randomly assign data to train data set
	int rand_train_split = RAND_MAX * train_ratio;
	for (vector<string>::iterator it = lines.begin(); it != lines.end(); ++it) {
		int randomNum = rand();
		if (randomNum < rand_train_split) {
			trainFile << *it << endl;
			lines.erase(it);  // TODO: erase line from vector
		}
	}

	//for (size_t i = 0; i < lines.size(); ++i) {
	//	int randomNum = rand();
	//	if (randomNum < rand_train_split) {
	//		trainFile << lines[i] << endl;
	//		lines.erase(lines.begin() + (i-1));  // TODO: erase line from vector
	//	}
	//}

	int rand_test_split = RAND_MAX * test_ratio;
	for (size_t i = 0; i < lines.size(); ++i) {
		int randomNum = rand();
		if (randomNum < rand_test_split) {
			testFile << lines[i] << endl;
		}
	}
}



void controlTrainAndTest(ifstream& dataFile, double split) {
	ofstream trainFile("train");
	ofstream testFile("test");

	// Create a list of each line in the data file
	vector<string> lines;
	for (string line; getline(dataFile, line);) {
		lines.push_back(line);
	}

	// Determine train to test ration
	int split_index = lines.size() * split;

	for (size_t i = 0; i < split_index; ++i) {
		trainFile << lines[i] << endl;
	}
	for (size_t i = split_index; i < lines.size(); ++i) {
		testFile << lines[i] << endl;
	}

	trainFile.close();
	testFile.close();
}


// returns the position of the point (row in traintable) of which the closest point of the test point is 
int findClosestPoint(const vvd& trainTable, const vd& test) {

	double dist = 0.0, closestPoint = 0.0;
	int indice = 0;

	// set the closest point to inf
	closestPoint = std::numeric_limits<double>::max();

	for (int j = 0; j < trainTable.size(); j++) {
		dist = calculateDistance(trainTable[j], test);		// find the distance between the two sets

		// if the distance we just got is the lowest in the clusters,
		if (dist < closestPoint)
		{
			closestPoint = dist;			// set some values
			indice = j;
		}
	}
	//cout << "dist: " << closestPoint << "\n";
	return indice;		// return the indice of the closest point
}

// tests the labels from the test table
int testLabels(const vvd& trainTable, const vvd& testTable, const vi& clusterTags, const vi& actualTable) {

	int classification = 0, guess = 0, modGuess = 0, correct = 0;
	vi guessList{};
	//cout << "oldClassification:\n";
	for (int i = 0; i < testTable.size(); i++) {

		// returns the indice of the closest point from the test table set
		// from the entirety of the training table
		classification = findClosestPoint(trainTable, testTable[i]);

		// pick the guess from the position found
		guess = clusterTags[classification];

		// modify the guess from the actual table
		modGuess = actualTable[guess];

		// push the modified guess to the guess list
		guessList.push_back(modGuess);
	}
	//cout << "\n";
	//print(guessList);

	// iterate between both sets and count the correct guesses
	for (int i = 0; i < testTable.size(); ++i) {
		cout << "guess: " << guessList[i] << " actual: " << testTable[i][NUM_FEATURES - 1] << "\n";
		if (guessList[i] == testTable[i][NUM_FEATURES - 1]) {
			correct++;	// increase the correct counter if the classification is correct
		}
	}
	return correct;	// return how many are correct
}

// finds the labels of the training table and returns the actual labels associated with the classificatons
vi findLabels(const vvd& trainTable, const vi& clusterTags) {

	vvi countTable(NUM_CLUSTERS, vector<int>(NUM_CLASSIFICATIONS));	// temp 2d vector used to count the probability of which classification 
																// belongs to a given cluster mean
	vi actualTable(NUM_CLUSTERS);								// table used to return the actual classification

	int actual = 0, tag = 0; // actual

	// iterate throught the training table..
	for (int r = 0; r < trainTable.size(); r++) {
		actual = trainTable[r][NUM_FEATURES - 1];		// the actual classification for that training set
		tag = clusterTags[r];						// the tag associated with the training set
		countTable[tag][actual]++;					// increase the count withe the actual as the row and the tag as the column
	}

	// iterate through the number of cluster means
	for (int r = 0; r < NUM_CLUSTERS; r++) {
		// class label will be assigned to each vector by taking a majority vote amongst it's assigned examples 
		// from the training set (ties will be broken by preferring the smallest integer class label).
		actualTable[r] = distance(countTable[r].begin(), max_element(countTable[r].begin(), countTable[r].end()));
	}

	return actualTable;	// return the key map for the actual classifications
}

// returns whether centroids from old are the same as the new
// if it is, we'll break from the main loop
bool equal(const vvd& oldCentroids, const vvd& newCentroids) {

	size_t rows = newCentroids.size();			// # of rows
	size_t columns = newCentroids[0].size();	// # of columns

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			//if ( fabs( newCentroids[i][j] - oldCentroids[i][j] ) < std::numeric_limits<double>::min() )		// is this close enough?
				// return false;
			//cout << "new " << newCentroids[i][j] << " old " << oldCentroids[i][j] << "\n";
			if (newCentroids[i][j] != oldCentroids[i][j])	// c++11 allows comparison operator
				return false;
		}
	}
	return true;
}

// updates the cluster means by averaging all of the rows that fit the cluster tags from the centroid table
bool updateClusters(const vvd& trainTable, vvd& centroidTable, const vi& clusterTags) {

	vi countedClusters;		// initialize a new vector of ints for the number of clusters in each classification
	bool done = false;		// flag for when to exit the loop in main

	// create a new table for the centroids
	vvd newCentroids(NUM_CLUSTERS, vector<double>(NUM_FEATURES));


	// iterate through the rows
	for (int i = 0; i < trainTable.size(); i++) {
		// and columns of the centroid table
		for (int j = 0; j < centroidTable[0].size(); j++) {
			// increment the new centroid table based on the training table value
			// use the clustertag as the row and the iterator as the column
			newCentroids[clusterTags[i]][j] += trainTable[i][j];
		}
	}

	for (int i = 0; i < NUM_CLUSTERS; i++) {
		countedClusters.push_back(count(clusterTags.begin(), clusterTags.end(), i));
	}

	//print (countedClusters);
	// divides each value by it's average
	for (int i = 0; i < newCentroids.size(); i++) {
		for (int j = 0; j < newCentroids[0].size(); j++) {

			if (countedClusters[i] != 0)		// prevent nan if the number near the cluster is 0
			{
				newCentroids[i][j] /= countedClusters[i];
			}
			else
			{
				newCentroids[i][j] = centroidTable[i][j];	// use the old one
			}


		}
	}

	// if the number of the old and new cluster are the same, the centroids have not moved
	if (equal(centroidTable, newCentroids)) {
		done = true;
		//cout << "done!\n";		// therefore, set that we are done and return
		return done;
	}

	centroidTable = newCentroids;	// updates the centroid table

	return done;					// returns false if we get this far
}

// distance function between two vectors
double calculateDistance(const vd& train, const vd& center) {
	double total = 0.0;	// initialize a distance

	// iterate through each column
	for (int i = 0; i < NUM_FEATURES; i++)
		total += pow(center[i] - train[i], 2);	// take the two components, subtract and raise to the second power

	return sqrt(total);	// return the square root of the total
}

// calulates the distances from each cluster mean and their respective points from the training table
bool calculateDistances(const vvd& trainTable, vvd& centroidTable, vi& clusterTags) {

	vd centroid;				// one center information
	vd training;				// one training information
	double dist = 0.0;			// distace calculated between a row in the center and a row in the train table
	double lowestDist = 0.0;	// lowest one in the whole training table
	int lowestCentroid = 0;		// the lowest row number in the centroid table
	int lowestRow = 0;			// the lowest row number in the train table
	bool done = false;			// flag for when to exit the while loop in main
	clusterTags.clear();		// reset the cluster tags

	// for each row in the training table
	for (int r = 0; r < trainTable.size(); r++) {

		lowestDist = std::numeric_limits<double>::max(); 	// reset distance
		training = trainTable[r];							// grab the row

		// for each cluster..
		for (int c = 0; c < NUM_CLUSTERS; c++) {
			centroid = centroidTable[c];					// grab the other row

			// pass the rows to a function that calculates the distance 
			dist = calculateDistance(training, centroid);
			//cout << "distance from: [" << r << ", " << c << "] is: " << dist << "\n";

			// if the distance we just got is the lowest in the clusters,
			if (dist < lowestDist)
			{
				lowestDist = dist;			// set some values
				lowestCentroid = c;
				lowestRow = r;
			}
		}
		//cout << "winner is..[" << lowestRow << ", " << lowestCentroid << "] is: " << lowestDist << "\n";
		clusterTags.push_back(lowestCentroid);	// then push the lowest center into a vector of tags

	}
	// update the means of the clusters
	done = updateClusters(trainTable, centroidTable, clusterTags);

	return done;	// return whether the clusters haven't been updated
}

// initializes the cluster means by picking a random row from the training table
void initKmeans(vvd& centroidTable, vvd trainTable) {

	//  good init, but shuffle the train table..
	random_shuffle2(trainTable, 0, trainTable.size());
	for (int i = 0; i < NUM_CLUSTERS; i++) {
		vd tempVec;
		//tempVec.resize(trainTable.size());
		for (int j = 0; j < NUM_FEATURES; j++) {
			tempVec.push_back(trainTable[i][j]);
		}
		centroidTable.push_back(tempVec);
	}

	//cout << "\n";
}

// handles the file input by opening an input filestream to open a string filename
// then puts the values of doubles into a 2 dimensional vector
void handleFile(string fn, vvd& v) {
	ifstream in;		// input filestream
	in.open(fn);			// open

	for (string line; getline(in, line); )
	{
		// replace delimiters with spaces to use istream_iterator
		if (isCommaDelimited(line)) {
			replace(line.begin(), line.end(), ',', ' ');  
		}
		else if (isTabDelimited(line)) {
			replace(line.begin(), line.end(), '\t', ' '); 
		}

		istringstream iss(line);
		v.emplace_back(istream_iterator<double>(iss),  // feed into the temp double from above
			istream_iterator<double>());

	}
	in.close();				// close
}

/* Templated Print Statements for double and single vectors */
template <typename t>
void print(vector<vector< t > >  v) {
	for (auto& i : v) {
		for (auto& j : i) {
			cout << j << " ";
		}
		cout << "\n";
	}cout << "\n";

}
template <typename t>
void print(vector< t >   v) {
	for (auto& i : v) {
		cout << i << " ";
	}
	cout << "\n";
}
