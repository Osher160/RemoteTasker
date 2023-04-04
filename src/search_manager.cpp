#include <filesystem>

#include "search_manager.hpp"
#include "file_finder.hpp"

namespace remote_tasker
{

    SearchManager::SearchManager(const std::string dir_name): m_save_to(dir_name) 
    {}

    // linux version 
    void SearchManager::SearchNSendSameComputer(const std::string file_name)
    {
        std::ifstream file;
        try
        {
            file =  FindFile(file_name,"/home/");
        }
        catch(std::runtime_error &err)
        {
            std::cout << err.what() << std::endl;
            return;
        }

        if(!std::filesystem::exists(m_save_to) || !std::filesystem::is_directory(m_save_to))
        {
            std::filesystem::create_directory(m_save_to);
        }

        std::string save_to = m_save_to + '/' + file_name;

        std::ofstream new_file(save_to,std::ios::binary | std::ios::out);

        bool is_true = true;

        while(is_true)
            
        {
            int ch = file.get();

            if(file.eof())
            {
                break;
            } 

            new_file.put(ch);
        }

        std::cout << "the file: " << file_name << " saved into the " << m_save_to 
        << " directory " << std::endl; 
    }

void SearchManager::SearchNSendNewComputer(std::string file_name, 
                        std::shared_ptr<remote_tasker::Socket> sock)
{
    std::ifstream file;

    try
    {
        file =  FindFile(file_name,"/home/");
    }
    
    catch(std::runtime_error &err)
    {
        std::cout << err.what() << std::endl;
        return;
    }

    bool is_true = true;

    std::vector<char> file_to_send;

    while(is_true)
    {
        char ch = file.get();

        if(file.eof())
        {
            break;
        } 

        file_to_send.push_back(ch);
    }

    sock->Send(file_to_send);
}

void SearchManager::SaveFromOtherComputer(std::string file_name, 
                        std::shared_ptr<remote_tasker::Socket> sock)
{
    
}


} // namespace remote_tasker