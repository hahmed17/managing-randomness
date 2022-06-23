for /l %%i in (1, 1, 9) do (
    cd sample%%i
    awk /Accuracy/ out.txt >> ../accuracy.txt
    cd ..
)
cut -d " " -f 3- accuracy.txt > happiness_exp8_accuracy.txt