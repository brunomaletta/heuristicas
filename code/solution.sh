make brute
for ((i = 1; i <= $1; i++))
do
	./brute < ../inst/in/g$i.txt > ../inst/sol/g$i.txt
done
make clean
