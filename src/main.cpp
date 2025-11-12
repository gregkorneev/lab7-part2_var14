#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>
#include <cstdlib>

// =======================================
// Лабораторная работа 7.2, вариант 14
// Тема: Самая длинная возрастающая подпоследовательность (LIS)
// Метод: Динамическое программирование O(n²)
// =======================================

// Результат LIS
struct LISResult {
    int length;
    std::vector<int> seq;
};

// Алгоритм LIS O(n²)
LISResult lis_dp(const std::vector<int>& a) {
    int n = (int)a.size();
    if (n == 0) return {0, {}};

    std::vector<int> dp(n, 1);     // dp[i] — длина LIS, заканчивающейся на i
    std::vector<int> prev(n, -1);  // для восстановления
    int bestLen = 1;
    int bestEnd = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
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

    // восстановление LIS
    std::vector<int> seq;
    for (int cur = bestEnd; cur != -1; cur = prev[cur])
        seq.push_back(a[cur]);
    std::reverse(seq.begin(), seq.end());

    return {bestLen, seq};
}

// Генерация случайного массива
std::vector<int> gen_random_array(int n, std::mt19937& rng) {
    std::uniform_int_distribution<int> dist(-10000, 10000);
    std::vector<int> v(n);
    for (int i = 0; i < n; ++i) v[i] = dist(rng);
    return v;
}

// Замер времени
long long measure_ms(const std::vector<int>& a, int& out_len) {
    auto t1 = std::chrono::steady_clock::now();
    LISResult res = lis_dp(a);
    auto t2 = std::chrono::steady_clock::now();
    out_len = res.length;
    return std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
}

int main() {
    std::mt19937 rng(1234567);

    std::system("mkdir -p data");
    std::ofstream csv("data/timings_lis.csv");
    csv << "n,time_ms,length\n";

    std::vector<int> sizes = {50, 100, 200, 400, 800, 1200, 1600, 2000};
    int trials = 5;

    for (int n : sizes) {
        for (int t = 1; t <= trials; ++t) {
            auto a = gen_random_array(n, rng);
            int len = 0;
            long long ms = measure_ms(a, len);
            csv << n << "," << ms << "," << len << "\n";
            std::cout << "n=" << n << " trial=" << t
                      << " time=" << ms << "ms len=" << len << "\n";
        }
    }

    // Демонстрация
    std::vector<int> demo = {10, 9, 2, 5, 3, 7, 101, 18};
    LISResult r = lis_dp(demo);
    std::cout << "\nПример:\nИсходный массив: ";
    for (int x : demo) std::cout << x << " ";
    std::cout << "\nДлина LIS = " << r.length << "\nПоследовательность: ";
    for (int x : r.seq) std::cout << x << " ";
    std::cout << "\n\nCSV сохранён в data/timings_lis.csv\n";
    return 0;
}