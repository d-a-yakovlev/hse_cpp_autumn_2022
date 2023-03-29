#pragma once
#include <iostream>
#include <string>
#include <cstring>

#include "error.hpp"


class Serializer
{
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out): out_(out) {};

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }
    
private:
    std::ostream& out_;

    Error process(bool& arg);
    Error process(uint64_t& arg);

    template <class T, class... ArgsT>
    Error process(T&& arg, ArgsT&&... argPack)
    {
        Error err = process(arg);
        if (err == Error::CorruptedArchive)
            return Error::CorruptedArchive;

        return process(std::forward<ArgsT>(argPack)...);
    }
};


class Deserializer
{
public:
    explicit Deserializer(std::istream& in): in_(in) {};

    template <class T>
    Error load(T& object) {
        return object.deserialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }

private:
    std::istream& in_;

    Error process(bool& value);
    Error process(uint64_t& value);

    template <class T, class... ArgsT>
    Error process(T&& arg, ArgsT&&... argPack)
    {
        Error err = process(arg);
        if (err == Error::CorruptedArchive)
            return Error::CorruptedArchive;

        return process(std::forward<ArgsT>(argPack)...);
    }
};
