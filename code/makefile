constr = construtivas
meta = meta
aux = aux

all:
	aux/runall.sh

brute:
	g++ -std=c++11 -O3 $(aux)/brute.cpp
	make run

greedy:
	g++ -std=c++11 -O3 $(constr)/greedy.cpp
	make run

match:
	g++ -std=c++11 -O3 $(constr)/match.cpp
	make run

floyd:
	g++ -std=c++11 -O3 $(constr)/floyd.cpp
	make run

ramsey:
	g++ -std=c++11 -O3 $(constr)/ramsey.cpp
	make run

bruno:
	g++ -std=c++11 -O3 $(meta)/bruno.cpp
	make run

bonito:
	g++ -std=c++11 -O3 $(meta)/bonito.cpp
	make run

ils:
	g++ -std=c++11 -O3 $(meta)/ils.cpp
	make run

reads:
	g++ -std=c++11 -o reads $(aux)/reads.cpp

run:
	$(aux)/run.sh

clean:
	rm -rf a.out reads
