#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>

//
//USACO 2023 February Contest, Silver
//Problem 2. Cow-libi
//https://usaco.org/index.php?page=viewproblem2&cpid=1303 

using namespace std;

struct pasture {
    long long x; 
    long long y;
    long long t;

    bool operator<(const pasture& other) const {
        return t < other.t;
    }
};

// it was not taxi cab distance afterall. 
bool straightLineCheck(pasture& pasture, long long x, long long y, long long t) {
    return abs(pasture.x - x)*abs(pasture.x - x) + abs(pasture.y-y)*abs(pasture.y-y) > (pasture.t - t) * (pasture.t - t);
}

int main() {
    long long G, N;
    cin >> G >> N;

    vector<pasture> pastures;
    for (long long i=0; i<G; i++) {
        long long x,y,t; cin >> x >> y >> t;
        pastures.push_back({x,y,t});
    }

    sort(pastures.begin(), pastures.end());

    auto firstGreaterThanOrEqual = [&](long long t) {
        long long lo = 0;
        long long hi = pastures.size();

        while (lo < hi) {
            long long mid = (lo + hi)/2;
            if (t > pastures[mid].t) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        return lo;
    };

    long long cnt = 0;

    for (long long i=0; i<N; i++) {
        long long x,y,t; cin >> x >> y >> t;

        auto firstGET = firstGreaterThanOrEqual(t);
        // if equals pastures.size(), then the alibi works
        if (firstGET == 0) {
            if (straightLineCheck(pastures[0], x, y, t)) {
                // cout << "!" << x << " " << y << " " << t << endl;
                cnt++;
            }
        } else if (firstGET == pastures.size()) {
            auto last = pastures.back();
            if (straightLineCheck(last, x, y, t)) {
                // cout << "!" << x << " " << y << " " << t << endl;
                cnt ++;
            }
        } else {
            auto first = pastures[firstGET-1];
            auto second = pastures[firstGET];
            if (straightLineCheck(first, x, y, t) || straightLineCheck(second, x, y, t)) {
                // cout << "!" << x << " " << y << " " << t << endl;
                cnt ++;
            }
        }
    }
    cout << cnt << endl;
}
