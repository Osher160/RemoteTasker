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

namespace remote_tasker
{

class Remote : public Gtk::Window
{
 public:
    Remote(std::string save_dir);

 private:

    void OnSearch();
    
    Gtk::Entry m_entry;
    Gtk::Button m_to_search;
    Gtk::Box m_box;
    SearchManager manager;
    std::shared_ptr<remote_tasker::Socket> m_sock;
};

class Result : public Gtk::Window
{
 public:
    Result(std::string response);

 private:
    Gtk::Label m_label;
};

} // namespace remote_tasker

#endif // __remote_HPP__