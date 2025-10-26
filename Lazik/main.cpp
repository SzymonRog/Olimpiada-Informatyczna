#include <bits/stdc++.h>
using namespace std;

string check(long long n, long long m) {
    string seq;
    long long g = gcd(m,n);

    if (n == 1) {
        seq = "P";
        return seq;
    }
    if (m == 1) {
        seq = "D";
        return seq;
    }

    if (g == 1) {
        seq = "DP";
    }
    else {

        if (g <= n - g && g <= m - 1) {
            seq = string(g - 1, 'D') + "P";
        } else if (g <= m - g && g <= n - 1) {
            seq = string(g - 1, 'P') + "D";
        } else {
            if (m <= n) {
                seq = "D" + string(g - 1, 'P');
            } else {
                seq = "P" + string( g - 1, 'D');
            }
        }
    }
    return seq;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m;
    cin >> n >> m;

    string seq;
    seq = check(n,m);
    cout << seq.size() << endl;
    cout << seq << endl;

    return 0;
}