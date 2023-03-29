/******************************************************************************/
/*	Project:	Remote Tasker   										      */
/*	File:		connector.hpp	    										  */
/*	Version: 	0.02														  */
/******************************************************************************/

#include <iostream>
#include <vector>

#ifdef __linux__
#include <unistd.h> // read 

#include <sys/types.h>
#include <netinet/in.h> // sockaddr_in 
#include <arpa/inet.h> // inet_addr 

#include <sys/socket.h> // sockets 

#elif _WIN32

#endif


namespace remote_tasker
{

class Socket
{
public:

    virtual int Send(const std::vector<char>& msg) = 0;

    virtual const std::vector<char>& Receive() = 0;
};


class SocketServer : public Socket 
{
public:
    SocketServer() = default;

    // return endpoint to client
    int openServer(int port);


private:

};

class SocketClient : public Socket
{
public:
    // return endpoint to server
    int ConnectToServer(int port,const std::string& ip);

private:

};

}// namespace remote_tasker