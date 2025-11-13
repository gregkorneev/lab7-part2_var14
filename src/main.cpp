#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>

// ============================================
// ЛР 7.2 — Вариант 14
// LIS — Longest Increasing Subsequence
// Методы:
//   1) Динамическое программирование O(n²)
//   2) Наивный перебор (экспонента, только для малого n)
// ============================================

// Структура результата LIS
struct LISResult {
    int length;
    std::vector<int> seq;
};

// -------------------------------------------
// 1. Основной метод — Динамическое программирование O(n²)
// -------------------------------------------
LISResult lis_dp(const std::vector<int>& a) {
    int n = a.size();
    if (n == 0) return {0, {}};

    std::vector<int> dp(n, 1);
    std::vector<int> prev(n, -1);

    int bestLen = 1;
    int bestEnd = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        if (dp[i] > bestLen) {
            bestLen = dp[i];
            bestEnd = i;
        }
    }

    std::vector<int> seq;
    for (int cur = bestEnd; cur != -1; cur = prev[cur])
        seq.push_back(a[cur]);
    std::reverse(seq.begin(), seq.end());

    return {bestLen, seq};
}

// -------------------------------------------
// 2. Наивный метод — полный перебор O(2^n)
// -------------------------------------------
int lis_bruteforce_len(const std::vector<int>& a) {
    int n = a.size();
    if (n == 0) return 0;

    int best = 1;

    for (int mask = 1; mask < (1 << n); mask++) {
        int last = 0;
        bool hasLast = false;
        int len = 0;
        bool ok = true;

        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                if (!hasLast) {
                    last = a[i];
                    len = 1;
                    hasLast = true;
                } else {
                    if (last < a[i]) {
                        last = a[i];
                        len++;
                    } else {
                        ok = false;
                        break;
                    }
                }
            }
        }
        if (ok) best = std::max(best, len);
    }
    return best;
}

// -------------------------------------------
// Генерация массива
// -------------------------------------------
std::vector<int> gen_random_array(int n, std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(-10000, 10000);
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = dist(rng);
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

// -------------------------------------------
// MAIN
// -------------------------------------------
int main() {
    std::mt19937 rng(1234567);

    system("mkdir -p data");
    std::ofstream csv("data/timings_lis.csv");
    csv << "method,n,time_ms,length\n";

    // --- Малые n: сравниваем два метода ---
    std::vector<int> tiny = {10, 12, 15, 18};
    int trials = 3;

    for (int n : tiny) {
        for (int t = 0; t < trials; t++) {
            auto a = gen_random_array(n, rng);

            int Lbf = 0;
            long long bf_ms = measure_ms_bf(a, Lbf);
            csv << "bruteforce," << n << "," << bf_ms << "," << Lbf << "\n";

            int Ldp = 0;
            long long dp_ms = measure_ms_dp(a, Ldp);
            csv << "dp," << n << "," << dp_ms << "," << Ldp << "\n";
        }
    }

    // --- Основные измерения: только DP ---
    std::vector<int> sizes = {50, 100, 200, 400, 800, 1200, 1600, 2000};

    for (int n : sizes) {
        for (int t = 0; t < trials; t++) {
            auto a = gen_random_array(n, rng);
            int Ldp = 0;
            long long ms = measure_ms_dp(a, Ldp);
            csv << "dp," << n << "," << ms << "," << Ldp << "\n";
            std::cout << "n=" << n << " time=" << ms << "ms len=" << Ldp << "\n";
        }
    }

    // Демонстрация
    std::vector<int> demo = {10, 9, 2, 5, 3, 7, 101, 18};
    LISResult r = lis_dp(demo);
    std::cout << "\nПример:\n";
    std::cout << "Исходный массив: ";
    for (int x : demo) std::cout << x << " ";
    std::cout << "\nДлина LIS = " << r.length << "\nПоследовательность: ";
    for (int x : r.seq) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "\nCSV сохранён в data/timings_lis.csv\n";
    return 0;
}
