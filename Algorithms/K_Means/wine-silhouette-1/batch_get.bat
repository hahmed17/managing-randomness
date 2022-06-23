for /l %%j in (1, 1, 9) do (
    for /l %%i in (2, 1, 6) do (
        awk 'NR==%%j' clusters-%%i\wine_clusters%%i_accuracy.txt >> "wine_ratio%%j_accuracy.txt"
        echo
    )
)