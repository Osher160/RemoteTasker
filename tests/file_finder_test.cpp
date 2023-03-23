#include <iostream>

#include "file_finder.hpp"

int main(int argc, const char *argv)
{
    if(argc < 2)
    {
        std::cout << "file finder <file_name>" std::endl;
        exit(-1);
    }

    std::ofstream stream = FileFind(argv[1]);

    return 0;
}