#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> stacks(m);
    vector<int> stack_size(m);

    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        stack_size[i] = k;
        stacks[i].resize(k);
        for (int j = 0; j < k; j++) {
            cin >> stacks[i][j];
        }
    }

    // Sprawdź czy każdy klocek na osobnym stosie
    bool one_per_stack = (n == m);
    if (one_per_stack) {
        for (int i = 0; i < m; i++) {
            if (stack_size[i] != 1) {
                one_per_stack = false;
                break;
            }
        }
    }

    if (one_per_stack) {
        // Stwórz mapę: klocek -> stos
        vector<int> block_to_stack(n + 1);
        for (int i = 0; i < m; i++) {
            block_to_stack[stacks[i][0]] = i;
        }

        int target_stack = block_to_stack[1];

        cout << n - 1 << endl;
        for (int block = 0; block < n; block++) {
            cout << block_to_stack[block] + 2 << " " << target_stack + 1<< endl;
        }
        return 0;
    }

    vector<int> ile_moves(n + 1, 0);
    vector<pair<int, int>> moves;
    moves.reserve(n);

    vector<int> gdzie(n + 1);
    vector<int> bottoms(m);

    const int MAX_ITERATIONS = n * 10;

    for (int iterations = 0; iterations < MAX_ITERATIONS; iterations++) {
        // Sprawdź czy wszystkie klocki na jednym stosie
        bool done = false;
        for (int i = 0; i < m; i++) {
            if (stack_size[i] == n) {
                done = true;
                break;
            }
        }
        if (done) break;

        // Pozycje klocków i bottomy
        for (int i = 0; i < m; i++) {
            int sz = stack_size[i];
            if (sz > 0) {
                bottoms[i] = stacks[i][sz - 1];
                for (int j = 0; j < sz; j++) {
                    gdzie[stacks[i][j]] = i;
                }
            } else {
                bottoms[i] = 0;
            }
        }

        // Wybór klocka z najmniejszą liczbą ruchów
        int block = 1;
        int min_mv = ile_moves[1];
        for (int j = 2; j <= n; j++) {
            if (ile_moves[j] < min_mv) {
                min_mv = ile_moves[j];
                block = j;
            }
        }

        // Wybór docelowego stosu
        int witch_stack = -1;
        int gap = -100000;
        for (int i = 0; i < m; i++) {
            int ngap = bottoms[i] - block;
            if (ngap < 0 && ngap > gap) {
                gap = ngap;
                witch_stack = i;
            }
        }

        if (witch_stack == -1) {
            cout << -1 << endl;
            return 0;
        }

        ile_moves[block]++;

        int from_stack_idx = gdzie[block];

        // Usuń klocek ze stosu źródłowego - OPTYMALIZACJA: swap zamiast erase
        int from_sz = stack_size[from_stack_idx];
        for (int i = 0; i < from_sz; i++) {
            if (stacks[from_stack_idx][i] == block) {
                // Zamień z ostatnim i zmniejsz rozmiar
                stacks[from_stack_idx][i] = stacks[from_stack_idx][from_sz - 1];
                stack_size[from_stack_idx]--;
                break;
            }
        }

        // Dodaj do stosu docelowego
        int to_sz = stack_size[witch_stack];
        if (to_sz >= stacks[witch_stack].size()) {
            stacks[witch_stack].push_back(block);
        } else {
            stacks[witch_stack][to_sz] = block;
        }
        stack_size[witch_stack]++;

        moves.emplace_back(from_stack_idx + 1, witch_stack + 1);
    }

    if (moves.size() >= MAX_ITERATIONS) {
        cout << -1 << endl;
        return 0;
    }

    cout << moves.size() << endl;
    for (const auto& [from, to] : moves) {
        cout << from << " " << to << endl;
    }

    return 0;
}