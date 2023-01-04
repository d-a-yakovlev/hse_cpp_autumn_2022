#include "serializer.hpp"


bool isDigitToken(std::string token)
{
    for (size_t i=0; i < token.length(); ++i) {
        if ( !isdigit(token[i]) )
            return false;
    }

    return true;
}


// Serializer section


Error Serializer::process(bool& arg)
{
    std::string value;
    if (arg) {
        value = "true";
    } else {
        value = "false";
    }

    if (out_.tellp() == std::streampos(0)) {
        out_ << value;
    }
    else {
        out_ << Serializer::Separator << value;
    }

    return Error::NoError;
}


Error Serializer::process(uint64_t& arg)
{
    std::string value = std::to_string(arg);
    if (out_.tellp() == std::streampos(0)) {
        out_ << value;
    }
    else {
        out_ << Serializer::Separator << value;
    }

    return Error::NoError;
}


// Deserializer section


Error Deserializer::process(bool& value)
{
    std::string text;
    in_ >> text;

    if (text == "true") {
        value = true;
    } else if (text == "false") {
        value = false;
    } else {
        return Error::CorruptedArchive;
    }
    
    return Error::NoError;
}


Error Deserializer::process(uint64_t& value)
{
    std::string text;
    in_ >> text;

    if (isDigitToken(text)) {
        value = std::stoull(text);
    } else {
        return Error::CorruptedArchive;
    }

    return Error::NoError;
}
