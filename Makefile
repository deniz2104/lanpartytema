.phony: build run clear

build: test.o functii.o
	gcc -Wall -Werror -Wextra test.o functii.o -o lan-party-02-checker/lanParty -lm

test.o: test.c my_library.h
	gcc -Wall -Werror -Wextra -c test.c -o test.o -lm

functii.o: functii.c my_library.h
	gcc -Wall -Werror -Wextra -c functii.c -o functii.o -lm
	
run:
	./lanParty

clear:
	rm test