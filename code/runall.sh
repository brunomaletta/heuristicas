make reads

echo "Greedy"
./rungreedy.sh | ./reads

echo "Match"
./runmatch.sh | ./reads

echo "Ramsey"
./runramsey.sh | ./reads

echo "Floyd"
./runfloyd.sh | ./reads
