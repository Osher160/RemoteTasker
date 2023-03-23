#include <iostream>

#include "file_finder.hpp"

using namespace remote_tasker;

int main(int argc, const char **argv)
{
    if(argc < 2)
    {
        std::cout << "file finder <file_name>" << std::endl;
        exit(-1);
    }

    std::ifstream file = FindFile(argv[1], "/home/");

    
    std::ofstream test_file(argv[1]);

    while(!file.eof())
    {
        test_file.put(file.get());
    }

    test_file.close();

    return 0;
}