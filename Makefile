all: sort_join.o main.o relation.o tuple.o list.o CuTest.o unitest.o
	gcc -o EXEC/sort_join main.o sort_join.o tuple.o relation.o list.o CuTest.o unitest.o

main.o: FILES/CODE/main.c 
	gcc -c FILES/CODE/main.c

list.o: FILES/CODE/list.c
	gcc -c FILES/CODE/list.c

sort_join.o: FILES/CODE/sort_join.c
	gcc -c FILES/CODE/sort_join.c

tuple.o: FILES/CODE/tuple.c
	gcc -c FILES/CODE/tuple.c

relation.o: FILES/CODE/relation.c
	gcc -c FILES/CODE/relation.c

CuTest.o: FILES/CODE/CuTest.c
	gcc -c FILES/CODE/CuTest.c

unitest.o: FILES/CODE/unitest.c
	gcc -c FILES/CODE/unitest.c

clean:
	rm *.o
