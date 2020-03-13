#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <cassert>

std::vector<std::string> diff_between_two_strings(const std::string& source, const std::string& target) {
    // dp[i][j]: min edit num of source[i, ...] & target[j, ...]
    std::vector<std::vector<int>> dp(source.size() + 1, std::vector<int>(target.size() + 1));

    for (int i = source.size(); i >= 0; i--) {
        for (int j = target.size(); j >= 0; j--) {
            if (i == source.size()) {
                dp[i][j] = target.size() - j;
            }
            else if (j == target.size()) {
                dp[i][j] = source.size() - i;
            }
            else if (source[i] == target[j]) {
                dp[i][j] = dp[i + 1][j + 1];
            }
            else {
                dp[i][j] = 1 + std::min(dp[i + 1][j], dp[i][j + 1]);
            }
        }
    }

    int i = 0;
    int j = 0;

    std::vector<std::string> result;

    while (i < source.size() && j < target.size()) {
        if (source[i] == target[j]) {
            result.emplace_back(std::string(1, source[i]));
            i += 1;
            j += 1;
        }
        else {
            if (dp[i + 1][j] <= dp[i][j + 1]) {
                // remove source[i]
                result.emplace_back(std::string(1, '-') + source[i]);
                i += 1;
            }
            else {
                // add target[j]
                result.emplace_back(std::string(1, '+') + target[j]);
                j += 1;
            }
        }
    }

    while (i < source.size()) {
        // remove source[i]
        result.emplace_back(std::string(1, '-') + source[i]);
        i += 1;
    }

    while (j < target.size()) {
        // add target[j]
        result.emplace_back(std::string(1, '+') + target[j]);
        j += 1;
    }

    return result;
}

template <typename T>
void check_equal(const std::vector<T>& i, const std::vector<T>& j) {
    assert(std::equal(i.begin(), i.end(), j.begin()));
}

int main() {
    const std::string source = "ABCDEFG";
    const std::string target = "ABDFFGH";
    const auto diff = diff_between_two_strings(source, target);
    check_equal(diff, { "A", "B", "-C", "D", "-E", "F", "+F", "G", "+H" });
}