#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

//https://usaco.org/index.php?page=viewproblem2&cpid=944
/*
USACO 2019 US Open Contest, Silver
Problem 3. Fence Planning
*/

struct cow {
    int x;
    int y;
};

int get_perimeter(const vector<cow>& cows) {
    vector<int> xs;
    vector<int> ys;

    for (auto const&cow: cows) {
        xs.push_back(cow.x);
        ys.push_back(cow.y);
    }

    return 2 * (*max_element(xs.begin(), xs.end()) - *min_element(xs.begin(), xs.end())) + 2 * (*max_element(ys.begin(), ys.end()) - *min_element(ys.begin(), ys.end()));
}

class DSU {
public:
    int n;
    vector<int> parents;
    vector<int> counts;


    DSU(int num) {
        n = num;
        for (int i=0; i<n; i++) {
            parents.push_back(i);
        }

        for (int i=0; i<n; i++) {
            counts.push_back(1);
        }
    }

    int get_parent(int x) {
        if (x == parents[x]) {
            return x;
        }

        auto ans = get_parent(parents[x]);
        parents[x] = ans;
        return ans;
    }

    // assumes 0 index
    void connect(int x, int y) {
        int px = get_parent(x);
        int py = get_parent(y);
        if (px != py) {
            int cx = counts[px];
            int cy = counts[py];

            if (cx <= cy) {
                counts[py] += cy;
                parents[px] = py;
            } else {
                connect(y, x);
            }
        }
    }
};

int main() {
    int N; int M;

    ifstream fin("fenceplan.in");
    ofstream fout("fenceplan.out");

    fin >> N >> M;

    vector<cow> cows;
    DSU dsu(N);

    for (int i=0; i<N; i++) {
        int x,y; fin >> x >> y;
        cows.push_back({x,y});
    }

    for (int i=0; i<M; i++) {
        int a,b; fin >> a >> b;
        dsu.connect(a-1, b-1);
    }

    for (int i=0; i<N; i++) {
        dsu.get_parent(i);
    }

    

    // goes from cow to a set of indexes of cows belonging to that group.
    unordered_map<int, vector<cow>> cow_to_idxs;

    for (int i=0; i<N; i++) {
        cow_to_idxs[dsu.parents[i]].push_back(cows[i]);
    }

    int least_perimeter = INT_MAX;

    for (auto const&group: cow_to_idxs) {
        least_perimeter = min(least_perimeter, get_perimeter(group.second));
    }

    fout << least_perimeter;
}
