#pragma once
#include <iostream>
#include <string>
#include <cstring>


enum class Error
{
    NoError,
    CorruptedArchive
};


struct DataA
{
    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }

    uint64_t a;
    bool b;
    uint64_t c;
};


struct DataB
{
    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }

    bool a;
    bool b;
    uint64_t c;
};


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
private:
    std::ostream& out_;
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
private:
    std::istream& in_;
};
