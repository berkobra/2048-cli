CC := g++
BUILDDIR := build

CFLAGS := -Wall -pedantic -pedantic-errors

2048-cli: controller.cpp game.cpp main.cpp grid.cpp node.cpp view.cpp
	$(CC) $(CFLAGS) controller.cpp game.cpp main.cpp grid.cpp node.cpp view.cpp -o 2048-cli

clean:
	@echo " Cleaning...";
	rm grid_test 2048-cli

# Tests
grid_test: grid_test.cpp grid.cpp node.cpp
	$(CC) $(CFLAGS) -DDEBUG grid_test.cpp grid.cpp node.cpp -o grid_test

.PHONY: clean
