for /l %%i in (1, 1, 100) do (
    cd sample%%i
    type seedFile.txt >> ../seeds.txt
    echo. >> ../seeds.txt
    cd ..
)