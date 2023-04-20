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
        
    char buffer[BUFF_SIZE] = {0};
    
    while(file.read(buffer,BUFF_SIZE))
    {

        new_file.write(buffer,file.gcount());

    }

    if(!file.eof() || !new_file)
    {
        std::cout << "problem in transferring the file" << std::endl;   
    } 

    else
    {
        std::cout << "the file: " << file_name << " saved into the " << m_save_to 
        << " directory " << std::endl; 
    }

    file.close();
    new_file.close();
}

std::string SearchManager::SearchNSendSameComputerGui(const std::string file_name)
{
    std::ifstream file;
    try
    {
        file =  FindFile(file_name,"/home/");

    }
    catch(std::runtime_error &err)
    {
        return err.what(); 
    }

    if(!std::filesystem::exists(m_save_to) || !std::filesystem::is_directory(m_save_to))
    {
        std::filesystem::create_directory(m_save_to);
    }

    std::string save_to = m_save_to + '/' + file_name;

    std::ofstream new_file(save_to,std::ios::binary | std::ios::out);
        
    char buffer[BUFF_SIZE] = {0};
    
    while(file.read(buffer,BUFF_SIZE))
    {

        new_file.write(buffer,file.gcount());

    }

    std::string ret;

    if(!file.eof() || !new_file)
    {
        ret =  "problem in transferring the file";   
    } 

    else
    {
        ret =  "the file: " + file_name + " saved into the " + m_save_to 
        + " directory "; 
    }

    file.close();
    new_file.close();

    return ret;
}

void SearchManager::SearchNSendNewComputer(std::string file_name, 
                        std::shared_ptr<remote_tasker::Socket> sock)
{
    std::ifstream file;

    // default - true - if file not found - became false and send empty vector
    bool is_true = true;

    try
    {
        file =  FindFile(file_name,"/home/");
    }
    
    catch(std::runtime_error &err)
    {
        std::cout << err.what() << std::endl;

        is_true = false;
    }

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

    std::size_t size_to_send = file_to_send.size();
    std::vector<char> size;

    char *size_ptr = reinterpret_cast<char *>(&size_to_send);

    for(size_t i = 0; i < sizeof(size_t); ++i)
    {
        size.push_back(size_ptr[i]);
    }

    if(sock->Send(size) == -1)
    {

        std::cout << "there was a problem sending the file, abort." << std::endl;

        return;
    }

    if(size_to_send == 0)
    {
        return;
    }

    if(sock->Send(file_to_send) == -1)
    {
        std::cout << "there was a problem sending the file, abort." << std::endl;

        return;
    }
}

void SearchManager::SaveFromOtherComputer(std::string file_name, 
                        std::shared_ptr<remote_tasker::Socket> sock)
{
    if(!std::filesystem::exists(m_save_to) || !std::filesystem::is_directory(m_save_to))
    {
        std::filesystem::create_directory(m_save_to);
    }

    std::string save_to = m_save_to + '/' + file_name;

    std::vector to_size = sock->Receive(sizeof(size_t));
    
    std::size_t * size = reinterpret_cast<size_t *>(to_size.data());

    if(*size == 0)
    {
        std::cout << "the file: " << file_name << " not found" << std::endl;

        return;    
    }
    
    // after checking if the file found -> create new file and copy the content
    std::ofstream new_file(save_to,std::ios::binary | std::ios::out);
    


    std::vector file_data = sock->Receive(*size);

    if (file_data.size() == 1 && file_data.front() == Socket::BAD_VECTOR)
    {
        std::cout << "there was a problem with the file, abort save." << std::endl;
        return;
    }


    std::size_t i = 0;

    while(file_data.size() > i)
    {
        new_file.put(file_data[i]);
        ++i;
    }

    std::cout << "the file: " << file_name << " saved into the " << m_save_to 
    << " directory " << std::endl;     
}


} // namespace remote_tasker