all: executavel

executavel: main.o jogovoraz.o
	gcc -o executavel main.o jogovoraz.o

main.o: main.c jogovoraz.h
	gcc -o main.o -c main.c -Wall -Werror

jogovoraz.o: jogovoraz.c jogovoraz.h
	gcc -o jogovoraz.o -c jogovoraz.c -Wall -Werror

clean:
	rm -rf *.o executavel 

run:
	./executavel