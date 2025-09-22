#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>

/*
USACO 2023 February Contest, Silver
Problem 1. Bakery
*/

// https://usaco.org/index.php?page=viewproblem2&cpid=1302

using namespace std;

struct Constraint {
    long long a;
    long long b;
    long long c;
};

long long N, TC, TM; 

long long ceil_div(long long a, long long b) {
    return (a + b-1) / b;
}

int main() {
    int T; cin >> T;
    for (int j=0; j<T; j++) {
        cin >> N >> TC >> TM;

        vector<Constraint> constraints;
        // w = number of moonies. 
        // set x + y = w, x = cookie upgrades and y = 
        // muffin upgrades. 
        // 0 <= x < tC
        // 0 <= y < tM
        // a_i(tC-x) + bi(tM - y) <= ci
        auto check_ok = [&](long long w) {
            long long maxX = 0, maxY = 0;

            for (auto const& constraint : constraints) {
                long long lower_bound = constraint.a * TC + constraint.b * TM - constraint.c;
                if (constraint.a == constraint.b) {
                    if (constraint.a * w < lower_bound) return false;
                } else if (constraint.a < constraint.b) {
                    lower_bound -= (constraint.a * w);
                    long long lower_y_bound = ceil_div(lower_bound, (constraint.b - constraint.a));
                    maxY = max(maxY, lower_y_bound);
                } else {
                    lower_bound -= (constraint.b * w);
                    long long lower_x_bound = ceil_div(lower_bound, (constraint.a - constraint.b));
                    maxX = max(maxX, lower_x_bound);
                }
            }

            return maxX + maxY <= w && maxX <= TC - 1 && maxY <= TM - 1;
        };

        for (int i=0; i<N; i++) {
            long long a, b, c; cin >> a >> b >> c;
            constraints.push_back({a, b, c});
        }

        long long lo = 0;
        long long hi = TC + TM - 2;
        while (lo < hi) {
            long long mid = (lo + hi) / 2;
            if (!check_ok(mid)) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }

        cout << lo << endl;
    }
    
}
