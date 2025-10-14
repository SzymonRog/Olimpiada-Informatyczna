#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream fin("dos/in/dos0c.in");
    if (!fin.is_open()) {
        cerr << "Nie mozna otworzyc pliku!" << endl;
        return 1;
    }

    int n, q;
    fin >> n >> q;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) fin >> grid[i];

    // Oblicz BFS tylko raz
    vector<vector<int>> dist(n, vector<int>(n, -1));
    queue<pair<int,int>> que;

    que.push({0, 0});
    dist[0][0] = 0;

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    while (!que.empty()) {
        auto [x, y] = que.front();
        que.pop();

        for (int j = 0; j < 4; j++) {
            int nx = x + dx[j];
            int ny = y + dy[j];

            if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
            if (grid[nx][ny] == '#') continue;
            if (dist[nx][ny] != -1) continue;

            dist[nx][ny] = dist[x][y] + 1;
            que.push({nx, ny});
        }
    }

    // Zliczamy forty według odległości (malejąco)
    map<int, int, greater<int>> dist_count; // sortowane malejąco

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'F' && dist[i][j] != -1) {
                dist_count[dist[i][j]]++;
            }
        }
    }

    // Obliczanie wyniku bez tworzenia wektora
    auto calculate_result = [&]() {
        int res = 0;
        int idx = 0;

        for (auto [d, cnt] : dist_count) {
            // Dla wszystkich fortów o odległości d
            for (int i = 0; i < cnt; i++) {
                res = max(res, d + idx);
                idx++;
            }
        }
        return res;
    };

    cout << calculate_result() << endl;

    // Przetwarzaj zmiany
    for (int i = 0; i < q; i++) {
        int x, y;
        fin >> x >> y;
        x--; y--;

        int d = dist[x][y];

        if (grid[x][y] == 'F') {
            grid[x][y] = '.';
            dist_count[d]--;
            if (dist_count[d] == 0) {
                dist_count.erase(d);
            }
        } else if (grid[x][y] == '.') {
            grid[x][y] = 'F';
            dist_count[d]++;
        }

        cout << calculate_result() << endl;
    }

    return 0;
}