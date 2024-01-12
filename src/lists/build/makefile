test_list: Rick45Blists.o Test_list.o Rick45Butil.o
	gcc -O3 -Wall -Wextra -Wconversion -std=c90 -ansi -g -o test_list Rick45Blists.o Test_list.o Rick45Butil.o
Test_list.o: Test_list.c Rick45B-AlgorithmsADT.h
	gcc -O3 -Wall -Wextra -Wconversion -std=c90 -ansi -g -c Test_list.c
Rick45Blists.o: Rick45Blists.c Rick45B-AlgorithmsADT.h
	gcc -O3 -Wall -Wextra -Wconversion -std=c90 -ansi -g -c Rick45Blists.c
gdb: Rick45Blists.o Test_list.o
	gcc -O3 -Wall -Wextra -Wconversion -std=c90 -ansi -g -o test_list_temp Rick45Blists.o Test_list.o
