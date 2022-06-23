for /l %%i in (1, 1, 100) do (
    cd sample%%i
    awk /before/ out.txt >> ../accuracy.txt
    cd ..
)
cut -d " " -f 4- accuracy.txt > heart_before_learning_accuracy.txt