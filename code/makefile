constr = construtivas
meta = meta
aux = aux

all:
	aux/runall.sh

brute:
	g++ -std=c++11 $(aux)/brute.cpp
	make run

greedy:
	g++ -std=c++11 $(constr)/greedy.cpp
	make run

match:
	g++ -std=c++11 $(constr)/match.cpp
	make run

floyd:
	g++ -std=c++11 $(constr)/floyd.cpp
	make run

ramsey:
	g++ -std=c++11 $(constr)/ramsey.cpp
	make run

bruno:
	g++ -std=c++11 $(meta)/bruno.cpp
	make run

reads:
	g++ -std=c++11 -o reads $(aux)/reads.cpp

run:
	$(aux)/run.sh

clean:
	rm -rf a.out reads
