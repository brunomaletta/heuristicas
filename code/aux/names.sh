for file in ../inst/stole/*
do
  name=$(echo $file | cut -c 15-)
  echo $name
done
