/******************************************************************************/
/*	Project:	Remote Tasker   										      */
/*	File:		gui.hpp	    										          */
/*	Version: 	0.02														  */
/******************************************************************************/
#ifndef __GUI_HPP__
#define __GUI_HPP__

#include <iostream>
#include <vector>

#include <gtkmm.h>

namespace remote_tasker
{

class App: public Gtk::Window
{
public:
    App();
    
protected:
    void on_button_clicked();

private:

    Gtk::Button m_button;
    Gtk::Button m_button2;

    Gtk::Box m_box;

};

} // namespace remote_tasker
#endif // __GUI_HPP__