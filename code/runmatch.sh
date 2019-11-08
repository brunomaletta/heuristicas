make match
for file in ../inst/stole/*
do
	start=`date +%s%N`
	./match < $file
	end=`date +%s%N`
	echo `expr $end - $start`
done
make clean
