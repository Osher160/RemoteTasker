/******************************************************************************/
/*	Project:	Remote Tasker   										      */
/*	File:		file_finder.hpp	    										  */
/*	Version: 	0.01														  */
/******************************************************************************/
#ifndef __SEARCH_MANAGER_HPP__
#define __SEARCH_MANAGER_HPP__

#include<iostream>

namespace remote_tasker
{

class SearchManager
{
public:    
    explicit SearchManager(std::string save_dir = "");
    ~SearchManager()=default;

    // for now - searching only in /home/ directories. 
    void SearchNSendSameComputer(std::string file_name);
    
    // linux version TODO -- 0.02
    // void SearchNSendNewComputer(std::string file_name, int socket_fd);


private:
    std::string m_save_to;
    // int m_socket? -- 0.02
}; //class SearchManager

} // namespace remote_tasker


#endif //__SEARCH_MANAGER_HPP__