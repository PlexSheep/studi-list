.PHONY = all clean
SOURCES = $(wildcard *.c)
BINARIES = $(SOURCES:%.c=%)
EXECUTABLES= $(addprefix bin/,${BINARIES})
all: pre bin/studentList

pre:
		@mkdir -p bin obj

clean:
		rm -rvf bin obj

bin/studentList:
		gcc main.c -g -o bin/studentList
