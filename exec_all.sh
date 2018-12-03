#!/bin/sh
echo "Run 001"
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 0 -U 1 -k 2 > ./out/001_2.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 0 -U 1 -k 5 > ./out/001_5.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 0 -U 1 -k 10 > ./out/001_10.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 0 -U 1 -k 25 > ./out/001_25.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 0 -U 1 -k 50 > ./out/001_50.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 0 -U 1 -k 100 > ./out/001_100.txt
echo "Run 010"
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 1 -U 0 -k 2 > ./out/010_2.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 1 -U 0 -k 5 > ./out/010_5.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 1 -U 0 -k 10 > ./out/010_10.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 1 -U 0 -k 25 > ./out/010_25.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 1 -U 0 -k 50 > ./out/010_50.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 1 -U 0 -k 100 > ./out/010_100.txt

echo "Run 011"
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 1 -U 1 -k 2 > ./out/011_2.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 1 -U 1 -k 5 > ./out/011_5.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 1 -U 1 -k 10 > ./out/011_10.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 1 -U 1 -k 25 > ./out/011_25.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 1 -U 1 -k 50 > ./out/011_50.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 0 -I 1 -U 1 -k 100 > ./out/011_100.txt

echo "Run 100"
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 0 -U 0 -k 2 > ./out/100_2.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 0 -U 0 -k 5 > ./out/100_5.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 0 -U 0 -k 10 > ./out/100_10.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 0 -U 0 -k 25 > ./out/100_25.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 0 -U 0 -k 50 > ./out/100_50.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 0 -U 0 -k 100 > ./out/100_100.txt
echo "Run 101"
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 0 -U 1 -k 2 > ./out/101_2.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 0 -U 1 -k 5 > ./out/101_5.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 0 -U 1 -k 10 > ./out/101_10.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 0 -U 1 -k 25 > ./out/101_25.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 0 -U 1 -k 50 > ./out/101_50.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 0 -U 1 -k 100 > ./out/101_100.txt
echo "Run 110"
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 1 -U 0 -k 2 > ./out/110_2.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 1 -U 0 -k 5 > ./out/110_5.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 1 -U 0 -k 10 > ./out/110_10.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 1 -U 0 -k 25 > ./out/110_25.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 1 -U 0 -k 50 > ./out/110_50.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 1 -U 0 -k 100 > ./out/110_100.txt
echo "Run 111"
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 1 -U 1 -k 2 > ./out/111_2.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 1 -U 1 -k 5 > ./out/111_5.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 1 -U 1 -k 10 > ./out/111_10.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 1 -U 1 -k 25 > ./out/111_25.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 1 -U 1 -k 50 > ./out/111_50.txt
./cluster -i data_files/in.csv -c cluster.conf -d euclidean -A 1 -I 1 -U 1 -k 100 > ./out/111_100.txt
