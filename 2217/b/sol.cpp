#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    while (b) { a %= b; swap(a, b); }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
      int n, k, pk;
      cin >> n >> k;
      vector<int> as(n, 0);
      for (int i=0; i<n; ++i) {
        cin >> as[i];
      }
      cin >> pk;
      // starting from pk, looking at left/right. Count alternative numbers.
      int last = as[pk-1];
      int cnt_l = 0;
      for (int i=pk-2; i>=0; --i) {
        if (as[i] != last) {
          last = as[i];
          cnt_l += 1;
        }
      }
      last = as[pk-1];
      int cnt_r = 0;
      for (int i=pk; i< n; ++i) {
        if (as[i] != last) {
          last = as[i];
          cnt_r += 1;
        }
      }
      int ans = max(cnt_l, cnt_r);
      cout << ans + (ans % 2) << endl;
    }



    return 0;
}
