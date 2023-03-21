
#include <iostream>

#include <algorithm>
//errno
#include <cerrno>

//select & Macros
#include <sys/select.h>

#include "reactor.hpp"


namespace remote_tasker
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

void Reactor::Stop()
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


    while(!m_shouldStop)
    {
        // convert from map to vector
        std::vector<Pair> to_select;

        std::for_each(m_container.begin(),m_container.end(),
                            [&to_select](std::pair<Pair,Function> fds_n_mode)
                                    {to_select.push_back(fds_n_mode.first);});

        //init new vector with the fds that changed
        std::vector<Reactor::Pair> fds_changed = Select(to_select);

        //doing the functions of the fds_changed
        std::for_each(fds_changed.begin(),fds_changed.end(),
        
        [&](Reactor::Pair find_me)
        {
            this->m_container.at(find_me)();
        }

        );

        while(to_select.size() > 0)
        {
            to_select.pop_back();
        }

    }
}



} //namespace remote_tasker