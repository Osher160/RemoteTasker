//errno
#include <cerrno>

#include <iostream>

//select & Macros
#include <sys/select.h>

#include "reactor.hpp"


namespace remote_tasker
{

namespace Reactor
{

void Reactor::Add(Function action, int fd, Mode mode)
{
    Reactor::Pair fdNmode(fd,mode);
    m_container.insert(std::make_pair(fdNmode,action));
}

void Reactor::Remove(int fd,Mode mode)
{
    Pair fdNmode(fd,mode);
    m_container.erase(fdNmode);
}

void Reactor::stop()
{
    m_shouldStop.store(1);
}

// the function that drives the event driven functionality
// differs between linux & windows

#ifdef __linux__

// insert the relevant fds to its corresponding set.
void InsertToSet(std::vector<fd_set*> &sets,const std::vector<Reactor::Pair> fds)
{
    for(std::size_t i = 0; i < fds.size(); ++i)
    {
        // KEEP IN MIND that this function is icomplete -- TODO -- fix it for next release- to be not attached to the order in Select
        if(fds[i].second == Reactor::Mode::READ)
        {
            FD_SET(fds[i].first,sets[0]);
        }

        else
        {
            FD_SET(fds[i].first,sets[1]);
        }
    }
}

//finding the biggest fd for select
int BiggestFd(const std::vector<Reactor::Pair> &fds)
{
    int biggest = 0;

    for(std::size_t i = 0; i < fds.size(); ++i)
    {
        if(fds[i].first > biggest)
        {

            biggest = fds[i].first;
        }
    }

    return biggest;
}

std::vector<Reactor::Pair> Reactor::Select(const std::vector<Pair> &fds)
{
    std::vector<Pair> ret;

    fd_set read_fds;
    fd_set write_fds;

    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);

    std::vector<fd_set *> sets;

    //   MUST BE IN THAT ORDER in this version. TODO - fix
    sets.push_back(&read_fds);
    sets.push_back(&write_fds);

    InsertToSet(sets,fds);

    // hardcoded, TODO - future builds - change
    timeval timeout = {5,0};

    int ret_select = select(BiggestFd(fds) +1, &read_fds,&write_fds,nullptr,&timeout);

    if(ret_select == -1)
    {
        //TODO Log & raise exception
        //for now:
        std::perror("select problem:");

        exit(-1);
    }

    else
    {
        for(std::size_t i = 0; i < fds.size(); ++i)
        {
            if(FD_ISSET(fds[i].first,&read_fds))
            {
                ret.push_back(fds[i]);
            }

            else if(FD_ISSET(fds[i].first,&write_fds))
            {
                ret.push_back(fds[i]);
            }
        }
    }

    return ret;
}

#elif _WIN32
// stub select of windows

#endif


void Reactor::Run()
{
    
}


} //namespace Reactor

} //namespace remote_tasker