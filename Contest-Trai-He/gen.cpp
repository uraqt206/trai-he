x#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
 
#define foru(i, l, r) for(int i=(l); i<=(r); ++i)
#define ford(i, l, r) for(int i=(l); i>=(r); --i)
#define fore(x, v) for(auto &x : v)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
 
void setIO(string name="") {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  if (!name.empty()) {
    freopen((name + ".inp").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
  }
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int range(int l, int r) {
  return l + rng() % (r - l + 1);
}

int main() {
  freopen("test.inp", "w", stdout);

  int n = 100000, q = 500000;
  cout << n << " " << q << "\n";
  foru(i, 1, q) {
    int x = range(100000, 1000000000);
    cout << x << " ";
  }
  cout << "\n";
  while (q--) {
    int l = range(1, n);
    int r = range(l, n);
    int w = range(1500, 5000);
    cout << l << " " << r << " " << w << "\n";
  }
}