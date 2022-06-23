for /l %%i in (1, 1, 100) do (
    mkdir sample%%i
    cd sample%%i
     ..\..\Source.exe 3
    cd ..
    timeout 5
)