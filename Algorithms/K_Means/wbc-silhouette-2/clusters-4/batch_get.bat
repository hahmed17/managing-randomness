for /l %%i in (1, 1, 100) do (
    cd sample%%i
    awk /Accuracy/ out.txt >> ../accuracy.txt
    cd ..
)
cut -d " " -f 2- accuracy.txt > wbc_clusters4_accuracy.txt