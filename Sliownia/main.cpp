#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;
    if (n == 1 || n == 2 || n == 4 || n == 5 || n == 7 || n == 10 || n == 13) {
        cout << "NIE";
    } else {
        cout << "TAK";
    }
}
