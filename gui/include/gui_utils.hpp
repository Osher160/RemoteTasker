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

class CheckNSend : public Gtk::Window
{
 public:
    CheckNSend(bool *is_true);

 private:
    void on_check_clicked();


    Gtk::Button m_button;
    Gtk::CheckButton m_is_server;
    
    bool *m_is_true;

    Gtk::Box m_box;

};


} // namespace remote_tasker

#endif // __GUI_UTILS_HPP__