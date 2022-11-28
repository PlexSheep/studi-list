.PHONY = all pre testfiles bigfiles
SOURCES = $(wildcard *.c)
BINARIES = $(SOURCES:%.c=%)
EXECUTABLES= $(addprefix bin/,${BINARIES})
all: bin/studentList

pre:
		@mkdir -p bin obj

clean:
		rm -rvf bin obj

bin/studentList:
