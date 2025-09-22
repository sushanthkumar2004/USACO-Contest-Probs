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


USACO 2016 January Contest, Silver
Problem 1. Angry Cows

*/

//https://usaco.org/index.php?page=viewproblem2&cpid=594

using namespace std;

bool simulate(vector<int>& x, int R, int K) {
    int leftPtr = 0;
    int rightPtr = 0;
    int numCowsNeeded = 0;
    while (leftPtr < x.size()) {
        while (rightPtr < x.size() && x[rightPtr] - x[leftPtr] <= 2*R) {
            rightPtr++;
        }
        // cout << "L" << leftPtr << " " <<  rightPtr << endl;
        numCowsNeeded ++;
        leftPtr = rightPtr;
        // cout << leftPtr << endl;
    }

    // cout << "numCowsNeeded" << numCowsNeeded << endl;

    return numCowsNeeded <= K;
}

int main() {
    ifstream fin("angry.in");
    ofstream fout("angry.out");

    int N, K; fin >> N >> K;

    vector<int> x; 
    for (int i=0; i<N; i++) {
        int xx; fin >> xx;
        x.push_back(xx);
    }

    sort(x.begin(), x.end());

    int lo = 0;
    int hi = 1000000000;
    while (lo < hi) {
        int mid = (lo + hi)/2;
        if (!simulate(x, mid, K)) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    fout << lo << endl;
}
