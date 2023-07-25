#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
 
#define foru(i, l, r) for(int i=(l); i<=(r); ++i)
#define ford(i, l, r) for(int i=(l); i>=(r); --i)
#define fore(x, v) for(auto &x : v)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define fi first
#define se second
 
void setIO(string name="") {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  if (fopen((name + ".inp").c_str(), "r")) {
    freopen((name + ".inp").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
  }
}

const int N = 5e5+5;
const int INF = 2e9+9;

ll sum_odd(int n) {
  if (n % 2 == 0) --n;
  ll cnt = (n+1)/2;
  return (n + 1) * cnt / 2;
}

ll sum(int n) {
  if (n == 0) return 0;
  return sum_odd(n) + sum(n/2);
}

int main() {
  setIO("input");

  int q;
  cin >> q;

  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << sum(r) - sum(l-1) << "\n";
  }
}