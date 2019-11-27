for i in ramsey greedy floyd match bruno
do
	echo "--> $i"
	make reads
	make $i | ./reads
done
