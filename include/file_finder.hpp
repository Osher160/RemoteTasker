/******************************************************************************/
/*	Project:	Remote Tasker   										      */
/*	File:		file_finder.hpp	    										  */
/*	Version: 	0.01														  */
/******************************************************************************/
#ifndef __FINDER_HPP__
#define __FINDER_HPP__

#include <fstream>

namespace remote_tasker
{

// a function that Find a file in the file system and returns ofstream of the file
// throw std::runtime_error if failed to find

//for 0.01 - stops at the first occurrence of the file. find only works inside /home 
std::ifstream FindFile(std::string file_name, std::string root);



} // namespace remote_tasker

#endif //__FINDER_HPP__