#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution {
    bool check(const std::vector<std::vector<int>>& g) {
        int m = g.size(), n = g[0].size();
        long long s1 = 0, s2 = 0;
        std::unordered_map<int, int> cnt1, cnt2;

        for (const auto& row : g) {
            for (int x : row) {
                s2 += x;
                cnt2[x]++;
            }
        }

        for (int i = 0; i < m - 1; ++i) {
            for (int x : g[i]) {
                s1 += x;
                s2 -= x;
                cnt1[x]++;
                cnt2[x]--;
            }

            if (s1 == s2) return true;

            if (s1 < s2) {
                long long diff = s2 - s1;
                if (cnt2[diff] > 0) {
                    // Check connectivity for bottom part (g[i+1 ... m-1])
                    // If height > 1 and width > 1, always connected.
                    // Otherwise, must be on boundary.
                    if ((m - (i + 1) > 1 && n > 1) || 
                        (i == m - 2 && (g[i + 1][0] == diff || g[i + 1][n - 1] == diff)) || 
                        (n == 1 && (g[i + 1][0] == diff || g[m - 1][0] == diff))) {
                        return true;
                    }
                }
            } else {
                long long diff = s1 - s2;
                if (cnt1[diff] > 0) {
                    // Check connectivity for top part (g[0 ... i])
                    if ((i + 1 > 1 && n > 1) || 
                        (i == 0 && (g[0][0] == diff || g[0][n - 1] == diff)) || 
                        (n == 1 && (g[0][0] == diff || g[i][0] == diff))) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    std::vector<std::vector<int>> rotate(const std::vector<std::vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        std::vector<std::vector<int>> res(n, std::vector<int>(m));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                res[j][m - 1 - i] = grid[i][j];
            }
        }
        // A simpler transpose works for grid orientation checks if symmetrical conditions apply,
        // but rotating/transposing correctly matches vertical cut evaluations.
        return res;
    }

public:
    bool canPartitionGrid(std::vector<std::vector<int>>& grid) {
        // Check horizontal cuts
        if (check(grid)) return true;

        // Check vertical cuts by transposing the grid
        int m = grid.size(), n = grid[0].size();
        std::vector<std::vector<int>> transposed(n, std::vector<int>(m));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                transposed[j][i] = grid[i][j];
            }
        }
        return check(transposed);
    }
};