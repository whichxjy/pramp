#include <vector>
#include <cassert>

// Time Complexity: O(log(N))
// Space Complexity: O(1)

// search_pivot([9, 12, 17, 2, 4, 5]) => 2 (index of 17)
int search_pivot(const std::vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if ((mid == arr.size() - 1) || (arr[mid] > arr[mid + 1])) {
            return mid;
        }
        else if (arr[mid] >= arr[0]) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }

    return -1;
}

int binary_search(const std::vector<int>& arr, int num, int left, int right) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == num) {
            return mid;
        }
        else if (arr[mid] > num) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }

    return -1;
}

int shifted_arr_search(const std::vector<int>& arr, int num) {
    if (arr.empty()) {
        return -1;
    }
    else {
        int pivot_index = search_pivot(arr);
        if (pivot_index == -1) {
            return -1;
        }

        int left_result = binary_search(arr, num, 0, pivot_index);

        if (left_result != -1) {
            return left_result;
        }
        else {
            return binary_search(arr, num, pivot_index + 1, arr.size());
        }
    }
}

int main() {
    {
        std::vector<int> arr = {};
        assert(shifted_arr_search(arr, 123) == -1);
    }
    {
        std::vector<int> arr = { 1 };
        assert(shifted_arr_search(arr, 1) == 0);
        assert(shifted_arr_search(arr, 8) == -1);
    }
    {
        std::vector<int> arr = { 1, 2 };
        assert(shifted_arr_search(arr, 1) == 0);
        assert(shifted_arr_search(arr, 2) == 1);
    }
    {
        std::vector<int> arr = { 9, 12, 17, 2, 4, 5 };
        assert(shifted_arr_search(arr, 2) == 3);
        assert(shifted_arr_search(arr, 8) == -1);
    }
}