make floyd
for file in ../inst/stole/*
do
	start=`date +%s%N`
	./floyd < $file
	end=`date +%s%N`
	echo `expr $end - $start`
done
make clean
