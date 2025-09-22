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

USACO 2020 US Open Contest, Silver
Problem 1. Social Distancing

*/

//https://usaco.org/index.php?page=viewproblem2&cpid=1038

using namespace std;

struct Interval {
    long long left;
    long long right;

    bool operator<(const Interval& other) {
        return left < other.left;
    }
};

bool simulate(vector<Interval>& pastures, long long N, long long D) {
    long long numPlacedCows = 0;

    // last position that we placed a cow. 
    // initialize to -D so that the first cow does
    // not need any special logic
    long long lastPos = -D;
    for (auto const& interval: pastures) {
        long long leastAcceptiblePos = lastPos + D;

        if (leastAcceptiblePos <= interval.right) {
            long long firstCowPlaced = max(leastAcceptiblePos, interval.left);
            long long newCowsPlaced = (interval.right - firstCowPlaced) / D + 1;
            numPlacedCows += newCowsPlaced;
            lastPos = firstCowPlaced + (newCowsPlaced - 1) * D;
        }
    }

    // cout << "numPlacedCows: " << numPlacedCows << endl;
    return numPlacedCows >= N;
}

int main() {
    ifstream fin("socdist.in");
    ofstream fout("socdist.out");

    long long N, M; fin >> N >> M;
    vector<Interval> pastures;
    for (long long i=0; i<M; i++) {
        long long a, b; fin >> a >> b;
        pastures.push_back({a,b});
    }
    sort(pastures.begin(), pastures.end());

    // for (long long D = 1; D<10; D++) {
    //     cout << D << " " << simulate(pastures, N, D) << endl;
    // }
    long long lo = 1;
    long long hi = (long long) 1000000000 * (long long) 1000000000;
    while (lo < hi) {
        long long mid = (1 + lo + hi)/2;
                // cout << mid << endl;
        if (!simulate(pastures, N, mid)) {
            hi = mid - 1;
        } else {
            lo = mid;
        }
    }
    fout << hi << endl; 
}
