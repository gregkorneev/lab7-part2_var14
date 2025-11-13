#include "include.h"
#include <algorithm>

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
    int cur = bestEnd;
    while (cur != -1) {
        seq.push_back(a[cur]);
        cur = prev[cur];
    }
    std::reverse(seq.begin(), seq.end());

    return {bestLen, seq};
}
