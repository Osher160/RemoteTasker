#include "remote.hpp"
#include "connector.hpp"

remote_tasker::Remote::Remote(std::string save_dir,bool is_server):
 m_manager(save_dir)
{
    int port = 0;
    std::string ip;

    // using InitRemote, check with the user the correct port and ip
    auto app = Gtk::Application::create("org.gtkmm.Init");

    app->make_window_and_run
    <remote_tasker::InitRemote,bool,std::string * ,int *>(0,NULL,bool(is_server),&ip,&port);

    std::shared_ptr<Socket> sock = nullptr;
    
    // Init Socket according to server/ client
    if(is_server)
    {
        sock.reset(new ServerSocket);
        //TODO if server -open window that wait until server connected

        sock->Connect(port,ip);
    }
    else
    {
        sock.reset(new SocketClient);

        sock->Connect(port,ip);

    }

    std::cout << "hi" <<std::endl;
    // open a thread that will be waiting on reactor for requests from socket

    //

}

void remote_tasker::Remote::OnSearch()
{
    
}

void remote_tasker::Remote::InitNActivateReactor()
{

}

remote_tasker::InitRemote::InitRemote
                    (bool is_server,std::string *ret_ip, int *ret_port):
m_send("Send"),
m_box(Gtk::Orientation::VERTICAL),
m_ret_ip(ret_ip),
m_ret_port(ret_port)
{
    //set title & default size
    set_title("Initialize");
    set_default_size(200,100);

    m_ip.set_text("Insert IP");
    m_port.set_text("Insert Port"); 


    // init the buttons and entries
    set_child(m_box);

    m_ip.set_margin(10);
    m_port.set_margin(10);
    m_send.set_margin(10);

    if(!is_server)
    {
        m_box.append(m_ip);
    }
    m_box.append(m_port);
    m_box.append(m_send);

    // Onclick Init
    m_send.signal_clicked().connect
                    (sigc::mem_fun(*this,&remote_tasker::InitRemote::OnClick));
}

void remote_tasker::InitRemote::OnClick()
{
    //get the text from the entries
    Glib::RefPtr<Gtk::EntryBuffer> buffer = m_ip.get_buffer();

    *m_ret_ip = buffer->get_text();

    buffer = m_port.get_buffer();

    *m_ret_port = std::atoi(std::string(buffer->get_text()).c_str());

    // close the window
    close();
}
