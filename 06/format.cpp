#include "format.hpp"


bool cute::isFormatException(std::string str, size_t curIdx, size_t &argIdx)
{
    size_t argIdx_ = argIdx;

    curIdx++; // переход указателя в фигурную скобку
    while (str[curIdx] != '}')
    {
        if (!isdigit(str[curIdx])) {
            return true;
        } else {
            argIdx_ = (argIdx_*10) + static_cast<size_t>(str[curIdx]);
        }

        curIdx++;
    }
    argIdx = argIdx_;

    return false;
}


std::string cute::joinStringVector(std::vector<std::string> &substrs)
{
    std::string result = "";
    for (auto substr : substrs) {
        result += substr;
    }

    return result;
}