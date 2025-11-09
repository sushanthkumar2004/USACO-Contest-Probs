#include <iostream>
#include <fstream>
#include <unordered_set>
#include <queue>
/*

USACO 2016 US Open Contest, Silver
Problem 3. Closing the Farm

https://usaco.org/index.php?page=viewproblem2&cpid=644
  */

using namespace std;

// returns num of visited vertices
int bfs(vector<unordered_set<int>>& adj_list, unordered_set<int>& valid_starts) {
    int starting = *valid_starts.begin();
    vector<bool> visited(adj_list.size(), false);

    queue<int> fringe;
    fringe.push(starting);
    while (!fringe.empty()) {
        int top = fringe.front();
        fringe.pop();
        visited[top] = true;

        for (auto const&n: adj_list[top]) {
            if (!visited[n]) {
                fringe.push(n);
            }
        }

    }
    int cnt = 0;
    for (int i=0; i<adj_list.size(); i++) {
        if (visited[i]) cnt++;
    }
    return cnt;
}

int main() {
    ifstream fin("closing.in");
    ofstream fout("closing.out");

    int N, M; fin >> N >> M;

    vector<unordered_set<int>> adj_list(N);

    unordered_set<int> valid_starts;
    for (int i=0; i<N; i++) valid_starts.insert(i);

    for (int i=0; i<M; i++) {
        int a,b; fin >> a >> b;
        adj_list[a-1].insert(b-1);
        adj_list[b-1].insert(a-1);
    }

    int expected_visited_count = N;
    for (int i=0; i<N; i++) {
        int num_visited = bfs(adj_list, valid_starts);
        if (num_visited == expected_visited_count) {
            fout << "YES" << endl;
        } else {
            fout << "NO" << endl;
        }

        expected_visited_count--;

        int barn_to_remove;
        fin >> barn_to_remove;
        barn_to_remove--;
        valid_starts.erase(barn_to_remove);

        auto afflicted_barns = adj_list[barn_to_remove];
        for (auto const&barn : afflicted_barns) {
            adj_list[barn].erase(barn_to_remove);
        }
        adj_list[barn_to_remove].clear();
    }
}
