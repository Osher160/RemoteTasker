#include "connector.hpp"

void ServerTest();
void ClientTest();



int main(int argc, char **argv)
{
    if(std::string("client") == argv[1])
    {
        ClientTest();
    }
    
    else
    {
        ServerTest();
    }

    return 0;
}



void ServerTest()
{
    using namespace remote_tasker;

    ServerSocket sock;

    sock.openServer(50000);

    std::vector<char> arr;

    arr.push_back('h');
    arr.push_back('i');

    sock.Send(arr);
    std::vector<char> arr_recv = sock.Receive();

    std::cout << arr_recv.data() << std::endl;
}

void ClientTest()
{
    using namespace remote_tasker;

    SocketClient sock;

    sock.ConnectToServer(50000,"127.0.0.1");

    std::vector<char> arr_recv = sock.Receive();

    std::cout << arr_recv.data() << std::endl;
    
    std::vector<char> arr;

    arr.push_back('b');
    arr.push_back('y');

    sock.Send(arr);
}