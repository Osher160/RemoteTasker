/******************************************************************************/
/*	Project:	Remote Tasker   										      */
/*	File:		file_finder.cpp	    										  */
/*	Version: 	0.01														  */
/******************************************************************************/
#include <filesystem>
#include <iostream>

#include "file_finder.hpp"

namespace remote_tasker
{

std::ifstream FindFile(std::string file_name,std::string root)
{
    std::ifstream ret;

    for(auto entry : std::filesystem::recursive_directory_iterator(root,
                std::filesystem::directory_options::skip_permission_denied))
    {
        if(std::filesystem::is_regular_file(entry.path()) && 
                                (entry.path().filename() == file_name))
        {
            
            ret.open(entry.path());
            return ret;
        }
    }

    throw std::runtime_error("file not found");
}

} //namespace remote_tasker