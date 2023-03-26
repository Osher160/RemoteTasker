#include <filesystem>

#include "search_manager.hpp"
#include "file_finder.hpp"

namespace remote_tasker
{

    SearchManager::SearchManager(std::string dir_name): m_save_to(dir_name) 
    {}

    // linux version 
    void SearchManager::SearchNSendSameComputer(std::string file_name)
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


} // namespace remote_tasker