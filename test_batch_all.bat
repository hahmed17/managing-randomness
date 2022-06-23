set algs_list=neural-net k-means
set datasets_list=heart-disease iris wine wisconsin-breast-cancer somerville-happiness breast-tissue

for %%a in (%algs_list%) do (
	for %%d in (%datasets_list%) do (
		if %%a==k-means ( 
			call batch_run_all.bat %%a %%d 100 .3 .7 3
		) else (
			call batch_run_all.bat %%a %%d 100 .3 .7
		)
	)
)