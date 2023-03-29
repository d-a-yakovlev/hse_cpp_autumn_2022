#pragma once
#include <iostream>

#include "serializer.hpp"
#include "error.hpp"

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


struct DataC
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
    uint64_t b;
    uint64_t c;
};


struct DataOneBool
{
    DataOneBool(bool arg) : a(arg) {}
    
    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a);
    }

    bool a;
};


struct DataOneUint
{
    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a);
    }

    uint64_t a;
};