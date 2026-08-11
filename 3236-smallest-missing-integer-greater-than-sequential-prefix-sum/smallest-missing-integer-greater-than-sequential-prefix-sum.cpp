#include <vector>
#include <unordered_set>

class Solution {
public:
    int missingInteger(std::vector<int>& nums) {
        // Step 1: Find the sum of the longest sequential prefix
        int curr_sum = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] == nums[i - 1] + 1) {
                curr_sum += nums[i];
            } else {
                break;
            }
        }
        
        // Step 2: Store elements in an unordered_set for O(1) lookups
        std::unordered_set<int> nums_set(nums.begin(), nums.end());
        
        // Step 3: Find the smallest integer >= curr_sum not present in nums
        int x = curr_sum;
        while (nums_set.count(x)) {
            x++;
        }
        
        return x;
    }
};