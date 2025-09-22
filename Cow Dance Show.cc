#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>


//https://usaco.org/index.php?page=viewproblem2&cpid=690

using namespace std;

bool simulate(int K, int T_MAX, vector<int>& d) {
    priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (int i=0; i<K; i++) {
        pq.push(d[i]);
    }

    for (int i=K; i<d.size(); i++) {
        int least_dur = pq.top();
        int new_dur = least_dur + d[i];
        // cout << "new" << new_dur << endl;
        pq.pop();
        pq.push(new_dur);
    }

    int maxVal = pq.top();

    for (int j=0; j<K; j++) {
        maxVal = max(maxVal, pq.top());
        pq.pop();
    }

    // cout << "!!" << maxVal << endl;

    return maxVal <= T_MAX;
}

int main() {
    ifstream fin("cowdance.in");
    ofstream fout("cowdance.out");
    int N, T_MAX; fin >> N >> T_MAX;

    vector<int> d;
    for (int i=0; i<N; i++) {
        int duration; fin >> duration;
        d.push_back(duration);
    }

    // for (int K=1; K<= N; K++) {
    //     cout << "!" << K << " " << simulate(K, T_MAX, d) << endl;
    // }

    int lo = 1;
    int hi = N;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (!simulate(mid, T_MAX, d)) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    fout << lo << endl;


}
