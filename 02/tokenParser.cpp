#include "tokenParser.hpp"

bool
TokenParser::isDigitToken(std::string token)
{
    for (size_t i=0; i < token.length(); ++i) {
        if ( !isdigit(token[i]) )
            return false;
    }

    uint64_t utoken = std::stoull(token);
    if ( token !=  std::to_string(utoken) )
        return false;

    return true;
}

void
TokenParser::setStartCallback(sCallBack cb)
{
    this->startCallback_ = cb;
}

void
TokenParser::setEndCallback(sCallBack cb)
{
    this->endCallback_ = cb;
}

void
TokenParser::setDigitTokenCallback(sCallBack cb)
{
    this->digitTokenCallback_ = cb;
}

void
TokenParser::setStringTokenCallback(sCallBack cb)
{
    this->stringTokenCallback_ = cb;
}

void
TokenParser::parse(const std::string & str)
{
    // Ссылка неизменяемая по сигнатуре метода из условия
    // поэтому делаю копию для обработки в callback'ах
    std::string localStr = str; 

    this->startCallback_(localStr);
    
    std::string resultStr = "";
    std::string token = "";
    size_t space_len = 0;

    for (size_t i = 0; i < localStr.length(); ++i) {
        
        // Это не пробельный символ, значит собираем токен
        // и выходим
        if ( !std::isspace(localStr[i]) ) {
            space_len = 0;
            token += localStr[i];
            if ( i != localStr.length()-1 ) // обработка конца строки
                continue;
        }

        // Встретили пробельный символ с учётом локали
        // считаем подряд идущий пробел
        space_len++;
        if ( space_len > 1 ) { // более одного пробела? 
            resultStr += localStr[i]; // просто сохраним
            continue; // и выходим
        }
        
        // Всретили ПЕРВЫЙ пробельный символ
        // значит токен готов, пора обработать
        if ( isDigitToken(token) ) {
            TokenParser::digitTokenCallback_(token);
        } else {
            TokenParser::stringTokenCallback_(token);
        }   

        // обработанный токен добавляем
        resultStr += token;
        token = "";

        
        // сохраняем пробельный символ
        if ( i != localStr.length()-1 || std::isspace(localStr[i]) )
            resultStr += localStr[i];
    }
    this->endCallback_(resultStr);
    this->parsedData = resultStr;
}