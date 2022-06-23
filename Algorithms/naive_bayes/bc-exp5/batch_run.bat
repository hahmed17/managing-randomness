for /l %%i in (1, 1, 9) do (
    mkdir sample%%i
    cd sample%%i
    ..\..\bayesian ..\..\breast_cancer_data\breast-cancer-wisconsin-2.data train test ..\..\breast_cancer_data\breast-cancer-wisconsin.cfg 0 %%i
    cd ..
    timeout 5
)