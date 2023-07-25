# Managing Randomness to Enable Reproducible Machine Learning #

DOI: 10.1145/3526062.3536353


## Source code

Neural network: https://github.com/TessaTlu/cpp_neural_heart_disease

K-means clustering: https://github.com/vanities/K_Means

Naive Bayes: https://github.com/lrvine/Bayesian


# Running experiments

## Neural net

1. Change to directory where "neural-net.cpp" is located.
2. Compile and link with srand()/rand() converter (assuming "srand-rand-functions.cpp" is in the parent directory):

    `cl -c neural-net.cpp ..\srand-rand-functions.cpp`

    `cl neural-net.cpp srand-rand-functions.cpp -o neural-net.exe`

3. Generate, train, and test a model by calling the executable file with the following 3 command line arguments: dataset file location, training ratio, test ratio. For example:

    `.\neural-net.exe data\iris.csv .3 .7`

will train a neural network on 30% of the Iris data set and test the neural net on the remaining 70% of Iris. In the same directory where the exectuable file is called, "out.txt" (prints the model's final accuracy) and "seedFile.txt" (stores the model's random number seed) will be written. The neural network source code should be compatible with all six data sets in .csv or .txt format.


## K-Means Clustering

Same as neural net except:
1. Replace "neural-net" with "kmeans" (i.e., "kmeans.cpp", "kmeans.exe")

2. Add a fourth command line argument: number of clusters (an integer). Example:
    `.\kmeans.exe data\iris.csv .3 .7 3`
where 3 is the number of clusters the data set will be grouped in.

Similar to the neural network, the k-means code is compatible with all six data sets in .csv or .txt format, and "out.txt" and "seedFile.txt" files are written for each model generated.


## Naive Bayes

1. Change to the directory where "naivebayesian.cc", "bayesian.cc", "machinelearning.cc", and "main.cc" are located. (They should all be located within the same directory.)

2. Compile and link all files with srand()/rand() converter:

    `cl -c naivebayesian.cc bayesian.cc machinelearning.cc main.cc ..\srand-rand-functions.cc`

    `cl naivebayesian.cc bayesian.cc machinelearning.cc main.cc ..\srand-rand-functions.cc -o bayesian.exe"

3. Call the executable file with 4 command line arguments: dataset file location, train ratio, test ratio, configuration file location.

    `.\bayesian.exe breast_cancer_data\breast-cancer-wisconsin.data .3 .7 breast_cancer_data\breast-cancer-wisconsin.cfg`

    `.\bayesian.exe happiness_data\SomervilleHappiness.data .3 .7 happiness_data\happiness.cfg`

An "out.txt" and "seedFile.txt" files should be written to the same directory where the executable was called from.

**Notes about Naive Bayes:** Currently, the naive Bayes source code is only compatible with the Somerville Happiness and Wisconsin Breast Cancer (Original) data sets. This is because we currently have written configuration (.cfg) files for these two data sets. (See the original GitHub repo for formatting the configuration files: https://github.com/lrvine/Bayesian.) Making the naive Bayes algorithm compatible with .csv and .txt data set files is also a work in progress.
