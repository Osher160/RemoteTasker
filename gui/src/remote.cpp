#include <thread>

#include <glibmm/iochannel.h>

#include "remote.hpp"
#include "connector.hpp"


bool MyCallback(Glib::IOCondition io_condition,std::shared_ptr<remote_tasker::Socket> sock,remote_tasker::SearchManager *manager)
{
    if(!io_condition)
    {
        // TODO - more subtle
        exit(1);
    }
    std::vector<char> name = sock->Receive();

    std::string msg = manager->SearchNSendNewComputerGui(name.data(),sock);

    std::cout << msg << std::endl;

    return true;
}

remote_tasker::Remote::Remote(std::string save_dir,bool is_server):
 m_to_search("Search"),
 m_box(Gtk::Orientation::VERTICAL),
 m_manager(save_dir),
 m_label("Enter the filename wanted")
{
    int port = 0;
    std::string ip;

    // using InitRemote, check with the user the correct port and ip
    auto app = Gtk::Application::create("org.gtkmm.Init");

    app->make_window_and_run
    <remote_tasker::InitRemote,bool,std::string * ,int *>(0,NULL,bool(is_server),&ip,&port);
    
    // Init Socket according to server/ client
    if(is_server)
    {
        m_sock.reset(new ServerSocket);
        //TODO if server -open window that wait until server connected

        m_sock->Connect(port,ip);
    }
    else
    {
        m_sock.reset(new SocketClient);

        m_sock->Connect(port,ip);

    }

    // for getting new requests    
    m_to_search.signal_clicked().connect(sigc::mem_fun(*this, 
                            &remote_tasker::Remote::OnSearch));  
    
 Glib::signal_io().connect(sigc::bind(sigc::ptr_fun(MyCallback),m_sock,&m_manager), m_sock->GetEndpoint(), Glib::IOCondition::IO_IN);

    // init box, entry , button, etc
    // init box, entry , button, etc
    set_title("RemoteTasker");
    set_default_size(100,300);

    m_entry.set_margin(10);

    m_box.append(m_label);
    m_box.append(m_entry);
    m_box.append(m_to_search);


    set_child(m_box);

}

void remote_tasker::Remote::OnSearch()
{

    //get the name of the file
    std::shared_ptr<Gtk::EntryBuffer> buff = m_entry.get_buffer();

    std::string name = buff->get_text();

    //send the name to socket
    std::vector<char> name_vec;

    std::copy(name.begin(),name.end(),std::back_inserter(name_vec));
    
    m_sock->Send(name_vec);

    //wait for response
    std::string msg = m_manager.SaveFromOtherComputerGui(name,m_sock);


    // return status to user

    std::cout << msg << std::endl;
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
