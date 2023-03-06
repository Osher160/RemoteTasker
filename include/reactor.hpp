/******************************************************************************/
/*	Project:	Remote Tasker   										      */
/*	File:		reactor.hpp		    										  */
/*	Version: 	0.01														  */
/******************************************************************************/

#ifndef __REACTOR_HPP__
#define __REACTOR_HPP__

#include <functional> // std::function
#include <vector>    //vector
#include <atomic>   // atomic<bool>
#include <map>     //map


namespace remote_tasker
{

using Function = std::function<void()>;

class Reactor
{
public:
    enum Mode{READ,WRITE};

    explicit Reactor();
    ~Reactor();

    // None Copyable
    Reactor(const Reactor& o) = delete;
    Reactor& operator=(const Reactor& o) = delete;

    void Remove(int fd,Mode mode);
    void Add(Function action, int fd, Mode mode);
    void stop();
    void Run();

private:
    using Pair = std::pair<int,Mode>;

    std::vector<Pair> select(const std::vector<Pair> &);

    std::map<Pair,Function> m_container; 
    std::atomic<bool> m_shouldStop;
};


}  //remote_tasker


#endif //	ifndef __REACTOR_HPP__			