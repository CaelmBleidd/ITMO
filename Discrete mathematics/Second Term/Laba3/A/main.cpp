#include <iostream>
#include <unordered_map>
#include <queue>

int main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::freopen("automaton.in", "r", stdin);
    std::freopen("automaton.out", "w", stdout);

    uint64_t n = 0;
    std::cin >> n;

    std::string start;
    std::cin >> start;

    std::unordered_map<std::string, bool> global_dict;

    std::unordered_map<char, std::vector<std::string>> dict;

    for (uint64_t i = 0; i < n; ++i) {
        char from = ' ';
        std::string to;
        std::string trash;
        std::cin >> from >> trash >> to;
        dict[from].push_back(to);
    }

    uint64_t m = 0;
    std::cin >> m;

    for(uint64_t i = 0; i < m; ++i) {
        std::string line;
        std::cin >> line;

        if (global_dict.find(line) == global_dict.end()) {

            bool is_true = false;

            std::queue<std::string> queue;
            queue.push(start);
            while (!queue.empty()) {
                if (is_true)
                    break;
                auto one_more_tmp = queue.front();
                queue.pop();

                if (one_more_tmp.length() > line.length())
                {
                    is_true = false;
                    break;
                }

                char tmp = one_more_tmp[one_more_tmp.size() - 1]; // всегда нетерминал
                one_more_tmp = one_more_tmp.substr(0, one_more_tmp.size() - 1); //one_more... слово, которое достал из очереди, но без последнего символа

                if (dict.find(tmp) != dict.end()) {
                    for (const auto &s : dict[tmp]) {
                        std::string new_line = one_more_tmp;
                        new_line = new_line + s;
                        if (s.size() == 2) {
                            queue.push(new_line);
                            continue;
                        } else {
                            if (new_line == line) {
                                global_dict[new_line] = true;
                                is_true = true;
                                break;
                            } else {
                                is_true = false;
                                global_dict[new_line] = true;
                                continue;
                            }
                        }

                    }
                } else {
                    is_true = false;
                    continue;
                }

            }
            if (is_true)
                std::cout << "yes" << '\n';
            else
                std::cout << "no" << '\n';
        } else {
            std::cout << "yes" << '\n';
        }

    }

    return 0;
}