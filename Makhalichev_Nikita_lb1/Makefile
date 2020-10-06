OBJ = main.o Workspace.o Recursion.o Test.o
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
Recursion.o: $(S)/Recursion.cpp $(H)/Recursion.h
	g++ -c $(S)/Recursion.cpp
Test.o: $(S)/Test.cpp $(H)/Test.h
	g++ -c $(S)/Test.cpp
run: a.out
	./$(NAME)
test: all
	./$(NAME) test
clear:
	rm -rf *.o $(NAME)
