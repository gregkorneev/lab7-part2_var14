#include "include.h"

int lis_bruteforce_len(const std::vector<int>& a) {
    int n = a.size();
    if (n == 0) return 0;

    int best = 1;

    for (int mask = 1; mask < (1 << n); mask++) {
        int last = 0;
        int len = 0;
        bool ok = true;
        bool hasLast = false;

        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                if (!hasLast) {
                    hasLast = true;
                    last = a[i];
                    len = 1;
                } else {
                    if (a[i] > last) {
                        last = a[i];
                        len++;
                    } else {
                        ok = false;
                        break;
                    }
                }
            }
        }
        if (ok && len > best) best = len;
    }

    return best;
}
