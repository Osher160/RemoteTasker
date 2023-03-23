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

    std::ifstream file = FindFile(argv[1]);
    int to_output = 0;
    
    std::ofstream test_file("test_file");

    while(file)
    {
        to_output = file.get();
        test_file << to_output;
    }

    return 0;
}