#include<gtkmm.h>

#include "remote_n_local.hpp"
#include "local.hpp"
#include "remote.hpp"
#include "gui_utils.hpp"




remote_tasker::RemoteNLocal::RemoteNLocal():
 m_label_first("1. Insert a directory name to save the files into:"),
 m_button("Search In This Computer"),
 m_button2("Search In Another Computer"),
 m_label_second("2. Choose to search in this computer or in another:"),
 m_box(Gtk::Orientation::VERTICAL)
{
    // init the buttons and entry
    set_child(m_box);

    m_button.set_margin(10);

    m_button2.set_margin(10);
    
    m_entry.set_text("save location");  
    m_entry.set_margin(10);

    set_title("Remote Tasker");

    set_default_size(200, 100);
    
    //insert functions that activate the local | remote operations

    m_button.signal_clicked().connect(sigc::mem_fun(*this,
                        &remote_tasker::RemoteNLocal::on_button_clicked_local));
    m_button2.signal_clicked().connect(sigc::mem_fun(*this,
                        &remote_tasker::RemoteNLocal::on_button_clicked_remote));

    // append to the box

    m_box.append(m_label_first);
    m_box.append(m_entry);
    m_box.append(m_label_second);

    m_box.append(m_button);
    m_box.append(m_button2);
}

void remote_tasker::RemoteNLocal::on_button_clicked_local()
{
    // Get the save location

    Glib::RefPtr<Gtk::EntryBuffer> buffer = m_entry.get_buffer();

    std::string text = buffer->get_text();

    //Create and Activate local window
    close();

    auto app = Gtk::Application::create("org.gtkmm.local");

    app->make_window_and_run<remote_tasker::Local,std::string>(0,NULL,std::string(text));
}

bool remote_tasker::RemoteNLocal::CheckIfServer()
{
    bool is_server = false;

    auto app = Gtk::Application::create("org.gtkmm.check");

    app->make_window_and_run<remote_tasker::CheckNSend,bool *>(0,nullptr,&is_server);

    return is_server;
}

void remote_tasker::RemoteNLocal::on_button_clicked_remote()
{
    // Get the save location

    Glib::RefPtr<Gtk::EntryBuffer> buffer = m_entry.get_buffer();

    std::string text = buffer->get_text();

    // close window
    close();

    // ask if server or client

    bool is_server = CheckIfServer();

    // open server window
    auto app = Gtk::Application::create("org.gtkmm.remote");

    app->make_window_and_run<remote_tasker::Remote,std::string>(0,NULL,std::string(text),is_server);
}

int main(int argc, char ** argv)
{
    auto app = Gtk::Application::create("org.gtkmm.remote_n_local");

    return app->make_window_and_run<remote_tasker::RemoteNLocal>(argc,argv);
}