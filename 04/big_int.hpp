#include <iostream>
#include <string>
#include <cmath>


class BigInt
{
public:
    BigInt();
    BigInt(int32_t i_num);
    BigInt(std::string s_num);
    BigInt(int32_t* ptr, size_t size);
    ~BigInt();
    BigInt& operator = (const int32_t& i_num); // конструктор через оператор присваивания

    BigInt(const BigInt& copied);
    BigInt& operator = (const BigInt& copied);
    BigInt(BigInt&& moved);
    BigInt& operator = (BigInt&& moved);
    

    BigInt& operator - ();

    bool operator < (const BigInt& rhs) const;
    bool operator == (const BigInt& rhs) const;
    bool operator > (const BigInt& rhs) const;
    bool operator <= (const BigInt& rhs) const;
    bool operator != (const BigInt& rhs) const;
    bool operator >= (const BigInt& rhs) const;

    BigInt operator + (const BigInt& other) const;
    BigInt operator + (const int32_t& other) const;

    BigInt operator - (const BigInt& other) const;
    BigInt operator - (const int32_t& other) const;

    BigInt operator * (const BigInt& other) const;
    BigInt operator * (const int32_t& other) const;

    std::string to_string() const;
    void show_debug() const;
private:
    int32_t* digits; // храним 123, как {3, 2, 1}
    size_t size_digits = 0;
    bool negative = false;
    const int32_t base = 10;
};

std::ostream& operator << (std::ostream& os, const BigInt& bigInt);