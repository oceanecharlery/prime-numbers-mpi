#/bin/bash
fichier="resultat.csv"
taille=(500 5000 50000 100000 250000 500000 1000000)
for t in "${taille[@]}":
do
	for i in {2..8};
	do
		gtime -f '%e' -o tmp.txt ./sequentiel 0 $t
		time=$(cat tmp.txt)
		echo -e "$t,1,$time,sequentiel" >> $fichier
		gtime -f '%e' -o tmp.txt mpirun --oversubscribe --quiet -n $i ./main 0 $t
		time=$(cat tmp.txt)
		echo -e "$t,$i,$time,parallele" >> $fichier
	done
done