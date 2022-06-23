for /l %%i in (1, 1, 9) do (
    mkdir train%%i
    cd train%%i
    ..\..\..\kmeans.exe %%i
    cd ..
)