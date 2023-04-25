/******************************************************************************/
/*	Project:	Remote Tasker   						         		      */
/*	File:		remote.hpp	    					       		              */
/*	Version: 	0.03										                  */
/******************************************************************************/
#ifndef __REMOTE_HPP__
#define __REMOTE_HPP__

#include <iostream>
#include <vector>

#include <gtkmm.h>

#include "search_manager.hpp"
#include "reactor.hpp"
#include "gui_utils.hpp"

namespace remote_tasker
{

class InitRemote: public Gtk::Window
{
 public:
   // ret_ip & ret_port are out params
    InitRemote(bool is_server,std::string *ret_ip, int *ret_port);

 private:

    void OnClick(); 
    
    Gtk::Entry m_ip;
    Gtk::Entry m_port;
    
    Gtk::Button m_send;

    Gtk::Box m_box;
   
    std::string *m_ret_ip;
    int *m_ret_port;
     
};

class Remote : public Gtk::Window
{
 public:
    Remote(std::string save_dir,bool is_server);

 private:

    void OnSearch();
    
    //open a thread and activate reactor to catch searches from other computer
    void InitNActivateReactor();

    Gtk::Entry m_entry;
    Gtk::Button m_to_search;
    Gtk::Box m_box;
    
    SearchManager m_manager;

    std::shared_ptr<remote_tasker::Socket> m_sock;
    std::shared_ptr<remote_tasker::Reactor> m_reactor;
};

} // namespace remote_tasker

#endif // __remote_HPP__