#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
  while(b) { a%= b; swap(a, b); }
  return a;
}

int lcm(int a, int b) {
  int v_gcd = gcd(a, b);
  return v_gcd * (a / v_gcd) * (b / v_gcd);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    int second_last;
    int last;
    int current;
    int n;
    int ans;
    cin >> t;
    while (t--) {
      second_last = 1;
      last = 1;
      current = 1;
      cin >> n;
      vector<int> lcms (n, INT_MAX);
      for (int i=0; i<n; ++i) {
        cin >> current;
        // Find gcd of last, current A.
        // Find gcd of second_last, last B.
        // Then last is updatable iff lcm(A, B) < b_i
        if (i == 1) {
          lcms[0] = lcm(last, current);
        }
        if (i > 1) {
          int A = gcd(second_last, last);
          int B = gcd(last, current);
          lcms[i-1] = lcm(A, B);
          // cout << second_last << ' ' << last << ' ' << lcms[i] << ' ' << current << endl;
          if (lcms[i] == last) {
            lcms[i] = INT_MAX;
          }
        }
        if (i == n - 1) {
          lcms[i] = lcm(last, current);
        }
        second_last = last;
        last = current;
      }
      ans = 0;
      for (int i=0; i<n; ++i) {
        cin >> current;
        if (current >= lcms[i]) {
          ans += 1;
        }
      }
      cout << ans << endl;
    }
    return 0;
}
