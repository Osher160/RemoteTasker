/******************************************************************************/
/*	Project:	Remote Tasker   										      */
/*	File:		reactor_test.cpp    										  */
/*	Version: 	0.01														  */
/******************************************************************************/

#include <iostream> // std::cout
#include <string.h> //strncmp

#include <sys/types.h> // open
#include <sys/stat.h> // open
#include <fcntl.h>   // open
#include <unistd.h> // read

#include "reactor.hpp"
#include "utility.hpp"

enum buffer_length{BUFF_LENGTH = 1000};


// test for reactor on stdin fd
int StdinTest();

int main()
{
    return IsSuccess(StdinTest(),0);   
}


// functor for stdin fd in the reactor
class StdinEvent
{
public:

    explicit StdinEvent(remote_tasker::Reactor *notifier);
    ~StdinEvent() {close(m_fd);};
    StdinEvent(StdinEvent&)=default;
    StdinEvent(StdinEvent&&)=default;

    StdinEvent& operator=(StdinEvent& )=delete;

    void operator()();


private:
    remote_tasker::Reactor *m_notifier;
    int m_fd;
};

StdinEvent::StdinEvent(remote_tasker::Reactor *notifier):
m_notifier(notifier)
{
    m_fd = open("test_reactor.txt",O_CREAT | O_RDWR ,S_IRWXU);

    ExitIfBad(m_fd < 0,"problem with open");
}

void StdinEvent::operator()()
{
    char *buff = new char[BUFF_LENGTH];
    
    int bytes_read = read(STDIN_FILENO,buff,BUFF_LENGTH);

    ExitIfBad(bytes_read < 0,"problem with read");

    int bytes_written = write(m_fd,buff,bytes_read);

    if(!strncmp(buff,"exit",4))
    {
        m_notifier->Stop();
    }

    ExitIfBad(bytes_written < 0,"problem with read");

    delete[] buff;
}

int StdinTest()
{
    using namespace remote_tasker;

    Reactor notifier;

    StdinEvent stdin_action(&notifier);

    notifier.Add(std::reference_wrapper<StdinEvent>(stdin_action),0,Reactor::Mode::READ);

    notifier.Run();

    return 0;
}