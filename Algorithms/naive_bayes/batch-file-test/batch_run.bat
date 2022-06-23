@echo off
for /l %%i in (1, 1, 9) do (
    mkdir sample%%i
    cd sample%%i
    ..\..\bayesian ..\..\happiness_data\SomervilleHappiness.txt ..\..\happiness_data\happiness.cfg %%i 0
    cd ..
    timeout 3
)