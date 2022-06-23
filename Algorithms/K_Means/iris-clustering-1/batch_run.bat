for /l %%i in (2, 1, 6) do (
    mkdir clusters-%%i
    cd clusters-%%i
    for /l %%j in (1, 1, 100) do (
        mkdir sample%%j
        cd sample%%j
        ..\..\..\kmeans.exe 3 %%i
        cd ..
	timeout 5
    )
    cd ..
)