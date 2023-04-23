CC = g++
CPPFLAGS = -std=c++17 -Wall -Wextra -g -pedantic-errors -I ./include
PKG = 'pkg-config --cflags --libs gtk4'


# test for reactor:
reactor : ./src/reactor.cpp ./src/utility.cpp ./tests/reactor_test.cpp
	$(CC) $(CPPFLAGS) ./src/reactor.cpp ./src/utility.cpp ./tests/reactor_test.cpp -o $@

# test for file_finder:

file_finder : ./src/file_finder.cpp ./src/utility.cpp ./tests/file_finder_test.cpp
	$(CC) $(CPPFLAGS) ./src/file_finder.cpp ./src/utility.cpp ./tests/file_finder_test.cpp -o $@

connector: ./src/connector.cpp ./tests/connector_test.cpp ./src/utility.cpp
	$(CC) $(CPPFLAGS) $^ -o $@

graphic_main: ./gui/src/remote_n_local.cpp ./gui/src/remote.cpp ./gui/src/local.cpp ./src/search_manager.cpp ./src/file_finder.cpp 
	g++ $(CPPFLAGS) ./gui/src/remote_n_local.cpp ./gui/src/remote.cpp ./gui/src/local.cpp ./src/search_manager.cpp ./src/file_finder.cpp -I ./gui/include -I ./include $$(pkg-config --cflags gtkmm-4.0) $$(pkg-config --libs gtkmm-4.0)



main : ./src/file_finder.cpp ./src/remote_tasker.cpp ./src/connector.cpp ./src/search_manager.cpp ./src/reactor.cpp ./src/connector.cpp ./src/utility.cpp ./main/main.cpp
	$(CC) $(CPPFLAGS) $^ -o remote_tasker

%.cpp :
