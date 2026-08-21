#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
    long long gcd(long long a, long long b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    long long lcm(long long a, long long b) {
        return (a / gcd(a, b)) * b;
    }

public:
    long long findKthSmallest(std::vector<int>& coins, int k) {
        int n = coins.size();
        long long left = 1;
        long long right = (long long)k * *std::min_element(coins.begin(), coins.end());
        long long ans = right;

        while (left <= right) {
            long long mid = left + (right - left) / 2;
            long long count = 0;

            // Enumerate all non-empty subsets using bitmask
            for (int i = 1; i < (1 << n); ++i) {
                long long current_lcm = 1;
                int set_bits = 0;

                for (int j = 0; j < n; ++j) {
                    if ((i >> j) & 1) {
                        set_bits++;
                        current_lcm = lcm(current_lcm, coins[j]);
                        if (current_lcm > mid) {
                            break; // Optimization: Exceeds mid, no need to continue
                        }
                    }
                }

                if (current_lcm <= mid) {
                    if (set_bits % 2 == 1) {
                        count += mid / current_lcm;
                    } else {
                        count -= mid / current_lcm;
                    }
                }
            }

            if (count >= k) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return ans;
    }
};