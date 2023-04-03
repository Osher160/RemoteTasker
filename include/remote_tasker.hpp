/******************************************************************************/
/*	Project:	Remote Tasker   										      */
/*	File:		remote_tasker.hpp    										  */
/*	Version: 	0.02														  */
/******************************************************************************/

#include <memory>

#include "reactor.hpp"
#include "connector.hpp"
#include "search_manager.hpp"

namespace remote_tasker
{


class RemoteTasker
{
public:
    explicit RemoteTasker(std::shared_ptr<remote_tasker::Reactor> reactor,
    std::shared_ptr<remote_tasker::SearchManager> search_manager);

    void RunOnlyThisComputer();
    
    void RunAll();

private:
    void InitAndActivateReactor();
    std::shared_ptr<remote_tasker::Reactor> m_reactor;
    std::shared_ptr<remote_tasker::Socket> m_sock;
    std::shared_ptr<remote_tasker::SearchManager> m_search_manager;
};

} // namespace remote_tasker