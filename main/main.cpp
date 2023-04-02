#include <iostream>

#include "utility.hpp"
#include "file_finder.hpp"
#include "reactor.hpp"
#include "search_manager.hpp"
#include "connector.hpp"

void RunAll();
void RunThisComputerSearch();

int main()
{
    std::cout << "Welcome to Remote Tasker," <<
    " In this application you can send and receive files directly through your WIFI." 
    << std::endl;

    std::cout << "If you want to search files in this computer, Please press 0"
    << "if you want to search in another computer, please press 1" << std::endl;

    bool is_true;
    std::cin >> is_true;

    if(is_true)
    {
        RunAll();
    }

    else
    {
        RunThisComputerSearch();
    }
}


void OnEventStdinAnotherCom(remote_tasker::SearchManager &search_m, remote_tasker::Socket *sock)
{
    std::string buff;

    std::cin >> buff;
    
    search_m.SearchNSendNewComputer(buff,sock);
}


void OnSearchingReq(remote_tasker::SearchManager &search_m, remote_tasker::Socket *sock)
{
    std::vector<char> name = sock->Receive();

    search_m.SearchNSendNewComputer(name.data(),sock);
}

void OnEventSearch(remote_tasker::SearchManager &search_m, remote_tasker::Socket *sock)
{
    std::string name;
    std::cin >> name;

    std::vector<char> name_vec;

    std::copy(name.begin(),name.end(),name_vec);

    sock->Send(name_vec);
}

void InitAndActivateReactor(remote_tasker::Reactor &reactor,
remote_tasker::SearchManager &search_m, remote_tasker::Socket *sock)
{
    using namespace remote_tasker;

    std::cout << "when you need a file, enter its name.\n" << std::endl;

    // to catch the searches from the other computer
    reactor.Add(std::bind(OnSearchingReq,search_m,sock),sock->GetEndpoint(),Reactor::Mode::READ);
    
    // to catch the searches to the other computer
    reactor.Add((std::bind(OnEventSearch,search_m,sock)),0,Reactor::Mode::READ);  

    reactor.Run();
}

void RunAll()
{
    using namespace remote_tasker;

// TODO - REMOVE IN NEXT VERSIONS - check if server or client and create the one needed
    std::cout << "Are this computer is server/client?" << std::endl;
    
    std::string is_server;
    std::cin >> is_server;

// get ip(if not server), port and dir name
    std::cout << "Enter port:" << std::endl;
    int port;
    std::cin >> port;

    std::cout << "Enter the directory name for copying the files into:" << std::endl;

    std::string to_search_manager;
    std::cin >> to_search_manager;

    SearchManager searchNcopy(to_search_manager);
    Reactor reactor;

// sign up to the reactor with the socket.
// run the reactor

    if(is_server == "server")
    {
        ServerSocket sock;

        std::cout << "waiting for client to connect..." << std::endl;
        
        sock.openServer(port);
        
        std::cout << "when you need a file, enter its name.\n" << std::endl;
        
        InitAndActivateReactor(reactor,searchNcopy,&sock);
    }

    else
    {
        std::cout << "Please enter the ip address:" << std::endl;

        std::string ip;
        std::cin >> ip;

        SocketClient sock;

        sock.ConnectToServer(port,ip);
        
        InitAndActivateReactor(reactor,searchNcopy,&sock);
    }
}

void OnEventStdin(remote_tasker::SearchManager &search_m)
{
    std::string buff;

    std::cin >> buff;
    
    search_m.SearchNSendSameComputer(buff);
}

void RunThisComputerSearch()
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