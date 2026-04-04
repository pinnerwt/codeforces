#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAXP = 110000;
    vector<bool> is_prime (MAXP, true);
    is_prime[0] = is_prime[1] = false;
    for (int i=2; i * i < MAXP; i++) {
      if (is_prime[i]) {
        for (int j = i*i; j < MAXP; j+= i) {
          is_prime[j] = false;
        }
      }
    }
    vector<long long> p;
    for (int i=2; i<MAXP; ++i) {
      if (is_prime[i]) p.push_back(i);
    }

    int t;
    int n;
    cin >> t;
    while (t--) {
      cin >> n;
      for (int i=0; i < n; ++i) {
        if (i) cout << ' ';
        if (i == 0) cout << p[0];
        else if (i == n - 1) cout << p[n-2];
        else cout << p[i - 1] * p[i];
      }
      cout << '\n';
    }
    return 0;
}
