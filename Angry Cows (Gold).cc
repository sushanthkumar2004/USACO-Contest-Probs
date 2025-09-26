#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <climits>
#include <iomanip>

/*

USACO 2016 January Contest, Gold
Problem 1. Angry Cows
https://usaco.org/index.php?page=viewproblem2&cpid=597 
*/

using namespace std;

// bin search on diam since .5 is possible
int main() {
    ifstream fin("angry.in");
    ofstream fout("angry.out");

    long long N;
    vector<long long> x;
    fin >> N;
    for (long long i=0; i<N; i++) {
        long long pos; fin >> pos;
        x.push_back(pos);
    }

    sort(x.begin(), x.end());

    // by convention, pos is the leftpoint of 
    // D sized interval
    auto can_explode_left = [&](long long pos, long long D) {
        auto left_most_in_range = lower_bound(x.begin(), x.end(), pos);
        if (left_most_in_range == x.begin()) {
            return true;
        }
        long long idx = left_most_in_range - x.begin();

        while (idx > 0 && D >= 0) {
            int idx_traveller = idx;
            while (idx_traveller >= 0 && 2 * (x[idx] - x[idx_traveller]) <= D - 2) {
                idx_traveller--;
            }
            if (idx_traveller == idx - 1) return false;
            if (idx_traveller == -1) return true;
            idx = idx_traveller+1;
            D -= 2;
        }
        return true;
    };

    // same convention as before
    auto can_explode_right = [&](long long pos, long long D) {
        long long right_endpoint = pos + D;
        auto right_most_out_of_range = upper_bound(x.begin(), x.end(), right_endpoint);
        if (right_most_out_of_range == x.end()) {
            return true;
        }

        long long idx = right_most_out_of_range - x.begin();
        while (idx < x.size() && D >= 0) {
            int idx_traveller = idx - 1;
            while (idx_traveller < x.size() && 2 * (x[idx_traveller] - x[idx-1]) <= D - 2) {
                idx_traveller++;
            }
            if (idx_traveller == x.size()) return true;
            if (idx_traveller == idx) return false;
            idx = idx_traveller--;
            D-=2;
        }
        return true;
    };

    // idea is to binary search to find the rightmost point
    // from which we can still explode the leftmost haybale. 
    // then binary search to find the leftmost point from which
    // we can still explode the rightmost haybale. 
    auto check_explodes = [&](long long D) {
        long long lo = x[0];
        long long hi = x.back();
        while (lo < hi) {
            long long mid = (1 + lo + hi) / 2;
            if (can_explode_left(mid, D)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return can_explode_right(hi, D);
    };

    long long lo = 0;
    long long hi = x.back() - x[0];
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        if (check_explodes(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    double answer = ((double) lo) / 2.0;
    cout << fixed << setprecision(1) << answer << "\n";
}
