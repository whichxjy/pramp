#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <cassert>

struct Result {
    int edit_num;
    std::vector<std::string> diff;

    Result() = default;
    Result(int edit_num, const std::vector<std::string>& diff)
    : edit_num(edit_num), diff(diff) {}
};

std::vector<std::string> diff_between_two_strings(const std::string& source, const std::string& target) {
    // dp[i][j]: result of source[i, ...] & target[j, ...]
    std::vector<std::vector<Result>> dp(source.size() + 1, std::vector<Result>(target.size() + 1));

    for (int i = source.size(); i >= 0; i--) {
        for (int j = target.size(); j >= 0; j--) {
            if (i == source.size()) {
                int edit_num = target.size() - j;
                std::vector<std::string> diff;
                for (int curr = j; curr < target.size(); curr++) {
                    diff.emplace_back(std::string(1, '+') + target[curr]);
                }
                dp[i][j] = Result(edit_num, diff);
            }
            else if (j == target.size()) {
                int edit_num = source.size() - i;
                std::vector<std::string> diff;
                for (int curr = i; curr < source.size(); curr++) {
                    diff.emplace_back(std::string(1, '-') + source[curr]);
                }
                dp[i][j] = Result(edit_num, diff);
            }
            else if (source[i] == target[j]) {
                auto result_next = dp[i + 1][j + 1];
                std::vector<std::string> diff{ std::string(1, source[i]) };
                diff.insert(diff.end(), result_next.diff.begin(), result_next.diff.end());
                dp[i][j] = Result(result_next.edit_num, diff);
            }
            else {
                // remove source[i]
                auto remove_result = dp[i + 1][j];
                // add target[j]
                auto add_result = dp[i][j + 1];

                if (remove_result.edit_num <= add_result.edit_num) {
                    // remove
                    std::vector<std::string> diff{ std::string(1, '-') + source[i] };
                    diff.insert(diff.end(), remove_result.diff.begin(), remove_result.diff.end());
                    dp[i][j] = Result(1 + remove_result.edit_num, diff);
                }
                else {
                    // add
                    std::vector<std::string> diff{ std::string(1, '+') + target[j] };
                    diff.insert(diff.end(), add_result.diff.begin(), add_result.diff.end());
                    dp[i][j] = Result(1 + add_result.edit_num, diff);
                }
            }
        }
    }

    return dp[0][0].diff;
}

template <typename T>
void check_equal(const std::vector<T>& lhs, const std::vector<T>& rhs) {
    assert(std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

int main() {
    const std::string source = "ABCDEFG";
    const std::string target = "ABDFFGH";
    const auto diff = diff_between_two_strings(source, target);
    check_equal(diff, { "A", "B", "-C", "D", "-E", "F", "+F", "G", "+H" });
}