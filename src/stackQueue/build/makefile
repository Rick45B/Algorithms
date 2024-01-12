stackQueueTest: Rick45BstackQueue.o stackQueueTest.o Rick45Butil.o
	gcc -O3 -Wall -Wextra -Wconversion -std=c90 -ansi -g -o stackQueueTest Rick45BstackQueue.o stackQueueTest.o Rick45Butil.o Rick45Blists.o
stackQueueTest.o: stackQueueTest.c Rick45B-AlgorithmsADT.h
	gcc -O3 -Wall -Wextra -Wconversion -std=c90 -ansi -g -c stackQueueTest.c
Rick45BstackQueue.o: Rick45BstackQueue.c Rick45B-AlgorithmsADT.h
	gcc -O3 -Wall -Wextra -Wconversion -std=c90 -ansi -g -c Rick45BstackQueue.c
gdb: Rick45BstackQueue.o stackQueueTest.o
	gcc -O3 -Wall -Wextra -Wconversion -std=c90 -ansi -g -o stackQueueTest_debug Rick45BstackQueue.o stackQueueTest.o
