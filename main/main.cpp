#include <iostream>

#include "file_finder.hpp"
#include "reactor.hpp"
#include "search_manager.hpp"

void RunAll();

int main()
{
    std::cout << "Hi, Welcome to Remote Tasker," <<
    "In this application you can send and receive files in your Intranet" 
    << std::endl;


    RunAll();


}


void OnEvent(remote_tasker::SearchManager &)
{

}

void RunAll()
{
    using namespace remote_tasker;
 
    std::cout << "enter your received directory name:" << std::endl;

    std::string to_search_manager;

    std::cin >> to_search_manager;

    SearchManager searchNcopy(to_search_manager);

    Reactor reactor;

    reactor.Add((std::bind(OnEvent,searchNcopy)),0,Reactor::Mode::READ);   

    reactor.Run();
}