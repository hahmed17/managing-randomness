#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <random>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <sstream>

using namespace std;


static bool srandCalled = false;
static mersenne_twister_engine<uint_fast32_t,
    32, 624, 397, 31, 0x9908b0df, 11, 0xffffffff, 7, 0x9d2c5680, 15, 0xefc60000, 18, 1812433253> generator;

extern "C" {
    /*
    * srand()
    * Intercepts std::srand()
    * Takes integer as input and sets seed to given value
    */
    void srand(unsigned int seed) {
        srandCalled = true;  // Flag that srand has been called

        ifstream seedFile;
        seedFile.open("seedFile.txt");
        if (seedFile.fail()) {  // If no file exists, create one
            // Open a file to store seed
            ofstream seedFile;
            seedFile.open("seedFile.txt");

            // Write seed value to file
            string SeedString = to_string(seed);
            seedFile << SeedString;

            seedFile.close();  // Close seed file
        }
        else {  // If a file exists, set the seed to the stored seed
            string seedLine;
            getline(seedFile, seedLine);
            seed = (unsigned int)stoi(seedLine);
        }

        generator.seed(seed);

    }



    /*
    * rand()
    *
    * intercepts std::rand(), generates a random number using minstd_rand,
    * then prints and returns the random number
    *
    */
    int rand(void) {

        if (!srandCalled) {
            unsigned int seedVal = (unsigned int)time(NULL);
            srand(seedVal);
        }

        // Print and return random number
        unsigned int randInt = (generator() >> 1);
        //cout << randInt << endl;
        return randInt;
        // return std::rand();
    }
}
