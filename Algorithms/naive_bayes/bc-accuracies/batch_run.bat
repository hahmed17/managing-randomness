for /l %%i in (1, 1, 100) do (
    mkdir sample%%i
    cd sample%%i
    ..\..\splitdata.exe ..\..\breast_cancer_data\breast-cancer-wisconsin-2.data
    ..\..\bayesian train test ..\..\breast_cancer_data\breast-cancer-wisconsin.cfg 0
    cd ..
    timeout 5
)