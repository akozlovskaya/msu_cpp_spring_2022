#include "BigInt.hpp"


BigInt::BigInt() : size(0), cap(0), data(nullptr), negative(false)
{}

BigInt::BigInt(const std::string& str)
    : size(0), cap(0), data(nullptr), negative(false)
{
    if (!str.empty()) {
        negative = str[0] == '-';
        int32_t shift = negative ? 1 : 0;
        cap = str.size() - shift;
        size = cap;
        data = new short[size];
        for (size_t i = shift; i < str.length(); i++) {
            if (!isdigit(str[i])) {
                if (data != nullptr) delete []data;
                throw std::invalid_argument{"String contains more than just digits"};
            }
            data[size - (i - shift + 1)] = str[i] - '0';
      }
    }
    remove_zeros();
}

BigInt::BigInt(int32_t num)
{
    negative = num < 0;
    data = nullptr;
    size = 0, cap = 0;
    if (negative) {
        num = -num;
    }
    while (num > 0) {
        push_back(num % 10);
        num /= 10;
    }
}

BigInt::BigInt(const BigInt &src)
        : size(src.size), cap(src.cap), negative(src.negative)
{
    data = new short[cap];
    memcpy(data, src.data, size * sizeof(data[0]));
}

BigInt&
BigInt::operator=(const BigInt &src)
{
    if (cap) delete []data;
    cap = src.cap;
    size = src.size;
    negative = src.negative;
    if (cap) {
        data = new short[cap];
        memcpy(data, src.data, size * sizeof(data[0]));
    } else { data = nullptr; }
    return *this;
}

BigInt&
BigInt::operator=(int32_t num)
{
    if (cap) delete []data;
    negative = num < 0;
    data = nullptr;
    size = 0, cap = 0;
    if (negative) {
        num = -num;
    }
    while (num > 0) {
        push_back(num % 10);
        num /= 10;
    }
    return *this;
}

BigInt::~BigInt()
{
   if (data != nullptr) {
        delete []data;
   }
}

std::ostream&
operator<<(std::ostream &out, const BigInt &bigint)
{
    if (bigint.size == 0) {
        out << '0';
        return out;
    }

    if (bigint.negative) {
        out << '-';
    }
    for (int32_t i = bigint.size - 1; i >= 0 ; --i) {
        out << bigint.data[i];
    }
    return out;
}

void
BigInt::push_back(int32_t digit)
{
    while (size + 1 > cap) {
        cap = cap == 0 ? 2 : cap * 2;
        short *tmp = new short[cap];
        if (data != nullptr) {
            memcpy(tmp, data, size * sizeof(data[0]));
            delete []data;
        }
        data = tmp;
    }
    data[size++] = digit;
}

void
BigInt::remove_zeros()
{
    size_t first_sign = 0;
    for (size_t i = size; i > 0; --i) {
        if (data[i-1] != 0) {
            first_sign = i;
            break;
        }
    }
    if (first_sign != size) {
        size = first_sign;
        cap = size;
        short *tmp = new short[cap];
        if (data != nullptr) {
            memcpy(tmp, data, size * sizeof(data[0]));
            delete []data;
        }
        data = tmp;
    }
}

bool
BigInt::operator==(const BigInt &bigint) const
{
    if (bigint.negative != negative || bigint.size != size) {
        return false;
    }

    for (size_t i = 0; i < size; ++i) {
        if (bigint.data[i] != data[i]) {
            return false;
        }
    }
    return true;
}

bool
BigInt::operator!=(const BigInt &bigint) const
{
    return !(*this == bigint);
}

bool
BigInt::unsigned_greater(const BigInt &bigint) const
{
    if (bigint.size > size) {
        return false;
    }
    if (bigint.size < size) {
        return true;
    }
    for (int32_t i = size - 1; i >= 0; --i) {
        if (bigint.data[i] < data[i]) {
            return true;
        }
        if (bigint.data[i] > data[i]) {
            return false;
        }
    }
    return false;
}

bool
BigInt::operator>(const BigInt &bigint) const
{
    if (bigint.negative != negative) {
        return bigint.negative;
    }
    return (bigint != *this) && (unsigned_greater(bigint) != negative);
}

bool
BigInt::unsigned_less(const BigInt &bigint) const
{
    if (bigint.size > size) {
        return true;
    }
    if (bigint.size < size) {
        return false;
    }
    for (int32_t i = size - 1; i >= 0; --i) {
        if (bigint.data[i] < data[i]) {
            return false;
        }
        if (bigint.data[i] > data[i]) {
            return true;
        }
    }
    return false;
}

bool
BigInt::operator<(const BigInt &bigint) const
{
    if (bigint.negative != negative) {
        return negative;
    }
    return (bigint != *this) && (unsigned_less(bigint) != negative);
}

bool
BigInt::operator<=(const BigInt &bigint) const
{
    return (*this == bigint) || (*this < bigint);
}

bool
BigInt::operator>=(const BigInt &bigint) const
{
    return (*this == bigint) || (*this > bigint);
}

BigInt
BigInt::unsigned_sum(const BigInt &bigint) const
{
    BigInt res;
    const BigInt& min_num = unsigned_greater(bigint.size) ? bigint : *this;
    const BigInt& max_num = unsigned_greater(bigint.size) ? *this : bigint;
    int32_t add = 0;
    int32_t sum;
    for (size_t i = 0; i < min_num.size; ++i) {
        sum = bigint.data[i] + data[i] + add;
        res.push_back(sum % 10);
        add = sum/10;
    }
    for (size_t i = min_num.size; i < max_num.size; ++i) {
        sum = max_num.data[i] + add;
        res.push_back(sum % 10);
        add = sum/10;
    }
    if (add > 0) {
        res.push_back(add);
    }
    return res;
}

BigInt
BigInt::unsigned_diff(const BigInt &bigint) const
{
    BigInt diff;
    const BigInt& min_num = unsigned_greater(bigint) ? bigint : *this;
    const BigInt& max_num = unsigned_greater(bigint) ? *this : bigint;
    int32_t add = 0, d1 = 0, d2 = 0;

    for (size_t i = 0; i < min_num.size; ++i) {
        if (max_num.data[i] - d1 < min_num.data[i]) {
            add = 10;
            d2 = 1;
        }
        diff.push_back(max_num.data[i] - d1 + add - min_num.data[i]);
        add = 0;
        d1 = d2;
        d2 = 0;
    }

    for (size_t i = min_num.size; i < max_num.size; ++i) {
        if (max_num.data[i] - d1 < 0) {
            add = 10;
            d2 = 1;
        }
        diff.push_back(max_num.data[i] - d1 + add);
        add = 0;
        d1 = d2;
        d2 = 0;
    }

    diff.remove_zeros();
    return diff;
}

BigInt
BigInt::operator+(const BigInt &bigint) const
{
    BigInt res;
    if (negative == bigint.negative) {
        res = unsigned_sum(bigint);
        res.negative = negative;
    } else {
        res = unsigned_diff(bigint);
        res.negative = unsigned_greater(bigint) ? negative : bigint.negative;
    }
    return res;
}

BigInt
BigInt::operator-(const BigInt &bigint) const
{
    BigInt res;
    if (negative == bigint.negative) {
        res = unsigned_diff(bigint);
    } else {
        res = unsigned_sum(bigint);
    }
    res.negative = *this < bigint;
    return res;
}

BigInt
BigInt::operator-() const
{
    BigInt ret(*this);
    ret.negative = !negative;
    return ret;
}

BigInt
BigInt::operator*(const BigInt &bigint) const
{
    BigInt res = 0;

    const BigInt& min_num = unsigned_greater(bigint) ? bigint : *this;
    const BigInt& max_num = unsigned_greater(bigint) ? *this : bigint;

    if (min_num.size == 0) {
        return res;
    }

    BigInt term;
    for (size_t j = 0; j < min_num.size; ++j) {
        term = 0;
        for (size_t k = 0; k < j; ++k) {
            term.push_back(0);
        }
        int32_t sum, add = 0;
        for (size_t i = 0; i < max_num.size; ++i) {
            sum = max_num.data[i]*min_num.data[j] + add;
            term.push_back(sum % 10);
            add = sum / 10;
        }
        if (add > 0) {
            term.push_back(add);
        }
        term.remove_zeros();
        res = res + term;
    }
    res.negative = negative != bigint.negative;
    return res;
}
