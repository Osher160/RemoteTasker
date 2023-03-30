/******************************************************************************/
/*	Project:	Remote Tasker   										      */
/*	File:		connector.hpp	    										  */
/*	Version: 	0.02														  */
/******************************************************************************/
#ifndef __CONNECTOR_HPP__
#define __CONNECTOR_HPP__


#include <iostream>
#include <vector>


namespace remote_tasker
{

class Socket
{
public:

    virtual ssize_t Send(const std::vector<char>& msg) = 0;

    virtual const std::vector<char> Receive() = 0;

    enum  { MAX_USR_MSG = 4096};
};


class ServerSocket : public Socket 
{
public:
    ServerSocket(): m_client(0) {};

    void openServer(int port);

    virtual ssize_t Send(const std::vector<char>& msg);
    virtual const std::vector<char> Receive();


private:
    int m_client;
};

class SocketClient : public Socket
{
public:
    void ConnectToServer(int port,const std::string& ip);

    virtual ssize_t Send(const std::vector<char>& msg);
    virtual const std::vector<char> Receive();

private:
    int m_server;

};

}// namespace remote_tasker
#endif //__CONNECTOR_HPP__