all:
	gcc -o normal normal-copy.c
	gcc -o zero zero-copy.c

normal:
	gcc -o normal normal-copy.c

zero: 
	gcc -o zero zero-copy.c

clean:
	rm zero normal
