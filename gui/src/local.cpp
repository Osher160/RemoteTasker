#include <gtkmm.h>


#include "local.hpp"

remote_tasker::Local::Local(std::string save_dir): 
 m_box(Gtk::Orientation::VERTICAL),
 manager(save_dir)
{
    // set title and size of the window
    set_title("Remote Tasker - Local");
    set_default_size(300, 200);

    // set the m_box under the window
    set_child(m_box);

  // TODO add directory check for search manager

    // set the button and entry values
    m_entry.set_text("file");  
    m_entry.set_margin(10);

    m_to_search.set_label("Search");

    m_box.append(m_entry);
    m_box.append(m_to_search);

    m_to_search.signal_clicked().connect(sigc::mem_fun(*this, 
                            &remote_tasker::Local::OnSearch));
}


void remote_tasker::Local::OnSearch() 
{
    std::shared_ptr<Gtk::EntryBuffer> buff = m_entry.get_buffer();

    std::string response = manager.SearchNSendSameComputerGui(buff->get_text());

    //TODO Show the response to the user


}