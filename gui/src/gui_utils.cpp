#include "gui_utils.hpp"

namespace remote_tasker
{


CheckNSend::CheckNSend(bool *is_true):
 m_button("Send"),
 m_is_server("Server"),
 m_is_true(is_true),
 m_box(Gtk::Orientation::VERTICAL)
{
    set_title("Is This Computer Server?");
    set_default_size(300, 200);

    m_is_server.set_margin(10);
    m_button.set_margin(10);
    
    m_button.signal_clicked().connect(sigc::mem_fun(*this,
                        &remote_tasker::CheckNSend::on_check_clicked));

    m_box.append(m_is_server);
    m_box.append(m_button);

    set_child(m_box);
}

void CheckNSend::on_check_clicked()
{
    close();

    *m_is_true = m_is_server.get_active();
}




Result::Result(std::string response):
 m_label(response)
{
    set_title("Massage");
    set_default_size(300, 200);

    set_child(m_label);
}

} // namespace remote_tasker