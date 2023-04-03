#include <iostream>
#include <memory>

#include "utility.hpp"
#include "file_finder.hpp"
#include "reactor.hpp"
#include "search_manager.hpp"
#include "connector.hpp"
#include "remote_tasker.hpp"

void Activate();
void RunThisComputerSearch();

int main()
{

    Activate();

    return 0;

}

void Activate()
{
    using namespace remote_tasker;

    std::cout << "Welcome to Remote Tasker," <<
    " In this application you can send and receive files directly through your WIFI." 
    << std::endl;

    std::cout << "If you want to search files in this computer, Please press 0"
    << "if you want to search in another computer, please press 1" << std::endl;
    
    bool is_true;
    std::cin >> is_true;

    std::cout << "Enter the directory name for copying the files into:" << std::endl;

    std::string to_search_manager;
    std::cin >> to_search_manager;

    std::shared_ptr<SearchManager> searchNcopy(new SearchManager(to_search_manager));
    std::shared_ptr<Reactor> reactor(new Reactor());

    RemoteTasker remote_tasker(reactor,searchNcopy);

    if(is_true)
    {
        remote_tasker.RunAll();
    }

    else
    {
        remote_tasker.RunOnlyThisComputer();
    }
}