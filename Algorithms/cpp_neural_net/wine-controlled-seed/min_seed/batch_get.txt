for /l %%i in (1, 1, 9) do (
    cd train%%i
    awk /accuracy/ out.txt >> ../accuracy.txt
    cd ..
)
cut -d " " -f 13- accuracy.txt > wine_min_accuracy.txt