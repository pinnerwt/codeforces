#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    while (b) { a %= b; swap(a, b); }
    return a;
}
int extended_gcd(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  int x1, y1;
  int d = extended_gcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * ((int)a / (int)b);
  return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
      int n, m, a, b;
      cin >> n >> m >> a >> b;
      int xn, yn, xm, ym, gcd_na, gcd_mb;
      gcd_na = extended_gcd(n, a, xn, yn);
      gcd_mb = extended_gcd(m, b, xm, ym);
      // cout << n << ' ' << a << ' ' << xn << ' ' << yn << "    " << gcd_na << ' ' << gcd_mb << ' ';
      // cout << m << ' ' << b << ' ' << xm << ' ' << ym << "    " << gcd(abs(yn), abs(ym));
      if (gcd_na == 1 && gcd_mb == 1 && gcd(n, m) <= 2) {
        cout << "YES" << endl;
      }
      else {
        cout << "NO" << endl;
      }
      // Note that we must alternate. So if the quotients are equal, we still can't parcour the grids.
    }
    return 0;
}
