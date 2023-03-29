#pragma once

#include <algorithm>
#include <cstring>
#include <iostream>
#include <map> 
#include <sstream>
#include <vector>

#define RELEASE


namespace cute
{

    enum class Error
    {
        ArgumentException,
        BadFormat,
    };

    bool isFormatException(std::string str, size_t curIdx, size_t &argIdx);
    std::string joinStringVector(std::vector<std::string> &strs);

    // вектор подстрок
    static std::vector<std::string> substrs;

    // мапа : индекс_аргумента -> {индекс подстроки1, индекс подстроки2, ...}
    static std::map<size_t, std::vector<size_t>> arg2substr;


    // счётчик аргументов (глубина рекурсии)
    static size_t processArgCounter = 0;

    template <class T>
    void process(T&& arg) {
#ifndef RELEASE
        std::cout << "in lil process" << std::endl;
#endif
        std::stringstream ios;

        ios << arg;
        std::string text;
        ios >> text;

        for (size_t substrIdx : arg2substr[processArgCounter]) {
            substrs[substrIdx] = substrs[substrIdx] + text;
        }
        processArgCounter++;

        // обработали все аргументы, проверяем на корректность кол-ва аргументов в строке и пришедших

        std::vector<size_t> keys;
        for (auto it = arg2substr.begin(); it != arg2substr.end(); it++) {
            keys.push_back(it->first);
        }

        if (keys.size() > processArgCounter) {
            throw Error::ArgumentException;
        }

        if (*(max_element(keys.begin(), keys.end())) > processArgCounter) {
            throw Error::ArgumentException;
        }
    }

    template <class T, class... ArgsT>
    void process(T&& arg, ArgsT&&... args)
    {
#ifndef RELEASE
        std::cout << "in big process" << std::endl;
#endif
        std::stringstream ios;

        ios << arg;
        std::string text;
        ios >> text;
#ifndef RELEASE
        std::cout << text << std::endl;
#endif
        
        for (size_t substrIdx : arg2substr[processArgCounter])
        {
#ifndef RELEASE
            std::cout << "substrIdx : " << substrIdx << "; text : " << text << "; processArgCounter : " << processArgCounter << std::endl;
#endif

            substrs[substrIdx] = substrs[substrIdx] + text;
        }

        processArgCounter++;
        process(std::forward<ArgsT>(args)...);
    }


    template <class... ArgsT>
    std::string format(std::string str, ArgsT&&... argPack)
    {
        processArgCounter = 0;
        bool notClosed = false;
        size_t substrBegin = 0;

        size_t argIdx = 0; // индекс аргумента
        std::string substr = "";
        size_t substrIdx = 0; // индекс подстроки

        substrs.clear();
        arg2substr.clear();

        // цикл обработчик строчки
#ifndef RELEASE
        std::cout << "I am in loop" << std::endl;
#endif
        for (size_t i=0; i < str.length(); ++i)
        {
#ifndef RELEASE
            std::cout << i << "iteration : " << str[i] << "; substrBegin :" << substrBegin <<std::endl;
#endif
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

                substr = str.substr(substrBegin, i - substrBegin);
#ifndef RELEASE
                std::cout << "substr is : " << substr << std::endl;
#endif
                substrs.push_back(substr);
                
                arg2substr[argIdx].push_back(substrIdx);
                substrIdx++;
            }
        }

        std::vector<size_t> keys;
        for (auto it = arg2substr.begin(); it != arg2substr.end(); it++) {
            keys.push_back(it->first);
        }
#ifndef RELEASE
        for (size_t key : keys) {
            std::cout << "arg2substr[" << std::to_string(key) << "] = " << std::endl;
            for (auto el : arg2substr[key]) {
                std::cout << el << " ";
            }
            std::cout << std::endl;
        }
#endif
        process(std::forward<ArgsT>(argPack)...);

        return joinStringVector(substrs);
    }

}