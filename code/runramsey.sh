make ramsey
for file in ../inst/stole/*
do
	start=`date +%s%N`
	./ramsey < $file
	end=`date +%s%N`
	echo `expr $end - $start`
done
make clean
