#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    int n;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i=0; i<n; ++i) {
            cout << i + 1 << ' ' << n + 2 * i + 1 << ' ' << n + 2 * i + 2<< ' ';
        }
        cout << endl;
    }



    return 0;
}
