.POSIX:
.SUFFIXES:
CC	= gcc
CFLAGS	= -O2 -fno-common -fno-omit-frame-pointer -fPIE -fstack-check -fstack-protector-strong -funsigned-char -mfunction-return=thunk -mindirect-branch=thunk -Wall -Wbad-function-cast -Wcast-align -Wcast-qual -Wconversion -Wextra -Wformat=2 -Wformat-nonliteral -Wformat-security -Winline -Wmissing-declarations -Wmissing-format-attribute -Wmissing-prototypes -Wpedantic -Wpointer-arith -Wsign-conversion -Wstrict-overflow -Wstrict-prototypes -Wtrampolines -Wwrite-strings 
LDFLAGS	= -lm -Wl,-z,nodlopen -Wl,-z,nodump -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now

all: ../bin/duplicates
../bin/duplicates: ../obj/compare.o ../obj/duplicates.o ../obj/error.o ../obj/input.o ../obj/main.o ../obj/memory.o ../obj/sort.o
	$(CC) $(LDFLAGS) -o duplicates ../obj/compare.o ../obj/duplicates.o \
		../obj/error.o ../obj/input.o ../obj/main.o ../obj/memory.o \
		../obj/sort.o $(LDLIBS); mv duplicates ../bin
../obj/compare.o: compare.c ../include/compare.h
	$(CC) $(CFLAGS) -o compare.o -c compare.c; mv *.o ../obj
../obj/duplicates.o: duplicates.c ../include/duplicates.h
	$(CC) $(CFLAGS) -o duplicates.o -c duplicates.c
../obj/error.o: error.c ../include/error.h; mv *.o ../obj
	$(CC) $(CFLAGS) -o error.o -c error.c
../obj/input.o: input.c ../include/input.h; mv *.o ../obj
	$(CC) $(CFLAGS) -o input.o -c input.c; mv *.o ../obj
../obj/main.o: main.c ../include/include.h ../include/config.h
	$(CC) $(CFLAGS) -o main.o -c main.c; mv *.o ../obj
../obj/memory.o: memory.c ../include/memory.h
	$(CC) $(CFLAGS) -o memory.o -c memory.c; mv *.o ../obj
../obj/sort.o: sort.c ../include/sort.h
	$(CC) $(CFLAGS) -o sort.o -c sort.c; mv *.o ../obj
clean:
	rm -f ../bin/duplicates ../obj/*.o
