all: main.o
	gcc -o EXEC/join main.o

main.o: FILES/CODE/main.c 
	gcc -c FILES/CODE/main.c

clean:
	rm *.o
