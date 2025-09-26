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
https://usaco.org/index.php?page=viewproblem2&cpid=573
USACO 2015 December Contest, Gold
Problem 1. High Card Low Card (Gold)
*/
int main() {
    ifstream fin("cardgame.in");
    ofstream fout("cardgame.out");

    int N; fin >> N;

    vector<bool> bitmap(2*N, false);
    vector<int> op_cards_first_half;
    vector<int> op_cards_second_half;
    for (int i=0; i<N; i++) {
        int x; fin >> x;
        if (i < N/2) {
            op_cards_first_half.push_back(x-1);
        } else {
            op_cards_second_half.push_back(x-1);
        }
        bitmap[x-1] = true;
    }
    sort(op_cards_first_half.begin(), op_cards_first_half.end(), std::greater<int>());
    sort(op_cards_second_half.begin(), op_cards_second_half.end());

    deque<int> my_cards_first;
    deque<int> my_cards_second;
    for (int i=0; i<2*N; i++){
        if (!bitmap[i]) {
            if (my_cards_second.size() < N/2) {
                // cout << "f" << " " << i << endl;
                my_cards_second.push_back(i);
            } else {
                // cout << "s" << " " << i << endl;
                my_cards_first.push_front(i);
            }
        }
    }

    // first half
    int won = 0;

    for (auto const& op_card:op_cards_first_half) {
        if (my_cards_first.front() > op_card) {
            my_cards_first.pop_front();
            won++;
        } else {
            my_cards_first.pop_back();
        }
    }

    for (auto const& op_card:op_cards_second_half) {
        if (my_cards_second.front() < op_card) {
            my_cards_second.pop_front();
            won++;
        } else {
            my_cards_second.pop_back();
        }
    }


    fout << won << endl;
}
