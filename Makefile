CC = g++
CFLAGS = -I.
DEPS =  world.h main.h 
OBJ = $(DEPS:.h=.o)

%.o: %.cpp
	$(CC) -c -g -o $@ $< $(CFLAGS)

install: $(OBJ)
	$(CC) -o m $^ -std=c++11 -lm -g


clean:
	rm *.o m
