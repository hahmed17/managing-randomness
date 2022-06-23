for /l %%i in (1, 1, 9) do (
    cd train%%i
    awk /Accuracy/ out.txt >> ../accuracy.txt
    cd ..
)
cut -d " " -f 2- accuracy.txt > breast_tissue_exp6_accuracy.txt