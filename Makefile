CC = g++
CFLAGS = -I.
DEPS =  geometrics.h
OBJ = $(DEPS:.h=.o)

%.o: %.cpp
	$(CC) -c -g -o $@ $< $(CFLAGS)

install: $(OBJ)
	$(CC) -o p parser.cpp $^ -std=c++11 -lm -g


clean:
	rm *.o m
