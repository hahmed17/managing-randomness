for /l %%i in (1, 1, 100) do (
    mkdir sample%%i
    cd sample%%i
     ..\..\kmeans.exe
    cd ..
    timeout 5
)