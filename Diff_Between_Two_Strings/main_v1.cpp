#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

struct Result {
    int edit_num;
    std::vector<std::string> diff;

    Result(int edit_num, const std::vector<std::string>& diff)
    : edit_num(edit_num), diff(diff) {}
};

// dp[i][j]: result of source[i, ...] & target[j, ...]

Result solve(const std::string& source, const std::string& target, int i, int j) {
    if (i == source.size()) {
        int edit_num = target.size() - j;
        std::vector<std::string> diff;
        for (int curr = j; curr < target.size(); curr++) {
            diff.emplace_back(std::string(1, '+') + target[curr]);
        }
        return { edit_num, diff };
    }
    else if (j == target.size()) {
        int edit_num = source.size() - i;
        std::vector<std::string> diff;
        for (int curr = i; curr < source.size(); curr++) {
            diff.emplace_back(std::string(1, '-') + source[curr]);
        }
        return { edit_num, diff };
    }
    else if (source[i] == target[j]) {
        auto result_next = solve(source, target, i + 1, j + 1);
        std::vector<std::string> diff{ std::string(1, source[i]) };
        diff.insert(diff.end(), result_next.diff.begin(), result_next.diff.end());
        return { result_next.edit_num, diff };
    }
    else {
        // remove source[i]
        auto remove_result = solve(source, target, i + 1, j);
        // add target[j]
        auto add_result = solve(source, target, i, j + 1);

        if (remove_result.edit_num <= add_result.edit_num) {
            // remove
            std::vector<std::string> diff{ std::string(1, '-') + source[i] };
            diff.insert(diff.end(), remove_result.diff.begin(), remove_result.diff.end());
            return { 1 + remove_result.edit_num, diff };
        }
        else {
            // add
            std::vector<std::string> diff{ std::string(1, '+') + target[j] };
            diff.insert(diff.end(), add_result.diff.begin(), add_result.diff.end());
            return { 1 + add_result.edit_num, diff };
        }
    }
}

std::vector<std::string> diff_between_two_strings(const std::string& source, const std::string& target) {
    auto result = solve(source, target, 0, 0);
    return result.diff;
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