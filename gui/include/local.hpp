/******************************************************************************/
/*	Project:	Remote Tasker   										      */
/*	File:		local.hpp	    										          */
/*	Version: 	0.03														  */
/******************************************************************************/
#ifndef __LOCAL_HPP__
#define __LOCAL_HPP__

#include <iostream>
#include <vector>

#include <gtkmm.h>

namespace remote_tasker
{

class Local : public Gtk::Window
{
 public:
    Local();

 private:

    void OnSearch();
    
    Gtk::Entry m_entry;
    Gtk::Button m_to_search;
    Gtk::Box m_box;

};

} // namespace remote_tasker

#endif // __LOCAL_HPP__