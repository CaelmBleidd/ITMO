//
// Created by CaelmBleidd on 02.04.2018.
//

#pragma once

#include <iostream>
#include <vector>
#include <cmath>

template<typename T, size_t Base = std::numeric_limits<T>::max()>
class BigInteger;

template<typename T, size_t Base>
class BigInteger{
public:
    explicit BigInteger(int64_t value = 0);
    explicit BigInteger(const std::string &);
    explicit BigInteger(const std::vector<T> &, const int64_t sign);
    template<typename NewT, size_t NewBase>
    explicit operator BigInteger<NewT, NewBase>();

    BigInteger(const BigInteger &);
    BigInteger(BigInteger &&) noexcept;

    ~BigInteger();

    size_t Size() const;
    std::string to_string(BigInteger &);
    T operator[](size_t id) const;

    BigInteger &operator=(const BigInteger &);
    bool operator<(const BigInteger&) const;
    bool operator>(const BigInteger&) const;
    bool operator<=(const BigInteger&) const;
    bool operator>=(const BigInteger&) const;
    bool operator==(const BigInteger&) const;
    bool operator!=(const BigInteger&) const;
    BigInteger abs() const;

    BigInteger &operator+=(const BigInteger &);
    BigInteger operator+(const BigInteger &) const;
    BigInteger &operator-=(const BigInteger &);
    BigInteger operator-(const BigInteger &) const;
    BigInteger &operator*=(const BigInteger&);
    BigInteger &operator*(const BigInteger&) const;
    BigInteger &operator/=(const BigInteger&);
    BigInteger &operator/(const BigInteger&) const;

    BigInteger operator*(int64_t) const;
    BigInteger operator/(int64_t) const;
    BigInteger operator%=(int64_t) const;
    BigInteger operator%(int64_t) const;
    BigInteger operator-() const;
    BigInteger operator+() const;

private:
    void trim();

    template<typename T, size_t Base>
    friend std::ostream &operator<<(std::ostream &, const BigInteger<T, Base> &);
    template<typename T, size_t Base>
    friend std::istream &operator>>(std::istream &, BigInteger<T, Base> &);

    BigInteger & add(BigInteger &) const;
    BigInteger & subtract(const BigInteger &);

    int64_t sign;
    std::vector<T> bits;
    size_t size_of_number;
    const size_t num_of_bits = (size_t) std::ceil(log2(Base));
    const size_t num_of_blocks = sizeof(T) * 8 / num_of_bits;
};
