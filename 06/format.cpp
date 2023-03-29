#include "format.hpp"


bool cute::isFormatException(std::string str, size_t curIdx, size_t &argIdx)
{
    size_t argIdx_ = 0;

    curIdx++; // переход указателя в фигурную скобку
#ifndef RELEASE
    std::cout << "In isFormatException" << std::endl;
#endif
    while (str[curIdx] != '}')
    {
        if (!isdigit(str[curIdx])) {
            return true;
        } else {
            argIdx_ = (argIdx_*10) + static_cast<size_t>(str[curIdx] - '0');
#ifndef RELEASE
            std::cout << argIdx_ << std::endl;
#endif
        }

        curIdx++;
    }
    argIdx = argIdx_;

    return false;
}


std::string cute::joinStringVector(std::vector<std::string> &strs)
{
    std::string result = "";
#ifndef RELEASE
    std::cout << "what in substrs" << std::endl;
#endif
    for (std::string substr : strs) {
#ifndef RELEASE
        std::cout << substr;
#endif
        result += substr;
    }
#ifndef RELEASE
    std::cout << std::endl;
#endif

    return result;
}