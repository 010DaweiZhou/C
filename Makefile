# all : 11.c 11_1.c
	# gcc 11.c 11_1.c -o all
	
all : 11.o 11_1.o
	gcc -o all 11.o 11_1.o
	
11.o : 11.c generic.h
	gcc -c 11.c
	
11_1.o : 11_1.c 11_1.h
	gcc -c 11_1.c

.PHONY: clean	
clean :
	rm -r all *.o