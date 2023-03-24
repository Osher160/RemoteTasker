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

        std::string save_to = m_save_to + '/' + file_name;

        std::ofstream new_file(save_to);

        while(!file.eof())
        {
            new_file.put(file.get());
        }
        
    }


} // namespace remote_tasker