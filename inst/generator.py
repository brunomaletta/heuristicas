import networkx as nx
import random as rd

for k in range(10):
	G = nx.gnp_random_graph(20, rd.random())
	
	m = 0
	for i in G:
		m += len(G[i])
	m = m//2

	f = open("in/g" + str(k+3) + ".txt", "w")
	print("in/g" + str(k+3) + ".txt")

	f.write(str(20) + " " + str(m) + "\n")
	for i in G:
		for j in G[i]:
			if i < j:
				f.write(str(i) + " " + str(j) + "\n")
