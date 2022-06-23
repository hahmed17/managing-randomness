Using naive Bayes code: https://github.com/lrvine/Bayesian

**7/4**
1. Using k-means algorithm for Iris and Cancer data sets: https://github.com/vanities/K_Means
2. Ran a Python program to determine the optimal number of clusters (4 or 5) for Cancer data using the "Elbow Method"

**7/2**
1. Modified neural net source code for wine dataset (https://archive.ics.uci.edu/ml/datasets/Wine). I reordered the columns, the one change being that the first column (the classes of wine) is now that last column. I did this because the source code seems to assume that there is a "diagnosis column", which in the heart disease dataset is the last column. This would mean that for any other dataset, the neural net would also assume that last column will contain classes/diagnoses.
2. Potential next models: 
    - Decision Tree, Wine quality data: https://github.com/DerrickDx/RedWineQualityPrecdtion
    - KNN, Iris data: https://github.com/marcoscastro/knn
    - K-Means, Iris and Cancer data: https://github.com/vanities/K_Means

**7/1:**

Starting at the directory where the neural network source code lives, these are the commands I used to generate 100 samples:

C:\Users\hahmed\source\repos\cpp_neural_net> cl -c Source.cpp

C:\Users\hahmed\source\repos\cpp_neural_net> cl Source.cpp -o Source.exe

C:\Users\hahmed\source\repos\cpp_neural_net> cd outputs-heart

C:\Users\hahmed\source\repos\cpp_neural_net> .\batch_run.bat

Notes:
- outputs-heart is the directory where I wanted the samples to be stored
- The NN source code assumes that the data is in a directory called ..\..\data

**6/30:**
1. Identified a neural network algorithm that trains on heart disease dataset (UCI ML Repository)
2. See neural network source code at GitHub repo here: https://github.com/TessaTlu/cpp_neural_heart_disease 
3. Retrieved wine and wine quality datasets from UCI ML Repository 
