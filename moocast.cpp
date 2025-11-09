#include <iostream>
#include <fstream>
#include <unordered_set>
#include <queue>

using namespace std;

/*
https://usaco.org/index.php?page=viewproblem2&cpid=668


USACO 2016 December Contest, Silver
Problem 3. Moocast

  */

// max cows we can reach starting from x

int bfs(vector<vector<bool>>& adj_matrix, int cow_idx) {
    vector<bool> visited(adj_matrix.size(), false);
    queue<int> fringe;
    fringe.push(cow_idx);

    while (!fringe.empty()) {
        int top = fringe.front();
        fringe.pop();
        visited[top] = true;

        for (int i=0; i<adj_matrix.size(); i++) {
            if (adj_matrix[top][i] == true && !visited[i]) {
                fringe.push(i);
            }
        }
    }

    int cnt = 0;
    for (auto const&v: visited) {
        if (v) cnt++;
    }

    return cnt;
}

struct cow {
    int x;
    int y;
    int p;
};

int main() {
    ifstream fin("moocast.in");
    ofstream fout("moocast.out");

    int N; fin >> N;

    vector<vector<bool>> adj_matrix(N, vector<bool>(N, false));
    vector<cow> cows;
    for (int i=0; i<N; i++) {
        int x,y,p;
        fin >> x >> y >> p;
        cows.push_back({x,y,p});
    }

    for (int i=0; i<N; i++) {
        auto cowi = cows[i];
        for (int j=0; j<N; j++) {
            auto cowj = cows[j];
            //  check if i can reach j
            if ((cowi.x - cowj.x) * (cowi.x - cowj.x) + (cowi.y - cowj.y) * (cowi.y - cowj.y) <= cowi.p * cowi.p) {
                adj_matrix[i][j] = true;
            }
        }
    }

    // for (int i=0; i<N; i++) {
    //     for (int j=0; j<N ; j++) {
    //         cout << adj_matrix[i][j] << " ";
    //     } cout << endl;
    // }

    int maxBrdcst = 0;

    for (int i=0; i<N; i++) {
        // cout << "bfs(adj_matrix, i)" << bfs(adj_matrix, i) << endl;
        maxBrdcst = max(maxBrdcst, bfs(adj_matrix, i));
    }

    fout << maxBrdcst;
}
