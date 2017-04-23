#
# Makefile for Binary Search Tree
# Minor edit by Ben Tanen to include a 'make test' option
#
CXX = clang++
FLAGS =  -g -Wall 

bst: BinarySearchTree.cpp BinarySearchTree.h main.cpp pretty_print.cpp
	${CXX} ${FLAGS} -o hw4 BinarySearchTree.cpp \
		main.cpp pretty_print.cpp

test: BinarySearchTree.cpp BinarySearchTree.h main_test.cpp pretty_print.cpp
	${CXX} ${FLAGS} -o hw4 BinarySearchTree.cpp \
		main_test.cpp pretty_print.cpp

clean:
	rm -f hw4

provide:
	provide comp15 hw4 main.cpp BinarySearchTree.cpp BinarySearchTree.h \
	        pretty_print.cpp ReadMe.md Makefile

