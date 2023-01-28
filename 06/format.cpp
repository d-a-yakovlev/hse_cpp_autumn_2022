#include "format.hpp"


// void cute::process()
// {
   
// }


bool cute::isFormatException(std::string str, size_t curIdx, size_t &argIdx)
{
    size_t argIdx_ = 0;

    curIdx++; // переход указателя в фигурную скобку
    std::cout << "In isFormatException" << std::endl;
    while (str[curIdx] != '}')
    {
        if (!isdigit(str[curIdx])) {
            return true;
        } else {
            argIdx_ = (argIdx_*10) + static_cast<size_t>(str[curIdx] - '0');
            std::cout << argIdx_ << std::endl;
        }

        curIdx++;
    }
    argIdx = argIdx_;

    return false;
}


std::string cute::joinStringVector(std::vector<std::string> &strs)
{
    std::string result = "";
    std::cout << "what in substrs" << std::endl;
    for (std::string substr : strs) {
        std::cout << substr;
        result += substr;
    }
    std::cout << std::endl;

    return result;
}