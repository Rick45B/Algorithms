Test_util: Rick45Butil.o Test_util.o
	gcc -Wall -Wextra -Wconversion -g -o test_util Rick45Butil.o Test_util.o
Test_util.o: Test_util.c Rick45B-Utils.h
	gcc -Wall -Wextra -Wconversion -g -c Test_util.c
Rick45Butil.o: Rick45Butil.c Rick45B-Utils.h
	gcc -Wall -Wextra -Wconversion -g -c Rick45Butil.c
gdb: Rick45Butil.o Test_util.o
	gcc -Wall -Wextra -Wconversion -g -o util_temp Rick45Butil.o Test_util.o
