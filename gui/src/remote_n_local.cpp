#include "remote_n_local.hpp"

#include<gtkmm.h>

remote_tasker::RemoteNLocal::RemoteNLocal():
 m_button("Search In This Computer"),
 m_button2("Search In Another Computer"),
 m_box(Gtk::Orientation::VERTICAL)
{
    set_child(m_box);

    m_button.set_margin(10);

    m_button2.set_margin(10);

    set_title("Remote Tasker");

    set_default_size(200, 100);

    m_button.signal_clicked().connect(sigc::mem_fun(*this,&remote_tasker::RemoteNLocal::on_button_clicked));
    m_button2.signal_clicked().connect(sigc::mem_fun(*this,&remote_tasker::RemoteNLocal::on_button_clicked));

    m_box.append(m_button);
    m_box.append(m_button2);
}

void remote_tasker::RemoteNLocal::on_button_clicked()
{
    std::cout << "hello world" << std::endl;

    close();
}

int main(int argc, char ** argv)
{
    auto app = Gtk::Application::create("org.gtkmm.check-server");

    return app->make_window_and_run<remote_tasker::RemoteNLocal>(argc,argv);
}