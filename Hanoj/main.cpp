#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Move {
    int from;
    int to;
};

bool allOnOneStack(const vector<vector<int>>& stacks, int n) {
    for (const auto& stack : stacks) {
        if (!stack.empty() && stack[0] == n)
            return true;
    }
    return false;
}

int main() {
    ifstream fin("han/in/han0e.in");
    if (!fin.is_open()) {
        cerr << "Nie można otworzyć pliku!" << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;

    vector<vector<int>> stacks(m);
    for (int i = 0; i < m; i++) {
        int k;
        fin >> k;
        stacks[i].push_back(k);
        for (int j = 0; j < k; j++) {
            int block;
            fin >> block;
            stacks[i].push_back(block);
        }
    }
    fin.close();

    vector<int> ile_moves(n + 1, 0);
    vector<Move> moves;
    int iterations = 0;
    const int MAX_ITERATIONS = n * 10;

    while (!allOnOneStack(stacks, n) && iterations < MAX_ITERATIONS) {
        iterations++;

        vector<int> gdzie(n + 1, 0);
        vector<int> tops(m, 0);
        vector<int> bottoms(m, 0);

        // Pozycje klocków
        for (int i = 0; i < m; i++) {
            vector<int>& stack = stacks[i];
            if (stack.size() < 2) continue;
            for (int j = 1; j < (int)stack.size(); j++) {
                gdzie[stack[j]] = i;
            }
        }

        // top/bottom każdego stosu
        for (int i = 0; i < m; i++) {
            vector<int>& stack = stacks[i];
            if (stack.size() <= 1 || stack[0] == 0) {
                tops[i] = 0;
                bottoms[i] = 0;
            } else {
                bottoms[i] = stack.back();
                tops[i] = stack[1];
            }
        }

        // wybór klocka z najmniejszą liczbą ruchów
        int min_moves = 1e9;
        int block = -1;
        for (int j = 1; j <= n; j++) {
            if (ile_moves[j] < min_moves) {
                min_moves = ile_moves[j];
                block = j;
            } else if (ile_moves[j] == min_moves && j < block) {
                block = j;
            }
        }

        // wybór docelowego stosu
        int witch_stack = 0;
        int gap = -100000;
        for (int i = 0; i < m; i++) {
            int ngap = bottoms[i] - block;
            if (ngap < 0) {
                if (ngap > gap) {
                    gap = ngap;
                    witch_stack = i + 1;
                }
            }
        }

        ile_moves[block]++;



        if (witch_stack == 0) {
            cout << "-1 Brak Rozwiązań" << endl;
            return 0;
        }


        int from_stack_idx = gdzie[block];
        int to_stack_idx = witch_stack - 1;

        stacks[from_stack_idx][0]--;
        stacks[to_stack_idx][0]++;

        auto& from_stack = stacks[from_stack_idx];
        int block_pos = -1;
        for (int i = 0; i < from_stack.size(); i++) {
            if (from_stack[i] == block) {
                block_pos = i;
                break;
            }
        }

        if (block_pos != -1) {
            from_stack.erase(from_stack.begin() + block_pos);
        }

        stacks[to_stack_idx].push_back(block);
        moves.push_back({from_stack_idx + 1, to_stack_idx + 1});
    }

    if (iterations >= MAX_ITERATIONS) {
        cout << "-1 Przekroczono limit iteracji" << endl;
        return 0;
    }

    cout << moves.size() << endl;
    for (const auto& move : moves) {
        cout << move.from << " " << move.to << endl;
    }



    return 0;
}
