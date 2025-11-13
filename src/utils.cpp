#include "include.h"
#include <chrono>

std::vector<int> gen_random_array(int n, std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(-10000, 10000);
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = dist(rng);
    return arr;
}

long long measure_ms_dp(const std::vector<int>& a, int& out_len) {
    auto t1 = std::chrono::steady_clock::now();
    LISResult r = lis_dp(a);
    auto t2 = std::chrono::steady_clock::now();
    out_len = r.length;
    return std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
}

long long measure_ms_bf(const std::vector<int>& a, int& out_len) {
    auto t1 = std::chrono::steady_clock::now();
    int L = lis_bruteforce_len(a);
    auto t2 = std::chrono::steady_clock::now();
    out_len = L;
    return std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
}
