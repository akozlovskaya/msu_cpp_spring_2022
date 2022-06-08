#pragma once

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>


class BigInt {

private:
    size_t size;
    size_t cap;
    short *data;
    bool negative;

    // assign digit to the right of a number
    void push_back(int32_t);
    // remove leading zeros
    void remove_zeros();
    // methods for absolute values of numbers
    bool unsigned_greater(const BigInt &) const;
    bool unsigned_less(const BigInt &) const;
    BigInt unsigned_diff(const BigInt &) const;
    BigInt unsigned_sum(const BigInt &) const;

public:
    BigInt();
    BigInt(const std::string&);
    BigInt(BigInt&&);
    BigInt(int32_t);
    BigInt(const BigInt &);
    BigInt& operator=(const BigInt &);
    BigInt& operator=(int32_t);
    BigInt& operator=(BigInt&& );
    ~BigInt();

    friend std::ostream& operator<<(std::ostream &, const BigInt &);

    bool operator==(const BigInt &) const;
    bool operator!=(const BigInt &) const;
    bool operator<(const BigInt &) const;
    bool operator>(const BigInt &) const;
    bool operator<=(const BigInt &) const;
    bool operator>=(const BigInt &) const;

    BigInt operator+(const BigInt &) const;
    BigInt operator-(const BigInt &) const;
    BigInt operator-() const;
    BigInt operator*(const BigInt &) const;
};