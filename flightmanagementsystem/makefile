out: main.o functions.o
	gcc -o out main.o functions.o
main.o: main.c
	gcc -c main.c
function.o: functions.c
	gcc -c functions.c
clean:
	rm -f main.o functions.o
