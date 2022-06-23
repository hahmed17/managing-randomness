for /l %%i in (1, 1, 9) do (
    mkdir sample%%i
    cd sample%%i
     ..\..\Source.exe %%i
    cd ..
)