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
        vector<int> a(n);
        for (int i=0; i < n; ++i) {
          cin >> a[i];
        }

        // Binary trie for maximum XOR pair
        vector<array<int,2>> tr(1, {-1, -1});

        auto insert = [&](int x) {
            int u = 0;
            for (int b = 29; b >= 0; b--) {
                int bit = (x >> b) & 1;
                if (tr[u][bit] == -1) {
                    tr[u][bit] = tr.size();
                    tr.push_back({-1, -1});
                }
                u = tr[u][bit];
            }
        };

        auto query = [&](int x) -> int {
            int u = 0, res = 0;
            for (int b = 29; b >= 0; b--) {
                int bit = (x >> b) & 1;
                if (tr[u][1 - bit] != -1) {
                    res |= 1 << b;
                    u = tr[u][1 - bit];
                } else {
                    u = tr[u][bit];
                }
            }
            return res;
        };

        for (int x : a) insert(x);

        int ans = 0;
        for (int x : a) ans = max(ans, query(x));
        cout << ans << '\n';
    }

    return 0;
}
