//
// Created by CaelmBleidd on 02.04.2018.
//

#pragma once

#include <iostream>
#include <vector>

class BigInteger {
public:
    explicit BigInteger(int64_t value = 0);

    BigInteger(const BigInteger &);

    BigInteger(BigInteger &&) noexcept;

    ~BigInteger();

    BigInteger &operator=(const BigInteger &);

    BigInteger &operator+=(const BigInteger &);

    BigInteger operator+(const BigInteger &) const;

    BigInteger &operator-=(const BigInteger &);

    BigInteger operator-(const BigInteger &) const;

    bool operator==(const BigInteger &);

private:
    friend std::ostream &operator<<(std::ostream &, const BigInteger &);

    friend std::istream &operator>>(std::istream &, BigInteger &);

    int64_t sign;
    std::vector<uint64_t> bits;

    int8_t compare(std::vector<uint64_t> bits);

    std::vector<uint64_t> add(std::vector<uint64_t> number1, std::vector<uint64_t> number2) const;

    std::vector<uint64_t> subtract(std::vector<uint64_t> number1, std::vector<uint64_t> number2) const;


};

std::ostream &operator<<(std::ostream &, const BigInteger &);

std::istream &operator>>(std::istream &, BigInteger &);

