for /l %%i in (4, 1, 6) do (
    mkdir clusters-%%i
    cd clusters-%%i
    for /l %%j in (1, 1, 100) do (
        mkdir sample%%j
        cd sample%%j
        ..\..\..\kmeans.exe 3 %%i
        cd ..
        timeout 3
    )
    cd ..
)