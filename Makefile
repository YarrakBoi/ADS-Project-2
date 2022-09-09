dict1: test.o dictionary.o list.o
	gcc -o dict1 test.o dictionary.o list.o -g -Wall

dict2: test.o dictionary.o list.o array.o
	gcc -o dict1 test.o dictionary.o list.o array.o -g -Wall

dict3: test2.o dictionary.o datapoint.o quadtree.o list.o
	gcc -o dict3 test2.o dictionary.o datapoint.o quadtree.o list.o -g -Wall

test.o: test.c
	gcc -c test.c -g -Wall 

test2.o: test2.c
	gcc -c test2.c -g -Wall

dictionary.o: dictionary.c dictionary.h
	gcc -c dictionary.c -g -Wall

list.o: list.c list.h
	gcc -c list.c -g -Wall

datapoint.o: datapoint.c datapoint.h
	gcc -c datapoint.c -g -Wall

quadtree.o: quadtree.c quadtree.h
	gcc -c quadtree.c -g -Wall



