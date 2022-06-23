for /l %%i in (1, 1, 9) do (
    cd train%%i
    awk /Accuracy/ out.txt >> ../accuracy.txt
    cd ..
)
cut -d " " -f 2- accuracy.txt > wbc_clusters2_accuracy.txt