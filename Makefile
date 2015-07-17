CC = g++
CFLAGS = -I. -O2
DEPS =  geometrics.h world.h obj_file.h main.h triangle.h rectangle.h polygon.h 
OBJ = $(DEPS:.h=.o)

%.o: %.cpp
	$(CC) -c -g -o $@ $< $(CFLAGS) -std=c++11

install: $(OBJ)
	$(CC) -o m $^ -std=c++11 -lm -g -pthread


clean:
	rm -f *.o m
