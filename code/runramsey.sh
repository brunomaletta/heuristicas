make ramsey
echo ""
for ((i = 1; i <= $1; i++))
do
	echo "Grafo $i"
	echo "deu:"
	./ramsey < ../inst/in/g$i.txt
	echo "sol:"
	cat ../inst/sol/g$i.txt
	echo ""
done
make clean
