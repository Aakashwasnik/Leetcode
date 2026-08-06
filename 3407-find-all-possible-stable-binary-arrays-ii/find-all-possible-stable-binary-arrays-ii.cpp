class Solution {
public:
    static constexpr int MOD = 1000000007;

    int numberOfStableArrays(int zero, int one, int limit) {
        vector<vector<array<int, 2>>> dp(
            zero + 1, vector<array<int, 2>>(one + 1));

        for (int i = 1; i <= min(zero, limit); i++)
            dp[i][0][0] = 1;

        for (int j = 1; j <= min(one, limit); j++)
            dp[0][j][1] = 1;

        for (int i = 1; i <= zero; i++) {
            for (int j = 1; j <= one; j++) {

                long long x = (i - limit - 1 >= 0)
                                  ? dp[i - limit - 1][j][1]
                                  : 0;

                long long y = (j - limit - 1 >= 0)
                                  ? dp[i][j - limit - 1][0]
                                  : 0;

                dp[i][j][0] =
                    ((long long)dp[i - 1][j][0] +
                     dp[i - 1][j][1] -
                     x + MOD) % MOD;

                dp[i][j][1] =
                    ((long long)dp[i][j - 1][0] +
                     dp[i][j - 1][1] -
                     y + MOD) % MOD;
            }
        }

        return ((long long)dp[zero][one][0] +
                dp[zero][one][1]) %
               MOD;
    }
};