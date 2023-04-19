/******************************************************************************/
/*	Project:	Remote Tasker   										      */
/*	File:		remote_n_local.hpp	    										          */
/*	Version: 	0.03														  */
/******************************************************************************/
#ifndef __REMOTE_N_LOCAL_HPP__
#define __REMOTE_N_LOCAL_HPP__

#include <iostream>
#include <vector>

#include <gtkmm.h>

namespace remote_tasker
{

class RemoteNLocal: public Gtk::Window
{
public:
    RemoteNLocal();
    
protected:
    void on_button_clicked();

private:

    Gtk::Button m_button;
    Gtk::Button m_button2;

    Gtk::Box m_box;

};

} // namespace remote_tasker
#endif // __REMOTE_N_LOCAL_HPP__