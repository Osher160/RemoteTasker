CC = g++
CPPFLAGS = -std=c++17 -Wall -Wextra -g -pedantic-errors -I ./include



# test for reactor:
reactor : ./src/reactor.cpp ./src/utility.cpp ./tests/reactor_test.cpp
	$(CC) $(CPPFLAGS) ./src/reactor.cpp ./src/utility.cpp ./tests/reactor_test.cpp -o $@

# test for file_finder:

file_finder : ./src/file_finder.cpp ./src/utility.cpp ./tests/file_finder_test.cpp
	$(CC) $(CPPFLAGS) ./src/file_finder.cpp ./src/utility.cpp ./tests/file_finder_test.cpp -o $@

main : ./src/file_finder.cpp ./src/search_manager.cpp ./src/reactor.cpp ./src/utility.cpp ./main/main.cpp
	$(CC) $(CPPFLAGS) $^
%.cpp :
