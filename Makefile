CC = g++
CFLAGS = -I.
DEPS =  geometrics.h world.h obj_file.h main.h triangle.h rectangle.h polygon.h 
OBJ = $(DEPS:.h=.o)

%.o: %.cpp
	$(CC) -c -g -o $@ $< $(CFLAGS)

install: $(OBJ)
	$(CC) -o m $^ -std=c++11 -lm -g


clean:
	rm *.o m
