for /l %%i in (1, 1, 9) do (
    cd train%%i
    awk /Accuracy/ out.txt >> ../accuracy.txt
    cd ..
)
cut -d " " -f 2- accuracy.txt > breast-tissue_exp8_accuracy.txt