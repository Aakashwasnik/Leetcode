#include <vector>
#include <cmath>
#include <algorithm>

class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, std::vector<int>& workerTimes) {
        long long l = 1;
        long long r = 1e16; // Safe upper bound based on constraints
        long long ans = r;

        auto check = [&](long long mid) {
            long long totalHeight = 0;
            for (int wt : workerTimes) {
                long long work = mid / wt;
                long long k = (-1 + std::sqrt(1 + 8.0 * work)) / 2;
                totalHeight += k;
                if (totalHeight >= mountainHeight) {
                    return true; // Early exit optimization
                }
            }
            return totalHeight >= mountainHeight;
        };

        while (l <= r) {
            long long mid = l + (r - l) / 2;
            if (check(mid)) {
                ans = mid;
                r = mid - 1; // Try to find a smaller feasible time
            } else {
                l = mid + 1; // Increase time if insufficient
            }
        }

        return ans;
    }
};