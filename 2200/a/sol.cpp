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
    int tmp_max;
    int tmp;
    vector<int> possible_ans;
    cin >> t;
    while (t--) {
      int n;
      cin >> n;
      tmp_max = 0;
      possible_ans.resize(0);
      for (int i=0; i<n; ++i) {
        cin >> tmp;
        if (tmp > tmp_max) {
          tmp_max = tmp;
          possible_ans.resize(0);
          possible_ans.push_back(tmp);
        } else if (tmp == tmp_max) {
          possible_ans.push_back(tmp);
        }
      }
      cout << possible_ans.size() << endl;
    }



    return 0;
}
