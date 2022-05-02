output: main.o 
	gcc  main.o -o bhta
main.o: main.c
	gcc -c main.c
debug:
	gcc -g main.o 
clean:
	rm bhta *.o