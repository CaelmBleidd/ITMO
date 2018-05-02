//
// Created by CaelmBleidd on 02.04.2018.
//

#include "BigInteger.h"
#include <cmath>
#include <vector>
#include <string>

const uint64_t base = (uint64_t) pow(10, 19);

BigInteger::BigInteger(int64_t value) {
    if (abs(value) < base) {
        sign = value;
        bits.clear();
    } else {
        bits.push_back((uint64_t) abs(value));
        sign = signbit(sign) ? -1 : 1;
    }
}

BigInteger::BigInteger(const BigInteger &bigInteger) {
    sign = bigInteger.sign;
    bits = bigInteger.bits;
}

BigInteger::BigInteger(BigInteger &&bigInteger) noexcept {
    std::vector<uint64_t>().swap(bits);
    sign = bigInteger.sign;
    bits = std::move(bigInteger.bits);
}

BigInteger &BigInteger::operator=(const BigInteger &bigInteger) {
    sign = bigInteger.sign;
    std::vector<uint64_t>().swap(bits);
    for (auto i: bigInteger.bits) {
        bits.push_back(i);
    }
    return *this;
}

BigInteger BigInteger::operator+(const BigInteger &bigInteger) const {
    BigInteger result(*this);
    result += bigInteger;
    return result;
}

BigInteger &BigInteger::operator+=(const BigInteger &bigInteger) {
    bool second_empty = false;
    std::vector<uint64_t> second_bits;
    if (bigInteger.sign == 0) {
    } else if (sign == 0) {
        *this = bigInteger;
    } else if (bigInteger.bits.empty() && bits.empty()) {
        auto tmp = (uint64_t) abs((sign + bigInteger.sign));
        if (tmp < base / 2 - 1) {
            sign = sign + bigInteger.sign;
        } else {
            if (sign > 0 && bigInteger.sign > 0) {
                sign = 1;
                bits.push_back(tmp);
            } else if (sign < 0 && bigInteger.sign < 0) {
                sign = -1;
                bits.push_back(tmp);
            }
        }
    } else {
        if (bits.empty()) {
            bits.push_back((uint64_t) abs((sign)));
            sign = signbit(sign) ? -1 : 1;
        } else if (bigInteger.bits.empty()) {
            second_empty = true;
            second_bits.push_back((uint64_t) abs(bigInteger.sign));
        }
        if ((sign > 0 && bigInteger.sign > 0) || (sign < 0 && bigInteger.sign < 0)) {
            bits = second_empty ? add(bits, second_bits) : add(bits, bigInteger.bits);
        } else {
            int8_t cmp = second_empty ? compare(second_bits) : compare(bigInteger.bits);
            if (cmp == 0) {
                bits.clear();
                sign = 0;
            } else {
                if (second_empty) {
                    bits = cmp > 0 ? subtract(bits, second_bits) : subtract(second_bits, bits);
                } else {
                    bits = cmp > 0 ? subtract(bits, bigInteger.bits) : subtract(bigInteger.bits, bits);

                }
                sign = cmp > 0 ? sign : bigInteger.sign;
                if (bits.size() == 1 && bits[0] < base / 2 - 1) {
                    sign = sign * (int64_t) bits[0];
                    bits.clear();
                }
            }
        }
    }
    return *this;
}

BigInteger BigInteger::operator-(const BigInteger &bigInteger) const {
    BigInteger result(*this);
    result -= bigInteger;
    return result;
}

BigInteger &BigInteger::operator-=(const BigInteger &bigInteger) {
    if (sign == 0) {
        *this = bigInteger;
        sign = -sign;
    } else if (bigInteger.sign == 0) {
    } else {
        BigInteger operand(bigInteger);
        operand.sign = -operand.sign;
        *this += operand;
    }
    return *this;
}

std::vector<uint64_t>
BigInteger::add(std::vector<uint64_t> first_number, std::vector<uint64_t> second_number) const {
    uint64_t carry = 0;
    for (size_t i = 0; i < std::max(first_number.size(), second_number.size()) || carry; ++i) {
        if (i == first_number.size())
            first_number.push_back(0);
        if (UINT64_MAX - carry - (i < second_number.size() ? second_number[i] : 0) < first_number[i]) {
            first_number[i] = (i < second_number.size() ? second_number[i] : 0) + carry - (base - first_number[i]);
            carry = 1;
        } else {
            first_number[i] += carry + (i < second_number.size() ? second_number[i] : 0);
            carry = first_number[i] >= base ? 1 : 0;
            if (carry)
                first_number[i] -= base;
        }
    }
    return first_number;
}


std::vector<uint64_t>
BigInteger::subtract(std::vector<uint64_t> first_number, std::vector<uint64_t> second_number) const {
    uint64_t carry = 0;
    for (size_t i = 0; i < second_number.size() || carry; ++i) {
        if (first_number[i] >= carry + (i < second_number.size() ? second_number[i] : 0)) {
            first_number[i] -= carry + (i < second_number.size() ? second_number[i] : 0);
            carry = 0;
        } else {
            uint64_t tmp = carry + (second_number.size() > i ? second_number[i] : 0) - first_number[i];
            carry = 1;
            first_number[i] = base;
            first_number[i] -= tmp;
        }
    }

    while (first_number.size() > 1 && first_number.back() == 0)
        first_number.pop_back();
    return first_number;
}


std::ostream &operator<<(std::ostream &stream, const BigInteger &bigInteger) {
    if (bigInteger.bits.empty()) {
        std::cout << bigInteger.sign;
    } else {
        if (bigInteger.sign == -1) {
            std::cout << "-";
        }
        std::cout << bigInteger.bits[bigInteger.bits.size() - 1];
        for (int64_t i = (int64_t) bigInteger.bits.size() - 2; i >= 0; --i) {
            printf("%019llu", bigInteger.bits[i]);
        }
    }
    return stream;
}

std::istream &operator>>(std::istream &stream, BigInteger &bigInteger) {
    bigInteger.sign = 0;
    std::vector<uint64_t>().swap(bigInteger.bits);
    std::string s;
    stream >> s;
    bool is_small = false;
    if (!s.empty()) {
        if (s[0] == '-') {
            if (s.substr(1).size() <= 19 && std::stoull(s.substr(1)) < base / 2) {
                bigInteger.sign = std::stoll(s);
                is_small = true;
            } else {
                bigInteger.sign = -1;
                s = s.substr(1);
            }
        } else {
            if (s.size() <= 19 && std::stoull(s) < base / 2) {
                bigInteger.sign = std::stoll(s);
                is_small = true;
            } else {
                bigInteger.sign = 1;
            }
        }
        if (!is_small) {
            for (auto i = (int64_t) s.size(); i > 0; i -= 19) {
                if (i < 19) {
                    bigInteger.bits.push_back(stoull(s.substr(0, i)));
                } else {
                    bigInteger.bits.push_back(stoull(s.substr(i - 19, 19)));
                }
            }
        }
    } else {
        bigInteger.bits.clear();
        bigInteger.sign = 0;
    }
    return stream;
}

int8_t BigInteger::compare(std::vector<uint64_t> bits2) {
    int8_t cmp = 0;
    if (bits.size() < bits2.size()) {
        cmp = -1;
    } else if (bits.size() > bits2.size()) {
        cmp = 1;
    } else {
        for (int64_t i = (int64_t) bits.size() - 1; i >= 0; --i) {
            if (bits[i] > bits2[i]) {
                cmp = 1;
                break;
            } else if (bits[i] < bits2[i]) {
                cmp = -1;
                break;
            }
        }
    }
    return cmp;
}

bool BigInteger::operator==(const BigInteger &bigInteger) {
    int8_t cmp = compare(bigInteger.bits);
    return cmp == 0;
}


BigInteger::~BigInteger() = default;

