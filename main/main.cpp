#include <iostream>

#include <unistd.h> // read

#include "utility.hpp"
#include "file_finder.hpp"
#include "reactor.hpp"
#include "search_manager.hpp"

void RunAll();

int main()
{
    std::cout << "Welcome to Remote Tasker," <<
    " In this application you can send and receive files in your Intranet." 
    << std::endl;


    RunAll();


}


void OnEventStdin(remote_tasker::SearchManager &search_m)
{
    // hardcoded for now
    std::string buff;

    std::cin >> buff;
    
    search_m.SearchNSendSameComputer(buff);
}

void RunAll()
{
    using namespace remote_tasker;
 
    std::cout << "Enter the directory name for copying the files into:" << std::endl;

    std::string to_search_manager;

    std::cin >> to_search_manager;

    SearchManager searchNcopy(to_search_manager);

    Reactor reactor;

    reactor.Add((std::bind(OnEventStdin,searchNcopy)),0,Reactor::Mode::READ);   

    std::cout << "when you need a file, enter its name.\n" <<
    "the program will search it for you and will send it to the directory you entered earlier." << std::endl;


    reactor.Run();
}