for /l %%i in (1, 1, 100) do (
    mkdir sample%%i
    cd sample%%i
    ..\..\bayesian ..\..\happiness_data\SomervilleHappiness.txt train test ..\..\happiness_data\happiness.cfg 0
    cd ..
    timeout 5
)