for /l %%i in (1, 1, 9) do (
    cd sample%%i
    awk /accuracy/ out.txt >> ../accuracy.txt
    cd ..
)
cut -d " " -f 13- accuracy.txt > wine_exp7_accuracy.txt