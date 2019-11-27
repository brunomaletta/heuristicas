for file in ../inst/stole/*
do
	start=`date +%s%N`
	./a.out < $file
	end=`date +%s%N`
	echo `expr $end - $start`
done
make clean
