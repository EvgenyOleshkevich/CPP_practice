#pragma once
#include <math.h>
#include <ctime>
#include <queue>
#include <unordered_set>

namespace leetcode {

    namespace task_552 {
        /*
        * https://leetcode.com/problems/student-attendance-record-ii/description/
        */
        class Solution {
        public:
            vector<unsigned long long> answers;
            const unsigned long long mod = 1000000007;
            unsigned long long f0, f1, f2, f3;
            unsigned long long g0, g1, g2, g3;

            int checkRecord(int n) {
                answers = vector<unsigned long long>({1, 2, 4, 7, 13, 24, 44, 81}); // steps 0-7
                f0 = 13, f1 = 20, f2 = 24, f3 = 24;

                for (int i = 8; i < n; ++i)
                    nextStep(i);

                unsigned long long res = answers[n % 8];
                for (size_t i = 2; i < 7 && i <= n; i++)
                    res += answers[(n - i) % 8] << 1;

                for (size_t i = 3; i < 8 && i <= n; i++)
                    res += answers[(n - i) % 8] * (n - i + 1);

                return res % mod;;
            }

            void nextStep(const int step) {
                g0 = f2;
                g1 = (f0 + f2) % mod;
                g2 = (f1 + f3) % mod;
                g3 = (f1 + f3) % mod;
                f0 = g0;
                f1 = g1;
                f2 = g2;
                f3 = g3;
                answers[step % 8] = (f0 + f1 + f2 + f3) % mod;;
            }
        };
    }

}