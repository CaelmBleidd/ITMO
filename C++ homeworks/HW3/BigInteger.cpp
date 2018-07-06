//
// Created by CaelmBleidd on 02.04.2018.
//

#include "BigInteger.h"
#include <cmath>
#include <vector>
#include <string>

const uint64_t DEFAULT_BASE = (uint64_t) std::pow(10, 19);
const uint64_t BASE_DIGITS = 19;

template<typename T, size_t Base>
BigInteger<T, Base>::BigInteger(int64_t value) {
    sign = value;
    bits.clear();
}

template<typename T, size_t Base>
BigInteger<T, Base>::BigInteger(const std::string &line) {
    size_t pos = 0;
    sign = 1;
    bits.clear();

    std::vector<uint64_t> data;

    while (pos < line.length() && (line[pos] == '-' || line[pos] == '+') {
        if (line[pos] == '-')
            sign = -sign;
        ++pos;
    }

    for (size_t i = line.length() - 1; i >= pos; i -= 19) {
        uint64_t x = 0;
        for (size_t j = std::max(pos, i - BASE_DIGITS + 1); j <= i; ++j)
            x = x * 10 + line[j] - '0';
        bits.push_back(x);
    }
    if (bits.size() == 1 && bits[0] < INT64_MAX) {
        sign *= bits[0];
        bits.clear();
    }
}

template<typename T, size_t Base>
BigInteger<T, Base>::BigInteger(const std::vector<T> &bits, const int64_t sign) {
    this->sign = sign;
    this->bits = bits;
}

template<typename T, size_t Base>
template<typename NewT, size_t NewBase>
BigInteger<T, Base>::operator BigInteger<NewT, NewBase>() {



    return BigInteger<NewT, NewBase>();
}

template<typename T, size_t Base>
BigInteger<T, Base>::BigInteger(const BigInteger &bigInteger) {
    sign = bigInteger.sign;
    bits = bigInteger.bits;
}

template<typename T, size_t Base>
BigInteger<T, Base>::BigInteger(BigInteger &&bigInteger) noexcept {
    sign = bigInteger.sign;
    bits = std::move(bigInteger.bits);
}

template<typename T, size_t Base>
size_t BigInteger<T, Base>::Size() const {
    return 0;
}

template<typename T, size_t Base>
std::string BigInteger<T, Base>::to_string(BigInteger &) {
    return std::string();
}

template<typename T, size_t Base>
T BigInteger<T, Base>::operator[](size_t id) const {
    return nullptr;
}

template<typename T, size_t Base>
BigInteger &BigInteger<T, Base>::operator=(const BigInteger &) {
    return <#initializer#>;
}

template<typename T, size_t Base>
bool BigInteger<T, Base>::operator<(const BigInteger &) const {
    return false;
}

template<typename T, size_t Base>
bool BigInteger<T, Base>::operator>(const BigInteger &) const {
    return false;
}

template<typename T, size_t Base>
bool BigInteger<T, Base>::operator<=(const BigInteger &) const {
    return false;
}

template<typename T, size_t Base>
bool BigInteger<T, Base>::operator>=(const BigInteger &) const {
    return false;
}

template<typename T, size_t Base>
bool BigInteger<T, Base>::operator==(const BigInteger &) const {
    return false;
}

template<typename T, size_t Base>
bool BigInteger<T, Base>::operator!=(const BigInteger &) const {
    return false;
}

template<typename T, size_t Base>
BigInteger BigInteger<T, Base>::abs() const {
    return BigInteger();
}

template<typename T, size_t Base>
BigInteger &BigInteger<T, Base>::operator+=(const BigInteger &) {
    return <#initializer#>;
}

template<typename T, size_t Base>
BigInteger BigInteger<T, Base>::operator+(const BigInteger &) const {
    return BigInteger();
}

template<typename T, size_t Base>
BigInteger &BigInteger<T, Base>::operator-=(const BigInteger &) {
    return <#initializer#>;
}

template<typename T, size_t Base>
BigInteger BigInteger<T, Base>::operator-(const BigInteger &) const {
    return BigInteger();
}

template<typename T, size_t Base>
BigInteger &BigInteger<T, Base>::operator*=(const BigInteger &) {
    return <#initializer#>;
}

template<typename T, size_t Base>
BigInteger &BigInteger<T, Base>::operator*(const BigInteger &) const {
    return <#initializer#>;
}

template<typename T, size_t Base>
BigInteger &BigInteger<T, Base>::operator/=(const BigInteger &) {
    return <#initializer#>;
}

template<typename T, size_t Base>
BigInteger &BigInteger<T, Base>::operator/(const BigInteger &) const {
    return <#initializer#>;
}

template<typename T, size_t Base>
BigInteger BigInteger<T, Base>::operator*(int64_t) const {
    return BigInteger();
}

template<typename T, size_t Base>
BigInteger BigInteger<T, Base>::operator/(int64_t) const {
    return BigInteger();
}

template<typename T, size_t Base>
BigInteger BigInteger<T, Base>::operator%=(int64_t) const {
    return BigInteger();
}

template<typename T, size_t Base>
BigInteger BigInteger<T, Base>::operator%(int64_t) const {
    return BigInteger();
}

template<typename T, size_t Base>
BigInteger BigInteger<T, Base>::operator-() const {
    return BigInteger();
}

template<typename T, size_t Base>
BigInteger BigInteger<T, Base>::operator+() const {
    return BigInteger();
}

template<typename T, size_t Base>
void BigInteger<T, Base>::trim() {

}

template<typename T, size_t Base>
std::ostream &operator<<(std::ostream &stream, const BigInteger<T, Base> &bigInteger) {
    BigInteger<uint64_t, DEFAULT_BASE> tmp_bigInteger = static_cast<BigInteger<uint64_t, DEFAULT_BASE>> (bigInteger);
    return stream;
}

template<typename T, size_t Base>
std::istream &operator>>(std::istream &stream, BigInteger<T, Base> &bigInteger) {
    std::string line;
    std::cin >> line;
    bigInteger = static_cast<BigInteger<T, Base>> (BigInteger<uint64_t, DEFAULT_BASE>(line));
    return stream;
}

template<typename T, size_t Base>
BigInteger &BigInteger<T, Base>::add(BigInteger &) const {
    return <#initializer#>;
}

template<typename T, size_t Base>
BigInteger &BigInteger<T, Base>::subtract(const BigInteger &) {
    return <#initializer#>;
}

template<typename T, size_t Base>
BigInteger<T, Base>::~BigInteger() = default;


