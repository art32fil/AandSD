OBJ = main.o Workspace.o Node.o Test.o
NAME = a.out
H = Headers
S = Sources

all: a.out
a.out: $(OBJ)
	g++ $(OBJ) -o $(NAME)
main.o: $(S)/main.cpp $(H)/Workspace.h
	g++ -c $(S)/main.cpp
Workspace.o: $(S)/Workspace.cpp $(H)/Workspace.h
	g++ -c $(S)/Workspace.cpp
Node.o: $(S)/Node.cpp $(H)/Node.h
	g++ -c $(S)/Node.cpp
Test.o: $(S)/Test.cpp $(H)/Test.h
	g++ -c $(S)/Test.cpp
run: a.out
	./$(NAME)
test: all
	./$(NAME) test
clear:
	rm -rf *.o $(NAME)
