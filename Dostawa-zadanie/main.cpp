#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) cin >> grid[i];

    // Oblicz BFS tylko raz
    vector<vector<int>> dist(n, vector<int>(n, -1));
    queue<pair<int,int>> que;

    que.push({0, 0});
    dist[0][0] = 0;

    constexpr int dx[4] = {-1, 1, 0, 0};
    constexpr int dy[4] = {0, 0, -1, 1};

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
    map<int, int, greater<int>> dist_count;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'F' && dist[i][j] != -1) {
                dist_count[dist[i][j]]++;
            }
        }
    }

    // Cache dla wyniku - obliczaj tylko gdy się zmienia
    int cached_result = -1;
    bool needs_recalc = true;

    auto calculate_result = [&]() {
        if (!needs_recalc) return cached_result;

        int res = 0;
        int idx = 0;

        for (const auto& [d, cnt] : dist_count) {
            res = max(res, d + idx + cnt - 1);
            idx += cnt;
        }

        cached_result = res;
        needs_recalc = false;
        return res;
    };

    cout << calculate_result() << '\n';

    // Przetwarzaj zmiany
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;

        int d = dist[x][y];

        if (grid[x][y] == 'F') {
            grid[x][y] = '.';
            if (--dist_count[d] == 0) {
                dist_count.erase(d);
            }
            needs_recalc = true;
        } else if (grid[x][y] == '.') {
            grid[x][y] = 'F';
            dist_count[d]++;
            needs_recalc = true;
        }

        cout << calculate_result() << '\n';
    }

    return 0;
}