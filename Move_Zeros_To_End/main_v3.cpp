#include <vector>
#include <cassert>

std::vector<int> move_zeros_to_end(const std::vector<int>& arr) {
    std::vector<int> result(arr.begin(), arr.end());

    int write = 0;
    for (int read = 0; read < arr.size(); read++) {
        if (result[read] != 0) {
            std::swap(result[read], result[write]);
            write += 1;
        }
    }

    return result;
}

template <typename T>
void check_equal(const std::vector<T>& lhs, const std::vector<T>& rhs) {
    assert(std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

int main() {
    {
        std::vector<int> arr = {};
        std::vector<int> result = move_zeros_to_end(arr);
        check_equal(result, {});
    }
    {
        std::vector<int> arr = { 0, 0, 0 };
        std::vector<int> result = move_zeros_to_end(arr);
        check_equal(result, { 0, 0, 0 });
    }
    {
        std::vector<int> arr = { 1, 10, 0, 2, 8, 3, 0, 0, 6, 4, 0, 5, 7, 0 };
        std::vector<int> result = move_zeros_to_end(arr);
        check_equal(result, { 1, 10, 2, 8, 3, 6, 4, 5, 7, 0, 0, 0, 0, 0 });
    }
}