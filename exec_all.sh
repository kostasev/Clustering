#!/bin/sh
mkdir ./out
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 0 -U 0 -k 2 > ./out/000_2.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 0 -U 0 -k 5 > ./out/000_5.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 0 -U 0 -k 10 > ./out/000_10.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 0 -U 0 -k 25 > ./out/000_25.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 0 -U 0 -k 50 > ./out/000_50.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 0 -U 0 -k 100 > ./out/000_100.txt

