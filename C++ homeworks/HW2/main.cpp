#import <iostream>
#import "BigInteger.h"
#import <cmath>

int main() {
    std::freopen("input_int64_t.txt", "r", stdin);
    std::cout << "Все числа влезают в встроенные типы: ";
//    std::freopen("BigAndSmall.txt", "r", stdin);
//    std::cout << "Большое и маленькое в каждой паре: ";
//    std::freopen("input_bigInteger.txt", "r", stdin);
//    std::cout << "Все строки от 5 до 10000 символов: ";

    bool result = true;
    int64_t res1, res2, res3, res4;
    int64_t ares1, ares2, ares3, ares4;
    res1 = res2 = res3 = res4 = ares1 = ares2 = ares3 = ares4 = 0;
    while (std::cin) {
        std::string c;
        BigInteger operand;
        BigInteger first;
        BigInteger second;
        BigInteger expected;
        std::cin >> first >> c >> second >> c >> expected;

        //    std::cout << ++q << '\n';
        operand = first + second;
        if (!(operand == expected)) {
            std::cout << "Ожидалось: " << expected << ". Найдено: " << operand << ". Выражение: " << first << " + "
                      << second << '\n';
            ++ares1;
        } else {
            //         std::cout << "Успех!" << '\n';
            ++res1;
        }

        std::cin >> first >> c >> second >> c >> expected;
        operand = first - second;
        if (!(operand == expected)) {
            std::cout << "Ожидалось: " << expected << ". Найдено: " << operand << ". Выражение: " << first << " - "
                      << second << '\n';
            ++ares2;
        } else {
            //        std::cout << "Успех!" << '\n';
            ++res2;
        }

        std::cin >> first >> c >> second >> c >> expected;
        operand = first;
        operand += second;
        if (!(operand == expected)) {
            std::cout << "Ожидалось: " << expected << ". Найдено: " << operand << ". Выражение: " << first << " += "
                      << second << '\n';
            ++ares3;
        } else {
            //          std::cout << "Успех!" << '\n';
            ++res3;
        }

        std::cin >> first >> c >> second >> c >> expected;
        operand = first;
        operand -= second;
        if (!(operand == expected)) {
            std::cout << "Ожидалось: " << expected << ". Найдено: " << operand << ". Выражение: " << first << " -= "
                      << second << '\n';
            ++ares4;
        } else {
            //          std::cout << "Успех!" << '\n';
            ++res4;
        }

    }
    std::cout << '\n';

    std::cout << "Пройдено всего: " << res1 + res2 + res3 + res4 << ". Провалено: " << ares1 + ares2 + ares3 + ares4
              << '\n';
    std::cout << "+: Пройдено: " << res1 << ". Провалено: " << ares1 << '\n';
    std::cout << "-: Пройдено: " << res2 << ". Провалено: " << ares2 << '\n';
    std::cout << "+=: Пройдено: " << res3 << ". Провалено: " << ares3 << '\n';
    std::cout << "-=: Пройдено: " << res4 << ". Провалено: " << ares4 << '\n';
    std::cout << "==================================================================\n";

    std::fclose(stdin);

    BigInteger bigInt1(25);
    BigInteger bigInt2(20000);
    BigInteger bigInt3(std::move(bigInt2));
    BigInteger bigInt4(bigInt1);
    std::cout << bigInt1 << "\n";
    std::cout << bigInt2 << "\n";
    std::cout << bigInt3 << "\n";
    std::cout << bigInt1 - bigInt4 << "\n";
    std::cout << bigInt1 + bigInt4 << "\n";
    BigInteger bigInt6;
    std::cin >> bigInt6;
    BigInteger bigInt7(31);
    std::cout << (bigInt6 + bigInt7);
    return 0;
}

