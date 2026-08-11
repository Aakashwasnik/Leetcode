#include <vector>

class Fancy {
private:
    std::vector<long long> vals;
    long long a = 1;
    long long b = 0;
    const long long MOD = 1e9 + 7;

    long long power(long long base, long long exp) {
        long long res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    }

    long long modInverse(long long n) {
        return power(n, MOD - 2);
    }

public:
    Fancy() {}

    void append(int val) {
        // Store the normalized original value: (val - b) * a^(-1) mod MOD
        long long original = (val - b % MOD + MOD) % MOD;
        original = (original * modInverse(a)) % MOD;
        vals.push_back(original);
    }

    void addAll(int inc) {
        b = (b + inc) % MOD;
    }

    void multAll(int m) {
        a = (a * m) % MOD;
        b = (b * m) % MOD;
    }

    int getIndex(int idx) {
        if (idx >= vals.size()) return -1;
        return (a * vals[idx] + b) % MOD;
    }
};