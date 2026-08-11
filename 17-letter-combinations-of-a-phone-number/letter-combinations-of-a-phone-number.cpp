#include <vector>
#include <string>

class Solution {
private:
    const std::vector<std::string> phone = {
        "",     // 0
        "",     // 1
        "abc",  // 2
        "def",  // 3
        "ghi",  // 4
        "jkl",  // 5
        "mno",  // 6
        "pqrs", // 7
        "tuv",  // 8
        "wxyz"  // 9
    };

    void backtrack(int index, const std::string& digits, std::string& current, std::vector<std::string>& result) {
        // Base case: if the current combination length equals digits length
        if (index == digits.length()) {
            result.push_back(current);
            return;
        }

        // Get the letters corresponding to the current digit
        std::string letters = phone[digits[index] - '0'];
        
        for (char c : letters) {
            current.push_back(c);           // Choose
            backtrack(index + 1, digits, current, result); // Explore
            current.pop_back();             // Un-choose (Backtrack)
        }
    }

public:
    std::vector<std::string> letterCombinations(std::string digits) {
        std::vector<std::string> result;
        if (digits.empty()) {
            return result;
        }
        std::string current = "";
        backtrack(0, digits, current, result);
        return result;
    }
};