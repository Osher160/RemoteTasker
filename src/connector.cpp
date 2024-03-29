

#ifdef __linux__
#include <unistd.h> // read 

#include <sys/types.h>

#include <arpa/inet.h> // inet_addr 

#include <sys/socket.h> // sockets 
#include <netinet/in.h> // sockaddr_in 


#elif _WIN32

#endif

#include "connector.hpp"
#include "utility.hpp"


using namespace remote_tasker;

void ServerSocket::openServer(int port)
{
    // init new listening socket. TODO - another function that support more clients
    int sock = socket(AF_INET,SOCK_STREAM,0);
    ExitIfBad(sock == -1,"Prob with socket");

    
    struct sockaddr_in addr;
    struct sockaddr_in addr_client;

    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;

    int is_good = bind(sock,(const sockaddr *)&addr,sizeof(addr));
    ExitIfBad(is_good == -1,"Prob with bind");

    is_good = listen(sock,SOMAXCONN);
    ExitIfBad(is_good != 0,"Prob with listen");


    socklen_t size = sizeof(addr);
    m_client = accept(sock,(sockaddr *)&addr_client,&size);
}

ssize_t ServerSocket::Send(const std::vector<char>& msg)
{
    size_t bytes_send = 0;


    while(bytes_send != msg.size())
    {
        ssize_t send_ret = send(m_client,msg.data() + bytes_send,msg.size()- bytes_send,MSG_CONFIRM);
        
        if(send_ret == -1)
        {
            return -1;
        }
        
        bytes_send += send_ret;
    }

    return bytes_send;
}

const std::vector<char> ServerSocket::Receive()
{

    std::vector<char> ret;
    
    ret.resize(MAX_USR_MSG);

    ssize_t real_size = recv(m_client,ret.data(),MAX_USR_MSG,0);

    if(real_size == -1)
    {
        return std::vector<char>(BAD_VECTOR);
    }

    ret.resize(real_size);

    return ret;
}

const std::vector<char> ServerSocket::Receive(int size)
{
    std::vector<char> ret;
    
    ret.resize(size * sizeof(char));

    ssize_t real_size = recv(m_client,ret.data(),size,0);

    while(real_size != size)
    {
        real_size += recv(m_client,ret.data() + real_size,(size - real_size),0);
    
        if(real_size == -1)
        {
            return std::vector<char>(BAD_VECTOR);
        }
    }

    return ret;
}

int ServerSocket::GetEndpoint()
{
    
    return m_client;
}

void ServerSocket::Connect(int port, const std::string &ip)
{
    openServer(port);

    (void)ip;
}

void SocketClient::ConnectToServer(int port, const std::string &ip)
{
    struct sockaddr_in addr;

    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_family = AF_INET;

    m_server = socket(AF_INET,SOCK_STREAM,0);
    ExitIfBad(m_server == -1,"Prob with socket");

    socklen_t size = sizeof(addr);

    int is_good = connect(m_server,(struct sockaddr*)&addr,size);
    ExitIfBad(is_good == -1,"Prob with connect");

}

void SocketClient::Connect(int port, const std::string &ip)
{
    ConnectToServer(port,ip);
}

ssize_t SocketClient::Send(const std::vector<char> &msg)
{
    size_t bytes_send = 0;


    while(bytes_send != msg.size())
    {
        ssize_t send_ret = send(m_server,msg.data() + bytes_send,msg.size()- bytes_send,MSG_CONFIRM);
        
        if(send_ret == -1)
        {
            return -1;
        }
        
        bytes_send += send_ret;
    }

    return bytes_send;

}

int SocketClient::GetEndpoint()
{
    return m_server;
}

const std::vector<char> SocketClient::Receive()
{
    std::vector<char> ret;
    
    ret.resize(MAX_USR_MSG);

    ssize_t real_size = recv(m_server,ret.data(),MAX_USR_MSG,0);
    
    if(real_size == -1)
    {
        return std::vector<char>(BAD_VECTOR);
    }
    
    ret.resize(real_size);

    return ret;
}

const std::vector<char> SocketClient::Receive(int size)
{
    std::vector<char> ret;
    
    ret.resize(size * sizeof(char));

    ssize_t real_size = recv(m_server,ret.data(),size,0);

    while(real_size != size)
    {
        real_size += recv(m_server,ret.data() + real_size,(size - real_size),0);
    
        if(real_size == -1)
        {
            return std::vector<char>(BAD_VECTOR);
        }
    }

    return ret;
}