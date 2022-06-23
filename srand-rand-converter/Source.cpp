#include <iostream>
#include <cstdlib>
#include <cmath>
#include <random>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <sstream>

using namespace std;


static bool srandCalled = false;
static int callNumber = 0;

/*
* srand()
* Intercepts std::srand()
* Takes integer as input and sets seed to given value
*/
inline void srand(unsigned int seed) {
    srandCalled = true;  // Flag that srand has been called

    // Open a file to store seed
    ofstream seedFile;
    seedFile.open("seedFile.txt");

    // Write seed value to file
    string SeedString = to_string(seed);
    seedFile << SeedString;

    seedFile.close();  // Close seed file
}



/*
* rand()
*
* intercepts std::rand(), generates a random number using minstd_rand,
* then prints and returns the random number
*
*/
inline int rand(void) {
    // Read seed value from the seed file
    ifstream seedFile("seedFile.txt");

    unsigned int seedVal;
    bool fileNotExistOrEmpty = !seedFile.good() || (seedFile.peek() == ifstream::traits_type::eof());  // Checks whether file exists and empty
    if (fileNotExistOrEmpty) {  // First call to rand(), generate random seed
        seedVal = time(NULL);
        if (!srandCalled) {  // Store seed
            srand(seedVal);
        }
    }
    else {
        // Read stored seed from first line of the file
        string SeedLine = "";
        getline(seedFile, SeedLine);

        // Save first line as seed value
        stringstream ss(SeedLine);
        ss >> SeedLine;
        seedVal = stoi(SeedLine);

        ++callNumber;
    }

    // Seed and generate random number
    mt19937 mt_rand(seedVal);
    unsigned int randomNum = mt_rand._Ax[callNumber];

    // Print and return random number
    cout << randomNum << endl;
    return randomNum;
}
