default: all

all: drops_demo

drops_demo:  main.o drops.o get_rand.o
	gcc -lncurses main.o get_rand.o drops.o  -o $@

main.o: main.c drops.h
	gcc main.c -c -o $@

drops.o: drops.c drops.h get_rand.h
	gcc drops.c -c -o $@

get_rand.o: get_rand.c get_rand.h
	gcc get_rand.c -c -o $@

clean:
	rm *.o
