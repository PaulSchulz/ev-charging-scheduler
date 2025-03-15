.PHONY: all clean

all: dining \
	scheduler

dining: dining.c
	gcc -o dining dining.c

scheduler: main.cpp scheduler.cpp development.cpp
	g++ -o scheduler main.cpp scheduler.cpp development.cpp

clean:
	rm dining scheduler
