make greedy
echo ""
for ((i = 1; i <= $1; i++))
do
	echo "Grafo $i"
	echo "deu:"
	./greedy < ../inst/in/g$i.txt
	echo "sol:"
	cat ../inst/sol/g$i.txt
	echo ""
done
make clean
