#pragma once
#include <vector>
#include <random>

// ====== Структуры ======
struct LISResult {
    int length;
    std::vector<int> seq;
};

// ====== Функции ДП ======
LISResult lis_dp(const std::vector<int>& a);

// ====== Наивный метод ======
int lis_bruteforce_len(const std::vector<int>& a);

// ====== Утилиты ======
std::vector<int> gen_random_array(int n, std::mt19937& rng);
long long measure_ms_dp(const std::vector<int>& a, int& out_len);
long long measure_ms_bf(const std::vector<int>& a, int& out_len);
