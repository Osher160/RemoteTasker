/******************************************************************************/
/*	Project:	Remote Tasker   						         		      */
/*	File:		gui_utils.hpp	   					       		              */
/*	Version: 	0.03										                  */
/******************************************************************************/
#ifndef __GUI_UTILS_HPP__
#define __GUI_UTILS_HPP__

#include <iostream>
#include <vector>

#include <gtkmm.h>

#include "search_manager.hpp"

namespace remote_tasker
{
// class for result of a search

class Result : public Gtk::Window
{
 public:
    Result(std::string response);

 private:
    Gtk::Label m_label;
};


Result::Result(std::string response):
 m_label(response)
{
    set_title("Massage");
    set_default_size(300, 200);

    set_child(m_label);
}



} // namespace remote_tasker

#endif // __GUI_UTILS_HPP__