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

USACO 2018 December Contest, Silver
Problem 1. Convention

*/

//https://usaco.org/index.php?page=viewproblem2&cpid=858 

using namespace std;

bool simulate(vector<int>& times, int maxWait, int M, int C) {
    //track num buses used
    int numBuses = 0;

    int leftPtr = 0;
    int rightPtr = 0;
    while (leftPtr < times.size()) {
        int numOnBus = 1;
        while (rightPtr < times.size() && times[rightPtr] - times[leftPtr] <= maxWait && numOnBus <= C) {
            numOnBus++;
            rightPtr++;
        }
        leftPtr = rightPtr;
        numBuses++;
    }

    return numBuses <= M;
}

int main() {
    ifstream fin("convention.in");
    ofstream fout("convention.out");

    int N, M, C;
    fin >> N >> M >> C;
    vector<int> times;
    for (int i=0; i<N; i++) {
        int t; fin >> t;
        times.push_back(t);
    }

    // cout << N << " " << M << " " << C << endl;

    sort(times.begin(), times.end());

    int lo = 0;
    int hi = 1000000000;

    // for (int i=lo; i < lo + 10; i++) {
    //     cout << simulate(times, i, M, C) << endl;
    // }

    while (lo < hi) {
        int mid = (lo + hi)/2;
        if (!simulate(times, mid, M, C)) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    fout << lo << endl;
}
