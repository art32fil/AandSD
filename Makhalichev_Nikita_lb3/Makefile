OBJ = main.o BinTree.o
NAME = a.out
H = Headers
S = Sources

all: a.out
a.out: $(OBJ)
	g++ $(OBJ) -o $(NAME)
main.o: $(S)/main.cpp $(H)/BinTree.h
	g++ -c $(S)/main.cpp
BinTree.o: $(S)/BinTree.cpp $(H)/BinTree.h
	g++ -c $(S)/BinTree.cpp
run: a.out
	./$(NAME)
test: all
	./$(NAME) test
leaks: a.out
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=leaks-out.txt ./$(NAME)
clear:
	rm -rf *.o $(NAME) leaks-out.txt output.txt
