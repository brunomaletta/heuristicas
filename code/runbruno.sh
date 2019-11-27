make bruno
for file in ../inst/stole/*
do
	start=`date +%s%N`
	./bruno < $file
	end=`date +%s%N`
	echo `expr $end - $start`
done
make clean
