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
    virtual int GetEndpoint() =0;
   
    virtual void Connect(int port,const std::string& ip) =0;
   
    virtual ssize_t Send(const std::vector<char>& msg) = 0;

    //return vector of chars if succuss, else, returns vector of char with 0;
    virtual const std::vector<char> Receive() = 0;
    virtual const std::vector<char> Receive(int size)= 0;


    enum  { MAX_USR_MSG = 4096000};
    enum {BAD_VECTOR = 0};
};


class ServerSocket : public Socket 
{
public:
    ServerSocket(): m_client(0) {};

    void openServer(int port);

    // if not initialized (A.K.A openServer activated) - return 0
    virtual int GetEndpoint();

    virtual void Connect(int port,const std::string& ip);
    
    virtual ssize_t Send(const std::vector<char>& msg);

    virtual const std::vector<char> Receive();
    virtual const std::vector<char> Receive(int size);
    

private:
    int m_client;
};

class SocketClient : public Socket
{
public:
    void ConnectToServer(int port,const std::string& ip);
    // if not initialized (A.K.A ConnectToServer activated) - return 0

    virtual int GetEndpoint();

    virtual void Connect(int port,const std::string& ip);
    
    virtual ssize_t Send(const std::vector<char>& msg);

    virtual const std::vector<char> Receive();
    virtual const std::vector<char> Receive(int size);

private:
    int m_server;

};

}// namespace remote_tasker
#endif //__CONNECTOR_HPP__