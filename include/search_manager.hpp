/******************************************************************************/
/*	Project:	Remote Tasker   										      */
/*	File:		search_manager.hpp	    									  */
/*	Version: 	0.01														  */
/******************************************************************************/
#ifndef __SEARCH_MANAGER_HPP__
#define __SEARCH_MANAGER_HPP__

#include<iostream>
#include<memory>

#include "connector.hpp"

namespace remote_tasker
{

class SearchManager
{
public:    
    explicit SearchManager(const std::string save_dir = "saves");
    ~SearchManager()=default;

    // for now - searching only in /home/ directories. 
    void SearchNSendSameComputer(const std::string file_name);
    
    void SearchNSendNewComputer(std::string file_name, 
                std::shared_ptr<remote_tasker::Socket> sock);
    void SaveFromOtherComputer(std::string file_name,std::shared_ptr<remote_tasker::Socket> sock);

private:
    enum {BUFF_SIZE = 1024};
    std::string m_save_to;
}; //class SearchManager

} // namespace remote_tasker


#endif //__SEARCH_MANAGER_HPP__