#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstring>
#define BOOST_TEST_MODULE myTestCases
#include <boost/test/included/unit_test.hpp>
#include "Source.cpp"

#if 0
BOOST_AUTO_TEST_CASE(myTestCase)
{
	BOOST_TEST(1 == 1);
	BOOST_TEST(true);
}
#endif

using namespace std;

// run once to generate the testing setup
// run a second time to actually test
// to test with fixed seeds, change this define to true or false (no fixed seed)

#define FIXED_SEED false
#define val_count 5

ofstream vals("vals.bin");
ifstream seedFile("seedFile.txt");
bool fileExists = seedFile.good();  // Checks whether file exists

BOOST_AUTO_TEST_SUITE(suite_srand_tests)

BOOST_AUTO_TEST_CASE(srand_and_no_file)
/* Test that srand was called and no seed file exists*/
{	
	srand(time(NULL)); // an arbitrary, fixed value to test against.

	for (int i = 0; i < val_count; i++) {
		int randInt = rand();
		string randString = to_string(randInt);
		cout << randString << endl;
		vals << randString + "\n";

		BOOST_TEST(true);
	}
	
}

BOOST_AUTO_TEST_CASE(srand_and_file)
/* Test that srand was called and a seed file exists*/
{
	srand(time(NULL)); // an arbitrary, fixed value to test against.

	ifstream vals;
	string RandLine;

	while (getline(vals, RandLine)) {
		int val;
		stringstream ss(RandLine);
		ss >> val;

		BOOST_TEST(val == rand());
	}

	// Remove seed file and vals file
	remove("seedFile.txt");
	remove("vals.bin");
}


BOOST_AUTO_TEST_CASE(no_srand_and_no_file)
/* Test that srand was not called and no seed file exists*/
{
	for (int i = 0; i < val_count; i++) {
		int randInt = rand();
		string randString = to_string(randInt);
		cout << randString << endl;
		vals << randString;

		BOOST_TEST(true);
	}
}

BOOST_AUTO_TEST_CASE(no_srand_and_file)
/* Test that srand was not called and a seed file exists*/
{
	ifstream vals;
	string RandLine;

	while (getline(vals, RandLine)) {
		int val;
		stringstream ss(RandLine);
		ss >> val;

		BOOST_TEST(val == rand());
	}

	// Remove seed file and vals file
	remove("seedFile.txt");
	remove("vals.bin");
}

BOOST_AUTO_TEST_SUITE_END()
