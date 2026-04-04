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
        cout << n - i << ' ';
      }
      cout << endl;
    }
    return 0;
}
