for /l %%i in (2, 1, 6) do (
    cd clusters-%%i
    for /l %%j in (1, 1, 100) do (
        cd sample%%j
        awk /Accuracy/ out.txt >> ../accuracy.txt
        cd ..
    )
    cut -d " " -f 2- accuracy.txt > ../happiness_clusters%%i_accuracy.txt
    cd..
)