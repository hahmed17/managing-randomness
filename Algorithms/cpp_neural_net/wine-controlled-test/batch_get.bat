for /l %%i in (1, 1, 100) do (
    cd sample%%i
    awk /accuracy/ out.txt >> ../accuracy.txt
    cd ..
)
cut -d " " -f 13- accuracy.txt > wine_controlled_test_accuracy.txt