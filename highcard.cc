#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <climits>
#include <iomanip>

using namespace std;


/*
https://usaco.org/index.php?page=viewproblem2&cpid=571

USACO 2015 December Contest, Silver
Problem 2. High Card Wins
*/
int main() {
    ifstream fin("highcard.in");
    ofstream fout("highcard.out");

    int N; fin >> N;

    vector<bool> bitmap(2*N, false);
    vector<int> op_cards;
    for (int i=0; i<N; i++) {
        int x; fin >> x;
        op_cards.push_back(x-1);
        bitmap[x-1] = true;
    }
    sort(op_cards.begin(), op_cards.end(), std::greater<int>());

    deque<int> my_cards;
    for (int i=0; i<2*N; i++){
        if (!bitmap[i]) {
            my_cards.push_front(i);
        }
    }
    int won = 0;

    for (auto const& op_card:op_cards) {
        if (my_cards.front() > op_card) {
            my_cards.pop_front();
            won++;
        } else {
            my_cards.pop_back();
        }
    }
    fout << won << endl;
}
