output: main.o laby.o
	gcc -o main laby.o main.o -lm -lncurses
main.o: main.c
	gcc -c main.c
laby.o: laby.c
	gcc -c laby.c
clean:
	rm *.o main