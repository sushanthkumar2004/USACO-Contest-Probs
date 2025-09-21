#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>
//https://usaco.org/index.php?page=viewproblem2&cpid=666 
// obv binary search
using namespace std;

int main() {
    int N, Q; 
    ifstream fin("haybales.in");
    ofstream fout("haybales.out");

    fin >> N >> Q;
    vector<int> haybales(N);
    vector<int> prefixHay(N+1, 0);
    for (int i=0; i<N; i++) {
        int x; fin >> x;
        haybales[i] = x;
        prefixHay[i+1] = prefixHay[i] + 1;
    }


    sort(haybales.begin(), haybales.end());
    for (int i=0; i<Q; i++) {
        int A, B; fin >> A >>B;

        auto itA = lower_bound(haybales.begin(), haybales.end(), A);
        auto itB = upper_bound(haybales.begin(), haybales.end(), B);

        if (itA == haybales.end()) {
            fout << 0 << endl; 
        } else {
            int valA = *itA;
            int indxA;

            if (valA == A) {
                indxA = (itA - haybales.begin());
            } else {
                indxA = (itA - haybales.begin());
            }

            int indxB = (itB - haybales.begin());        
            // cout << indxA  << " " << indxB << endl;
            fout << prefixHay[indxB] - prefixHay[indxA] << endl;
        }


    }



}
