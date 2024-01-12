treesTest: Rick45Btrees.o treesTest.o Rick45Butil.o
	gcc -O3 -Wall -Wextra -Wconversion -std=c90 -ansi -g -o treesTest Rick45Btrees.o treesTest.o Rick45Butil.o
treesTest.o: treesTest.c Rick45B-AlgorithmsADT.h
	gcc -O3 -Wall -Wextra -Wconversion -std=c90 -ansi -g -c treesTest.c
Rick45Blists.o: Rick45Btrees.c Rick45B-AlgorithmsADT.h
	gcc -O3 -Wall -Wextra -Wconversion -std=c90 -ansi -g -c Rick45Btrees.c
gdb: Rick45Btrees.o treesTest.o
	gcc -O3 -Wall -Wextra -Wconversion -std=c90 -ansi -g -o treesTest_debug Rick45Btrees.o treesTest.o
