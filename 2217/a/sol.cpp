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
      int n, k;
      cin >> n >> k;
      int sum = 0;
      int tmp;
      for (int i=0; i<n; ++i) {
        cin >> tmp;
        sum += tmp;
      }
      if (((k * n) % 2 == 1) && ((sum % 2) == 0)) {
        cout << "NO" << endl;
      }
      else {
        cout << "YES" << endl;
      }
    }



    return 0;
}
