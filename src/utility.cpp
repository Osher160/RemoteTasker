#include<iostream> //std::cout

#define KGRN  "\x1B[32m"
#define KRED  "\x1B[31m"
#define RST  "\x1B[0m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST




int IsSuccess(int tests_ret_val, int expected)
{
    if(tests_ret_val != expected)
    {
        std::cout << FRED("problem with the tests.\ninformation above.");

        return -1;
    }

    std::cout << 
                FGRN("Well Done, managed to pass all tests!\n");
    return 0;
}