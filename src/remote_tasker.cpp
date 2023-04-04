#include "remote_tasker.hpp"

using namespace remote_tasker;

RemoteTasker::RemoteTasker(std::shared_ptr<remote_tasker::Reactor> reactor,
std::shared_ptr<remote_tasker::SearchManager> search_manager)
: m_sock(nullptr),
  m_reactor(reactor),
  m_search_manager(search_manager)
{

}

void OnEventStdin(remote_tasker::SearchManager &search_m)
{
    std::string buff;

    std::cin >> buff;
    
    search_m.SearchNSendSameComputer(buff);
}

void RemoteTasker::RunOnlyThisComputer()
{
    m_reactor->Add((std::bind(OnEventStdin,*m_search_manager)),0,Reactor::Mode::READ);   

    std::cout << "when you need a file, enter its name.\n" <<
    "the program will search it for you and will send it to the directory you entered earlier." << std::endl;


    m_reactor->Run();
}

void RemoteTasker::RunAll()
{
    // TODO - REMOVE IN NEXT VERSIONS - check if server or client and create the one needed
    std::cout << "Is this computer server/client?" << std::endl;
    
    std::string is_server;
    std::cin >> is_server;

    // get ip(if not server), port and dir name
    std::cout << "Enter port:" << std::endl;
    int port;
    std::cin >> port;

    if(is_server == "server")
    {
        m_sock.reset(new ServerSocket);

        std::cout << "waiting for client to connect..." << std::endl;
        
        m_sock->Connect(port,"never mind");
        
        InitAndActivateReactor();
    }

    else
    {
        std::cout << "Please enter the ip address:" << std::endl;

        std::string ip;
        std::cin >> ip;

        m_sock.reset(new SocketClient);
        m_sock->Connect(port,ip);
        
        InitAndActivateReactor();
    }
}


void OnSearchingReq(std::shared_ptr<remote_tasker::SearchManager> search_m,
                             std::shared_ptr<remote_tasker::Socket> sock)
{
    std::vector<char> name = sock->Receive();

    search_m->SearchNSendNewComputer(name.data(),sock);
}

void OnEventSearch(std::shared_ptr<remote_tasker::SearchManager> search_m,
                                 std::shared_ptr<remote_tasker::Socket> sock)
{
    std::string name;
    std::cin >> name;

    std::vector<char> name_vec;

    std::copy(name.begin(),name.end(),std::back_inserter(name_vec));

    sock->Send(name_vec);

    // wait for the file and save it
    search_m->SaveFromOtherComputer(name,sock);
}


void RemoteTasker::InitAndActivateReactor()
{
    std::cout << "when you need a file, enter its name.\n" << std::endl;

    // to catch the searches from the other computer
    m_reactor->Add(std::bind(OnSearchingReq,m_search_manager,m_sock),m_sock->GetEndpoint(),Reactor::Mode::READ);
    
    // to catch the searches to the other computer
    m_reactor->Add((std::bind(OnEventSearch,m_search_manager,m_sock)),0,Reactor::Mode::READ);  

    m_reactor->Run();
}