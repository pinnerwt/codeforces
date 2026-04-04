#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    int n;
    int ans;
    int tmp;
    cin >> t;
    while (t--) {
      cin >> n;
      ans = 0;
      for (int i=0; i<n; ++i) {
        cin >> tmp;
	// If p_i < i, then the chair can be sit.
	if (tmp < i + 2) {
		ans += 1;
	}
      }
      cout << ans << endl;
    }

    return 0;
}
