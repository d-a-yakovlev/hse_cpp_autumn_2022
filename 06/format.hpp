#pragma once

#include <iostream>
#include <vector>
#include <map>

enum class Error
{
    BadFormat,
};

bool isFormatException(std::string str, size_t curIdx, size_t argIdx);

// вектор подстрок
std::vector<std::string> substrs;

// мапа : индекс_аргумента -> {индекс подстроки1, индекс подстроки2, ...}
std::map<size_t, std::vector<size_t>> arg2substr;

template <class... ArgsT>
std::string format(std::string str, ArgsT&&... argPack)
{
    bool notClosed = false;
    size_t substrBegin = 0;

    size_t argIdx = 0; // индекс аргумента
    std::string substr = "";
    size_t substrIdx = 0; // индекс подстроки

    substrs.clear();
    arg2substr.clear();

    for (size_t i=0; i < str.length(); ++i)
    {
        if (notClosed)
        {
            if (str[i] == '}') {
                notClosed = false;
                substrBegin = i + 1;
            } else {
                continue;
            }
        }


        if (str[i] == '{')
        {
            if (isFormatException(str, i, argIdx)) {
                throw Error::BadFormat;
            }

            notClosed = true;

            substr = str.substr(substrBegin, i);
            substrs.push_back(substr);
            
            arg2substr[argIdx].push_back(substrIdx);
            substrIdx++;
        }
    }


    process(std::forward<ArgsT>(argPack)...);

    return joinStringVector(substrs);
}


// счётчик аргументов
size_t processArgCounter = 0;

template <class T, class... ArgsT>
void process(T&& arg, ArgsT&&... args)
{
    for (auto substrIdx : arg2substr[processArgCounter])
    {
        substrs[substrIdx] += arg; // TODO
    }

    processArgCounter++;
    process(std::forward<ArgsT>(args)...);
}