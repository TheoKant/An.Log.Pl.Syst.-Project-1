CPP=gcc

objects=main.o list.o 

SOURCE = main.c list.c 

HEADER = main.h list.h 

OUT = test

FLAGS = -g -c 

all : $(objects)
	$(CPP) -g $(objects) -o $(OUT) 

main.o: main.c
	$(CPP) $(FLAGS) main.c

list.o: list.c
	$(CPP) $(FLAGS) list.c


clean:

	rm test


