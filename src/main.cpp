#include "include.h"
#include <iostream>
#include <fstream>

int main() {
    std::mt19937 rng(123456);

    system("mkdir -p data");
    std::ofstream csv("data/timings_lis.csv");
    csv << "method,n,time_ms,length\n";

    // Малые размеры — сравнение двух методов
    std::vector<int> tiny = {10, 12, 15, 18};
    for (int n : tiny) {
        auto a = gen_random_array(n, rng);

        int len_bf = 0;
        long long t_bf = measure_ms_bf(a, len_bf);
        csv << "bruteforce," << n << "," << t_bf << "," << len_bf << "\n";

        int len_dp = 0;
        long long t_dp = measure_ms_dp(a, len_dp);
        csv << "dp," << n << "," << t_dp << "," << len_dp << "\n";
    }

    // Основные размеры — только ДП
    std::vector<int> sizes = {50, 100, 200, 400, 800, 1200, 1600, 2000};
    for (int n : sizes) {
        auto a = gen_random_array(n, rng);

        int L = 0;
        long long t = measure_ms_dp(a, L);

        csv << "dp," << n << "," << t << "," << L << "\n";

        std::cout << "Размер массива n = " << n
                  << "   Время = " << t << " мс"
                  << "   Длина LIS = " << L << "\n";
    }

    // Демонстрация
    std::vector<int> demo = {10, 9, 2, 5, 3, 7, 101, 18};
    LISResult r = lis_dp(demo);

    std::cout << "\nДемонстрационный пример:\n";
    std::cout << "Массив: ";
    for (int x : demo) std::cout << x << " ";

    std::cout << "\nДлина LIS: " << r.length << "\n";
    std::cout << "Подпоследовательность: ";
    for (int x : r.seq) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "\nCSV-файл сохранён: data/timings_lis.csv\n";

    return 0;
}
