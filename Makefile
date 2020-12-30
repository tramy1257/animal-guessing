compile: animal_main.cpp ./animal_tree/animal_tree.cpp
	clang++ -Wall -std=c++11 animal_main.cpp ./animal_tree/animal_tree.cpp -o animal-guessing

all: compile

clean: 
	rm ./animal-guessing
