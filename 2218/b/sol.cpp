#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    int current;
    cin >> t;
    while (t--) {
        int maxi = -70;
        int total_sum = 0;

        for (int i=0; i<7; ++i) {
            cin >> current;
            if (current > maxi) {
                maxi = current;
            }
            total_sum += current;
        }
        cout << -total_sum + 2 * maxi << endl;
    }



    return 0;
}
