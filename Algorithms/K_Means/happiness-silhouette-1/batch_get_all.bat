for /l %%n in (2, 1, 6) do (
    cd clusters-%%n
    for /l %%m in (1, 1, 9) do (
        cd train%%m
        awk /Accuracy/ out.txt >> ../accuracy.txt
        cd ..
    )
    cut -d " " -f 2- accuracy.txt > happiness_clusters%%n_accuracy.txt
    cd..
)

for /l %%j in (1, 1, 9) do (
    for /l %%i in (2, 1, 6) do (
        awk 'NR==%%j' clusters-%%i\happiness_clusters%%i_accuracy.txt >> "happiness_ratio%%j_accuracy.txt"
        echo
    )
)