OBJ = main.o binTree.o arm.o node.o treeWork.o
NAME = a.out

all: a.out

a.out: $(OBJ)
	g++ $(OBJ) -o $(NAME)
main.O: main.cpp treeWork.h
	g++ -c main.cpp
arm.o: arm.h arm.cpp
	g++ -c arm.cpp
binTree.o: binTree.cpp binTree.h arm.h
	g++ -c binTree.cpp
node.o: node.h node.cpp
	g++ -c node.cpp
treeWork.o: treeWork.cpp treeWork.h binTree.h
	g++ -c treeWork.cpp
clean:
	rm -rf *.o $(NAME)
