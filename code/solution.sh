make brute
for i in {1..2}
do
	./brute < ../inst/in/g$i.txt > ../inst/sol/g$i.txt
done
make clean
