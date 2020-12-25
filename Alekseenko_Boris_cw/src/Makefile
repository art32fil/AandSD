
OBJ = main.o
NAME = a.out


all: a.out
a.out: $(OBJ)
	g++ $(OBJ) -o $(NAME)
main.o: main.cpp AVL_tree.h
	g++ -c main.cpp
leaks: a.out
	valgrind --leak-check=full --log-file=leaks-out.txt ./$(NAME)
