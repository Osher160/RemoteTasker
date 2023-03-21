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

// reactor is an object that implements event driven behaviour.
// in linux- it's attached to file descriptor(s) and sleeps until there is a change in the file(s).

using Function = std::function<void()>;

class Reactor
{
public:
    enum Mode{READ,WRITE};
    using Pair = std::pair<int,Mode>;

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

    std::vector<Pair> Select(const std::vector<Pair> &);

    std::map<Pair,Function> m_container; 
    std::atomic<bool> m_shouldStop;
};


}  //remote_tasker


#endif //	ifndef __REACTOR_HPP__			