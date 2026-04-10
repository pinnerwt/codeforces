#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
      int n, k;
      cin >> n >> k;
      vector<int> a(n + 2);
      for (int i = 1; i <= n; i++) cin >> a[i];
      vector<int> p(k);
      for (int i = 0; i < k; i++) cin >> p[i];

      int x = a[p[0]];
      a[0] = x;
      a[n + 1] = x;

      // Special indices with sentinels at boundaries
      vector<int> sp = {0};
      for (int i = 0; i < k; i++) sp.push_back(p[i]);
      sp.push_back(n + 1);

      int W = 0, W_max = 0;
      for (int i = 0; i + 1 < (int)sp.size(); i++) {
        // Count wrong blocks in open interval (sp[i], sp[i+1])
        int w = 0;
        bool in_wrong = false;
        for (int j = sp[i] + 1; j < sp[i + 1]; j++) {
          if (a[j] != x) {
            if (!in_wrong) {
              w++;
              in_wrong = true;
            }
          } else {
            in_wrong = false;
          }
        }
        W += w;
        W_max = max(W_max, w);
      }

      cout << max(W, 2 * W_max) << "\n";
    }
    return 0;
}
