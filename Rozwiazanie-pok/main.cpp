#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
using namespace std;

bool czy_sasiedzi(pair<int,int> a, pair<int,int> b) {
    int dr = abs(a.first - b.first);
    int dc = abs(a.second - b.second);
    return dr <= 1 && dc <= 1 && (dr > 0 || dc > 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    map<int, pair<int,int>> current_pos;
    map<int, pair<int,int>> target_pos;
    vector<tuple<int,int,int>> moves;


    int n, king_number;
    cin >> n >> king_number;
    vector<vector<int>> grid(n,vector<int> (n,0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            grid[i][j] = x;

            if (x > 0) {
                current_pos[x] = {i,j};
            }

        }
    }

    vector<vector<int>> final_grid(n,vector<int> (n,0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            final_grid[i][j] = x;

            if (x > 0) {
                target_pos[x] = {i,j};
            }
        }
    }




    return 0;
}