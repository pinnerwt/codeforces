#include <bits/stdc++.h>
using namespace std;

int count_adjacent_pairs(string &s) {
  int m = s.size();
  int count = 0;
  for (int i = 0; i < m - 1; ++i) {
    if (s[i] == '(' && s[i+1] == ')') {
      ++count;
    }
  }
  return count;
}

int count_outer_brackets(string &s) {
  int m = s.size();
  vector<int> match(m, -1);
  stack<int> indices;
  for (int i=0; i<m; i++) {
    if (s[i] == ')') {
      match[indices.top()] = i;
      indices.pop();
    }
    else {
      indices.push(i);
    }
  }
  int count = 0;
  int l = 0;
  int r = m-1;
  while (match[l] == r) {
    ++l;
    --r;
    ++count;
  }
  return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
      int n;
      string s, t;
      cin >> n;
      cin >> s >> t;
      // count adjacent pairs
      if (count_adjacent_pairs(s) == count_adjacent_pairs(t) && count_outer_brackets(s) == count_outer_brackets(t)) {
        cout << "YES" << endl;
      }
      else {
        cout << "NO" << endl;
      }
    }



    return 0;
}
