.PHONY: all clean

all: dining \
	scheduler \
	scheduler-simple

dining: dining.c
	gcc -o dining dining.c

scheduler: main.cpp scheduler.cpp development.cpp
	g++ -o scheduler main.cpp scheduler.cpp development.cpp

scheduler-simple: main.cpp scheduler-simple.cpp development.cpp
	g++ -o scheduler-simple main.cpp scheduler-simple.cpp development.cpp

clean:
	rm dining scheduler
