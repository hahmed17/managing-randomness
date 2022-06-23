set algorithm=%1
set dataset=%2
set num_runs=%3
set train_ratio=%4
set test_ratio=%5
set extra_arg=%6

set ALGS_DIR=C:\Users\hahmed\source\repos\managing-randomness-to-enable-reproducible-ML\Algorithms
set DATA_DIR=C:\Users\hahmed\source\repos\managing-randomness-to-enable-reproducible-ML\Datasets

mkdir BatchResults
cd BatchResults
if %algorithm% == neural-net (
	mkdir neural-net
	cd neural-net
	mkdir %dataset%
	cd %dataset%
	for /l %%i in (1, 1, %num_runs%) do (
		mkdir sample%%i
		cd sample%%i
		%ALGS_DIR%\cpp_neural_net\neural-net.exe %DATA_DIR%\%dataset%.csv %train_ratio% %test_ratio%
		cd..
		timeout 3
	)
	cd..\..\..\
)
if %algorithm% == k-means (
	mkdir k-means
	cd k-means
	mkdir %dataset%
	cd %dataset%
	for /l %%i in (1, 1, %num_runs%) do (
		mkdir sample%%i
		cd sample%%i
		%ALGS_DIR%\K_Means\kmeans.exe %DATA_DIR%\%dataset%.csv %train_ratio% %test_ratio% %extra_arg%
		cd..
		timeout 3
	)
	cd..\..\..\
)
if %algorithm% == naive-bayes (
	mkdir naive-bayes
	cd naive-bayes
	mkdir %dataset%
	cd %dataset%
	for /l %%i in (1, 1, %num_runs%) do (
		mkdir sample%%i
		cd sample%%i
		%ALGS_DIR%\naive_bayes\bayesian.exe %DATA_DIR%\%dataset%.csv %train_ratio% %test_ratio% %DATA_DIR%\%dataset%.cfg
		cd..
		timeout 3
	)
	cd..\..\..\
)