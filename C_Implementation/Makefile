output: main.o utilities.o kmeans.o
	gcc -o output main.o utilities.o kmeans.o -lm

main.o: kmeans.h utilities.h
	gcc -c main.c

kmeans.o: kmeans.h utilities.h
	gcc -c kmeans.c

utilities.o: utilities.h
	gcc -c utilities.c

clean: 
	rm *.o output