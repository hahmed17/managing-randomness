for /l %%i in (1, 1, 100) do (
    cd sample%%i
    awk /Accuracy/ out.txt >> ../accuracy.txt
    cd ..
)
cut -d " " -f 3- accuracy.txt > bc_rand-data_accuracy.txt