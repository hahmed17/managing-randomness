for /l %%i in (1, 1, 100) do (
    mkdir sample%%i
    cd sample%%i
     ..\..\neural-net.exe ..\..\data\breast-cancer-wisconsin.csv .3 .7
    cd ..
    timeout 3
)