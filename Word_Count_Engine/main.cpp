#include <iostream>
#include <cctype>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

std::vector<std::vector<std::string>> word_count_engine(const std::string& document) {
    // word -> count
    std::unordered_map<std::string, int> word_count;
    // word -> index
    std::unordered_map<std::string, int> word_index;

    int max_word_count = 0;
    int curr_index = 0;

    std::string word;

    auto handle_word = [&]() {
        if (word_count.find(word) == word_count.end()) {
            word_count[word] = 1;
            word_index[word] = curr_index;
            curr_index += 1;
        }
        else {
            word_count[word] += 1;
        }
        max_word_count = std::max(max_word_count, word_count[word]);
        word.clear();
    };

    for (char ch : document) {
        if (ispunct(ch)) {
            continue;
        }
        else if (ch >= 'a' && ch <= 'z') {
            word += ch;
        }
        else if (ch >= 'A' && ch <= 'Z') {
            word += ('a' + ch - 'A');
        }
        else if (!word.empty()) {
            handle_word();
        }
    }

    if (!word.empty()) {
        handle_word();
    }

    // count -> words
    std::vector<std::vector<std::string>> buckets(max_word_count + 1);

    for (const auto& kv : word_count) {
        const auto word = kv.first;
        const auto count = kv.second;
        buckets[count].push_back(word);
    }

    std::vector<std::vector<std::string>> result;

    for (int count = max_word_count; count >= 1; count--) {
        if (!buckets[count].empty()) {
            std::sort(buckets[count].begin(), buckets[count].end(), [& word_index](const std::string& lhs, const std::string& rhs) {
                return word_index[lhs] < word_index[rhs];
            });
            for (const auto& word : buckets[count]) {
                result.emplace_back(std::vector<std::string>{ word, std::to_string(count) });
            }
        }
    }

    return result;
}

int main() {
    const auto result = word_count_engine("Practice makes perfect. you'll only get Perfect by practice. just practice!");

    for (const auto& item : result) {
        std::cout << item[0] << " " << item[1] << std::endl;
    }
}