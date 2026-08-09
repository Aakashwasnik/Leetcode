#include <vector>
#include <algorithm>

class Solution {
private:
    std::vector<int> suffixSum;
    std::vector<std::vector<int>> memo;

    int dp(int i, int m, int n, const std::vector<int>& piles) {
        // If all remaining piles can be taken in this turn
        if (i + 2 * m >= n) {
            return suffixSum[i];
        }
        
        if (memo[i][m] != -1) {
            return memo[i][m];
        }

        int maxStones = 0;
        // Try all valid choices for X (1 to 2*M)
        for (int x = 1; x <= 2 * m; ++x) {
            int stones = suffixSum[i] - dp(i + x, std::max(m, x), n, piles);
            maxStones = std::max(maxStones, stones);
        }

        return memo[i][m] = maxStones;
    }

public:
    int stoneGameII(std::vector<int>& piles) {
        int n = piles.size();
        
        // Precompute suffix sums from right to left
        suffixSum.assign(n + 1, 0);
        for (int i = n - 1; i >= 0; --i) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }

        // Initialize memoization table with -1
        memo.assign(n, std::vector<int>(n + 1, -1));
        
        return dp(0, 1, n, piles);
    }
};