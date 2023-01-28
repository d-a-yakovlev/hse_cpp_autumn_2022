#pragma once

#include <cstring>
#include <iostream>
#include <map>
#include <ranges>
#include <sstream>
#include <vector>


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
        std::cout << "in lil process" << std::endl;
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

        if (keys.size() > processArgCounter ) {
            throw Error::ArgumentException;
        }
    }

    template <class T, class... ArgsT>
    void process(T&& arg, ArgsT&&... args)
    {
        std::cout << "in big process" << std::endl;
        std::stringstream ios;

        ios << arg;
        std::string text;
        ios >> text;

        std::cout << text << std::endl;
        
        for (size_t substrIdx : arg2substr[processArgCounter])
        {
            std::cout << "substrIdx : " << substrIdx << "; text : " << text << "; processArgCounter : " << processArgCounter << std::endl;

            substrs[substrIdx] = substrs[substrIdx] + text;
        }

        processArgCounter++;
        process(std::forward<ArgsT>(args)...);
    }


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

        // цикл обработчик строчки
        std::cout << "I am in loop" << std::endl;
        for (size_t i=0; i < str.length(); ++i)
        {
            std::cout << i << "iteration : " << str[i] << "; substrBegin :" << substrBegin <<std::endl;
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
                std::cout << "substr is : " << substr << std::endl;
                substrs.push_back(substr);
                
                arg2substr[argIdx].push_back(substrIdx);
                substrIdx++;
            }
        }

        std::vector<size_t> keys;
        for (auto it = arg2substr.begin(); it != arg2substr.end(); it++) {
            keys.push_back(it->first);
        }

        for (size_t key : keys) {
            std::cout << "arg2substr[" << std::to_string(key) << "] = " << std::endl;
            for (auto el : arg2substr[key]) {
                std ::cout << el << " ";
            }
            std::cout << std::endl;
        }


        process(std::forward<ArgsT>(argPack)...);

        return joinStringVector(substrs);
    }

}