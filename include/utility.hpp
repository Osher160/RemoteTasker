/******************************************************************************/
/*	Project:	Remote Tasker   										      */
/*	File:		utility.hpp		    										  */
/*	Version: 	0.01														  */
/******************************************************************************/

#include <iostream>
// check if all test ret value are as expected 
// return value: 0 in case of success,-1 in case of failure in one of the test
int IsSuccess(int tests_ret_val, int expected);


// if val != expected_val -> massage and exit program
inline void ExitIfBad(int val,std::string massage)
{
    if(val)
    {
        std::cout << massage << std::endl;
        exit(-1);
    }
}