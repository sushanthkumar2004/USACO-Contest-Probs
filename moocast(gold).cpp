#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <climits>
#include <algorithm>
#include <stack>

// https://usaco.org/index.php?page=viewproblem2&cpid=669#
/*
USACO 2016 December Contest, Gold
Problem 1. Moocast
*/

using namespace std;

struct Cow {
    int x;
    int y;
};


bool check(vector<Cow>& cows, int X) {
    // connect all cows within X*X
    vector<vector<int>> adj_list(cows.size());
    for (int i=0; i<cows.size(); i++) {
        for (int j=0; j<i; j++) {
            if (i != j) {
                auto cowj = cows[j];
                auto cowi = cows[i];

                int dist = (cowi.x - cowj.x) * (cowi.x - cowj.x) + (cowi.y - cowj.y) * (cowi.y - cowj.y);
                if (dist <= X) {
                    adj_list[i].push_back(j);
                    adj_list[j].push_back(i);
                }
            }
        }
    }

    // check we can reach everthing

    stack<int> dfs_queue;
    vector<bool> visited(cows.size(), false);

    dfs_queue.push(0);
    while (!dfs_queue.empty()) {
        int top = dfs_queue.top();
        dfs_queue.pop();

        visited[top] = true;

        for (auto const&n : adj_list[top]) {
            if (!visited[n]) {
                dfs_queue.push(n);
            }
        }
    }
    for (auto const&v : visited) {
        if (!v) {
            return false;
        }
    }
    return true;
}


int main() {
    ifstream fin("moocast.in");
    ofstream fout("moocast.out");

    int N; fin >> N;

    int lo = 0;
    int hi = 2 * 25000 * 25000 + 1;

    vector<Cow> cows;
    for (int i=0; i<N; i++) {
        int a,b; fin >> a >> b;
        cows.push_back({a,b});
    }

    // for (int i=0; i<20; i++) {
    //     cout << i << " " << check(cows, i) << endl;
    // }

    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (check(cows, mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    fout << lo << endl;


}
