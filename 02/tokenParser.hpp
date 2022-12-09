#pragma once

#include <iostream>
#include <functional>
#include <cstring>

using sCallBack = std::function<void (std::string & str)>;

class TokenParser
{
public:
    TokenParser() = default;
    std::string parsedData;

    // Устанавливаем callback-функцию перед стартом парсинга.
    void setStartCallback(sCallBack cb);

    // Устанавливаем callback-функцию после окончания парсинга.
    void setEndCallback(sCallBack cb);

    // Устанавливаем callback-функцию для обработки токенов чисел.
    void setDigitTokenCallback(sCallBack cb);

    // Устанавливаем callback-функцию для обработки токенов строк.
    void setStringTokenCallback(sCallBack cb);

    void parse(const std::string & str);
private:
    sCallBack startCallback_;
    sCallBack endCallback_;
    sCallBack digitTokenCallback_;
    sCallBack stringTokenCallback_;

    static bool isDigitToken(std::string token);
};