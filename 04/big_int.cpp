#include "big_int.hpp"


BigInt::BigInt()
{
    digits = new int32_t[1];
    digits[0] = 0;
    size_digits = 1;
    negative = false;
}


BigInt::BigInt(int32_t i_num)
{
    if (i_num < 0)
        negative = true;
    
    int32_t tmp_num = abs(i_num);
    while (tmp_num) {
        tmp_num /= base;
        size_digits++;
    }

    digits = new int32_t[size_digits];
    tmp_num = abs(i_num);
    for (size_t i=0; i<size_digits; ++i) {
        digits[i] = tmp_num % base;
        tmp_num /= base;
    }
}


BigInt::BigInt(std::string s_num)
{   
    size_digits = s_num.length();
    if (s_num[0] == '-') {
        size_digits--;
        negative = true;
    }

    digits = new int32_t[size_digits];
    
    for (size_t i=0; i<size_digits; ++i) {
        digits[i] = s_num[s_num.length()-1-i] - '0';
    }
}


BigInt::BigInt(int32_t* ptr, size_t size)
{
    digits = ptr;
    size_digits = size;
}


BigInt::~BigInt()
{
    if (digits != nullptr)
        delete[] digits;
}


BigInt& BigInt::operator = (const int32_t& i_num)
{
    if (i_num < 0)
        negative = true;
    
    int32_t tmp_num = i_num;
    while (tmp_num) {
        tmp_num /= base;
        size_digits++;
    }

    digits = new int32_t[size_digits];
    tmp_num = i_num;
    for (size_t i=0; i<size_digits; ++i) {
        digits[i] = tmp_num % base;
        tmp_num /= base;
    }

    return *this;
}


BigInt::BigInt(const BigInt& copied)
{
    this->size_digits = copied.size_digits;
    this->negative = copied.negative;
    this->digits = new int32_t[this->size_digits];
    for (size_t i=0; i<this->size_digits; ++i) {
        this->digits[i] = copied.digits[i];
    }
}


BigInt& BigInt::operator = (const BigInt& copied)
{
    this->size_digits = copied.size_digits;
    this->negative = copied.negative;
    this->digits = new int32_t[this->size_digits];
    for (size_t i=0; i<this->size_digits; ++i) {
        this->digits[i] = copied.digits[i];
    }

    return *this;
}


BigInt::BigInt(BigInt&& moved)
{
    this->size_digits = moved.size_digits;
    this->negative = moved.negative;
    this->digits = new int32_t[this->size_digits];
    for (size_t i=0; i<this->size_digits; ++i) {
        this->digits[i] = moved.digits[i];
    }

    moved.size_digits = 0;
    moved.negative = false;
    delete[] moved.digits;
    moved.digits = nullptr;
}


BigInt& BigInt::operator = (BigInt&& moved)
{
    this->size_digits = moved.size_digits;
    this->negative = moved.negative;
    this->digits = new int32_t[this->size_digits];
    for (size_t i=0; i<this->size_digits; ++i) {
        this->digits[i] = moved.digits[i];
    }
    moved.size_digits = 0;
    moved.negative = false;
    delete[] moved.digits;
    moved.digits = nullptr;

    return *this;
}


BigInt BigInt::operator - ()
{
    BigInt result = BigInt(*this);
    result.negative = !(result.negative);
    return result;
}


bool BigInt::operator < (const BigInt& rhs) const
{
    if (this->negative != rhs.negative) {
        if (!rhs.negative) {
            return true;
        } else {
            return false;
        }
    }

    if (this->negative) {
        if (this->size_digits > rhs.size_digits) {
            return true;
        } else if (this->size_digits == rhs.size_digits) {
            for (size_t i=0; i<this->size_digits; ++i) {
                if (this->digits[this->size_digits-1-i] > rhs.digits[this->size_digits-1-i]) {
                    return true;
                } else if (this->digits[this->size_digits-1-i] < rhs.digits[this->size_digits-1-i]) {
                    return false;
                }
            }
            return false;
        } else {
            return false;
        }
    }

    if (this->size_digits > rhs.size_digits) {
        return false;
    } else if (this->size_digits == rhs.size_digits) {
        for (size_t i=0; i<this->size_digits; ++i) {
            if (this->digits[this->size_digits-1-i] < rhs.digits[this->size_digits-1-i]) {
                return true;
            } else if (this->digits[this->size_digits-1-i] < rhs.digits[this->size_digits-1-i]) {
                return false;
            }
        }
        return false;
    } else {
        return true;
    }
}


bool BigInt::operator > (const BigInt& rhs) const
{
    if (this->negative != rhs.negative) {
        if (!rhs.negative) {
            return false;
        } else {
            return true;
        }
    }

    if (this->negative) {
        if (this->size_digits > rhs.size_digits) {
            return false;
        } else if (this->size_digits == rhs.size_digits) {
            for (size_t i=0; i<this->size_digits; ++i) {
                if (this->digits[this->size_digits-1-i] > rhs.digits[this->size_digits-1-i]) {
                    return false;
                } else if (this->digits[this->size_digits-1-i] < rhs.digits[this->size_digits-1-i]) {
                    return true;
                }
            }
            return false;
        } else {
            return true;
        }
    }

    if (this->size_digits > rhs.size_digits) {
        return true;
    } else if (this->size_digits == rhs.size_digits) {
        for (size_t i=0; i<this->size_digits; ++i) {
            if (this->digits[this->size_digits-1-i] > rhs.digits[this->size_digits-1-i]) {
                return true;
            } else if (this->digits[this->size_digits-1-i] < rhs.digits[this->size_digits-1-i]) {
                return false;
            }
        }
        return false;
    } else {
        return false;
    }
}


bool BigInt::operator == (const BigInt& rhs) const
{
    if (this->negative != rhs.negative)
        return false;

    if (this->size_digits != rhs.size_digits)
        return false;

    for (size_t i=0; i<this->size_digits; ++i) {
        if (this->digits[this->size_digits-i-1] != rhs.digits[this->size_digits-i-1])
            return false;
    }

    return true;
}


bool BigInt::operator <= (const BigInt& rhs) const
{
    return !((*this) > rhs);
}


bool BigInt::operator >= (const BigInt& rhs) const
{
    return !((*this) < rhs);
}


bool BigInt::operator != (const BigInt& rhs) const
{
    return !((*this) == rhs);
}


void resizePtrDelZeros(int32_t* ptr, size_t& size)
{
    size_t cntZeros = 0;
    for (size_t i=0; i<size; ++i) { 
        if (ptr[size-1-i] != 0) {
            break;
        }
        cntZeros++;
    }
    size -= cntZeros;

    int32_t* ptr_new = new int32_t[size];
    for (size_t i=0; i<size; ++i) {
        ptr_new[i] = ptr[i];
    }
    ptr = ptr_new;
}


BigInt BigInt::operator + (const BigInt& other) const
{
    if (this->negative && other.negative) {
        return -((-BigInt(*this)) + (-BigInt(other)));
    } else if (other.negative) {
        return ((*this) - (-BigInt(other)));
    } else if (this->negative) {
        return other - (-BigInt(*this));
    }

    if ((*this) < other) {
        return other + (*this);
    }

    size_t size_new = std::max(this->size_digits, other.size_digits) + 1;
    int32_t* digits_new = new int32_t[size_new];
    for (size_t i=0; i<size_new; ++i)
        digits_new[i] = 0;

    int32_t carry = 0;
    for (size_t i=0; i<other.size_digits; ++i) {
        digits_new[i] = this->digits[i] + other.digits[i] + carry;
        carry = digits_new[i] / this->base;
        digits_new[i] = digits_new[i] % this->base;
    }
    for (size_t i=other.size_digits; i<size_new-1; ++i) {
        digits_new[i] += this->digits[i] + carry;
        carry = digits_new[i] / this->base;
        digits_new[i] = digits_new[i] % this->base;
    }
    digits_new[size_new-1] += carry;

    resizePtrDelZeros(digits_new, size_new);
    return BigInt(digits_new, size_new);
}


BigInt BigInt::operator + (const int32_t& other) const
{
    return (*this) + BigInt(other);
}


BigInt BigInt::operator - (const BigInt& other) const
{
    if (this->negative && other.negative) {
        return -((-BigInt(*this)) - (-BigInt(other)));
    } else if (other.negative) {
        return (*this) + (-BigInt(other));
    } else if (this->negative) {
        return -((-BigInt(*this)) + BigInt(other));
    }

    if ((*this) < other) {
        return -(other - (*this));
    }

    size_t size_new = std::max(this->size_digits, other.size_digits) + 1;
    int32_t* digits_new = new int32_t[size_new];
    for (size_t i=0; i<size_new; ++i)
        digits_new[i] = 0;

    int32_t cur_diff = 0;
    for (size_t i=0; i<other.size_digits; ++i) {
        cur_diff = this->digits[i] - other.digits[i];
        if (cur_diff < 0) {
            cur_diff += this->base;
            digits_new[i+1] -= 1;
        }
        digits_new[i] += cur_diff;
    }
    for (size_t i=other.size_digits; i<size_new-1; ++i) {
        digits_new[i] += this->digits[i]; 
    }

    resizePtrDelZeros(digits_new, size_new);
    return BigInt(digits_new, size_new);
}


BigInt BigInt::operator - (const int32_t& other) const
{
    return (*this) - BigInt(other);
}


BigInt BigInt::operator * (const BigInt& other) const
{
    bool negative_new = false;
    if (this->negative != other.negative)
        negative_new = true;
    
    size_t size_new = this->size_digits + other.size_digits;
    int32_t* digits_new = new int32_t[size_new];
    for (size_t i=0; i<size_new; ++i)
        digits_new[i] = 0;

    for (size_t i=0; i<this->size_digits; ++i) {
        for (size_t j=0; j<other.size_digits; ++j) {
            digits_new[i+j] += this->digits[i] * other.digits[j];
        }
    }

    int32_t carry = 0;
    for (size_t i=0; i<size_new-1; ++i) {
        carry = digits_new[i] / this->base;
        digits_new[i+1] += carry;
        digits_new[i] %= this->base;
    }

    resizePtrDelZeros(digits_new, size_new);

    BigInt result = BigInt(digits_new, size_new);
    result.negative = negative_new;

    return result;
}


BigInt BigInt::operator * (const int32_t& other) const
{
    return (*this) * BigInt(other);
}


std::string BigInt::to_string() const
{
    std::string result = "";
    for (size_t i=0; i < this->size_digits; ++i) {
        result = std::to_string(this->digits[i]) + result;
    }
    if (this->negative)
        result = "-" + result;

    return result;
}


std::ostream& operator << (std::ostream& os, const BigInt& bigInt)
{
    os << bigInt.to_string();
    return os;
}


void BigInt::show_debug() const
{
    std::cout << "size_digits = " << this->size_digits << std::endl
              << "negative = " << this->negative << std::endl;
    std::cout << "Number is:" << std::endl;
    if (this->negative)
        std::cout << "-";

    for (size_t i=0; i<this->size_digits; ++i) {
        std::cout << digits[this->size_digits-1-i] << "";
    }
    std::cout << std::endl;
}