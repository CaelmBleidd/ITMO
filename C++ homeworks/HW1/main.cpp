#include <iostream>
#include <stack>

bool is_number(std::string word) {
    for (char c: word)
        if (!isdigit(c))
            return false;
    return true;
}

void operation(std::stack<int> &stack, std::string &word, bool &is_error_exist, std::string &error) {
    int result = 0;
    if (word.size() != 1) {
        is_error_exist = true;
    } else {
        char sign = word[0];
        int second = stack.top();
        stack.pop();
        int first = stack.top();
        stack.pop();

        switch (sign) {
            case '+':
                result = first + second;
                break;
            case '-':
                result = first - second;
                break;
            case '/':
                result = first / second;
                break;
            case '*':
                result = first * second;
                break;
            default:
                is_error_exist = true;
        }
    }
    if (!is_error_exist) {
        stack.push(result);
    } else {
        error = "An unexpected sign \'" + word + "\'.";
    }
}


int main() {
    std::string word;
    std::stack<int> numbers;
    std::string error;
    bool is_error_exist = false;

    while (std::cin >> word && !is_error_exist) {
        if (is_number(word)) {
            numbers.push(std::stoi(word));
        } else {
            if (numbers.size() > 1) {
                operation (numbers, word, is_error_exist, error);
            }
            else {
                is_error_exist = true;
                error = "";
            }
        }
    }

    if (numbers.size() == 1 && !is_error_exist) {
        std::cout << " = " << numbers.top() << '\n';
    } else if (is_error_exist) {
        std::cout << '\n' << error << '\n';
    } else {
        std::cout << '\n' << "Wrong number of arguments." << '\n';
    }


}
