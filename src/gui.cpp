#include "gui.hpp"

#include<gtkmm.h>

remote_tasker::App::App():
m_button("Search In This Computer"),
m_button2("Search In Another Computer"),
m_box(Gtk::Orientation::VERTICAL)
{
    set_child(m_box);

    m_button.set_margin(10);

    m_button2.set_margin(10);

    set_title("Remote Tasker");

    set_default_size(700, 500);

    m_button.signal_clicked().connect(sigc::mem_fun(*this,&remote_tasker::App::on_button_clicked));
    m_button2.signal_clicked().connect(sigc::mem_fun(*this,&remote_tasker::App::on_button_clicked));

    m_box.append(m_button);
    m_box.append(m_button2);
}

void remote_tasker::App::on_button_clicked()
{
    std::cout << "hello world" << std::endl;
}

int main(int argc, char ** argv)
{
    auto app = Gtk::Application::create("org.gtkmm.example.base");

    return app->make_window_and_run<remote_tasker::App>(argc,argv);
}