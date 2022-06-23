for /l %%i in (2, 1, 6) do (
    mkdir clusters-%%i
    cd clusters-%%i
    for /l %%j in (1, 1, 9) do (
        mkdir train%%j
        cd train%%j
        ..\..\..\kmeans.exe %%j %%i
        cd ..
    )
    cd..
)