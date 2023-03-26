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
            
            ret.open(entry.path(),std::ios::binary | std::ios::in);
            return ret;
        }
    }

    std::string err = "file " + file_name + " not found";

    throw std::runtime_error(err);
}

} //namespace remote_tasker