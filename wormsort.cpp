#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>
#include <stack>

/*
https://usaco.org/index.php?page=viewproblem2&cpid=992
USACO 2020 January Contest, Silver
Problem 3. Wormhole Sort
*/

// the key idea is to get the islands from the permutation and verify
// using DSU that those islands are connected completely. 

using namespace std;

class DSU {
    public:
        vector<int> parents;
        vector<int> weights;
        int size;

        DSU(int N) {
            size = N;
            for (int i=0; i<N; i++) {
                parents.push_back(i);
            }

            for (int i=0; i<N; i++) {
                weights.push_back(1);
            }
        }

        int parent(int x) {
            if (parents[x] == x) {
                return x;
            }

            auto real_parent = parent(parents[x]);
            parents[x] = real_parent;
            return real_parent;
        }

        void connect(int x, int y) {
            if (parent(x) != parent(y)) {
                if (weights[parent(x)] <= weights[parent(y)]) {
                    parents[parent(x)] = parent(y);
                    weights[parent(y)] += weights[parent(x)];
                } else {
                    connect(y, x);
                }
            }
        }

        // check everything has same parent.

        bool is_connected(vector<int> items) {
            auto par = parent(items[0]);
            for (int i=1; i<items.size(); i++) {
                if (par != parent(items[i])) {
                    return false;
                }

            }
            return true;
        }
};

struct WH {
    int a;
    int b;
    int w;
};

// only use wormhole with width at least W
bool check(int N, vector<vector<int>>& islands, vector<WH>& whs, int W) {
    DSU components(N);
    for (auto const&wh : whs) {
        if (wh.w >= W) {
            components.connect(wh.a, wh.b);
        }
    }

    for (auto const&island: islands) {
        if (!components.is_connected(island)) {
            return false;
        }
    }
    return true;
}

int main() {
    ifstream fin("wormsort.in");
    ofstream fout("wormsort.out");

    int N,M; fin >> N >> M;

    vector<int> p(N);
    for (int i=0; i<N; i++) {
        int x;
        fin >> x;
        p[i] = x-1;
    }

    bool done = true;
    for (int i=0; i<N; i++) {
        if (p[i] != i) done = false;
    }

    if (done) {
        fout << -1 << endl;
        return 0;
    }

    vector<vector<int>> islands;
    vector<bool> visited(N, false);
    for (int i=0; i<N; i++) {
        if (!visited[i]) {
            vector<int> island;
            auto cur = i;
            while (!visited[cur]) {
                island.push_back(cur);
                visited[cur] = true;
                cur = p[cur];
            }
            islands.push_back(island);
        }
    }

    vector<WH> whs;

    for (int i=0; i<M; i++ ){ 
        int a,b,w; fin >> a >> b >> w;
        whs.push_back({a-1, b-1, w});
    }

    // for (int i=0; i<20; i++) {
    //     cout << i << " " << check(N, islands, whs, i) << endl;
    // }

    int lo = 0;
    int hi = 1000000000 + 5;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (check(N, islands, whs, mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    fout << lo << endl;


}
