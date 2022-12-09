#include <iostream>
#include <gtest/gtest.h>

#include "tokenParser.hpp"

class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};

TEST(TestTokenParser, test_someCBTransforms)
{
    // Тестовые данные
    std::string test_string = "heLLO my\nname  is Dmytrij\ni am 22 y.o";
    
    // Набор из callback'ов
    auto ucTransformer = [](std::string & str) {
        std::string resultStr = "";
        for (size_t i=0; i<str.length(); ++i)
            resultStr += toupper(str[i]);
        str = resultStr;
    };
    auto noMLetterTransformer = [](std::string & str) {
        std::string resultStr = "";
        for (size_t i=0; i<str.length(); ++i) {
            if ( str[i] != 'm' && str[i] != 'M' )
                resultStr += str[i];
        }
        str = resultStr;
    };
    auto mod7DigitStringTransaformer = [](std::string & str) {
        uint64_t ustr = std::stoull(str);
        str = std::to_string(ustr % 7);
    };
    auto wrapStringTransformer = [](std::string & str) {
        str = "<<<" + str + ">>>";
    };

    // Зона тестирования
    {
        TokenParser parser;
        std::string expectedStr = "<<<HELLO Y\nNAE  IS DYTRIJ\nI A 1 Y.O>>>";
        
        parser.setStartCallback(ucTransformer);
        parser.setDigitTokenCallback(mod7DigitStringTransaformer);
        parser.setStringTokenCallback(noMLetterTransformer);
        parser.setEndCallback(wrapStringTransformer);
        
        // вариант с обработкой потока через getline считаю излишним
        parser.parse(test_string);

        std::cout << "test_someCBTransforms" 
            << std::endl << "result :"
            << std::endl << parser.parsedData
            << std::endl;
        ASSERT_EQ( parser.parsedData, expectedStr);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}