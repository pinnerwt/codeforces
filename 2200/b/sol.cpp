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
    int n;
    int tmp;
    int tmp_last;
    bool non_decreasing;
    cin >> t;
    while (t--) {
      cin >> n;
      // input as
      tmp_last = 0;
      non_decreasing = false;
      for (int i=0; i<n; ++i) {
        cin >> tmp;
        if (tmp < tmp_last) {
          non_decreasing = true;
        }
        tmp_last = tmp;
      }
      if (!non_decreasing) {
        cout << n << endl;
      }
      else {
        cout << 1 << endl;
      }
    }



    return 0;
}
