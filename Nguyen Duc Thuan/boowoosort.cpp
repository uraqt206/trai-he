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

const int N = 1e5+5;
int n, a[N], b[N];
map<int, int> ori[2], nw[2];

bool solve() {
  cin >> n;
  foru(i, 1, n) {
    cin >> a[i];
    b[i] = a[i];
  }
  ori[0].clear();
  ori[1].clear();
  nw[0].clear();
  nw[1].clear();
  sort(a+1, a+n+1);
  
  for(int i=1; i<=n; ++i) {
    ori[i&1][a[i]] += 1;
    nw[i&1][b[i]] += 1;
  }

  for(auto x : ori[0]) {
    if (nw[0][x.fi] != x.se) return 0;
  }

  for(auto x : ori[1]) {
    if (nw[1][x.fi] != x.se) return 0;
  }

  return 1;
}

int main() {
  setIO("input");

  int t;
  cin >> t;
  while (t--) cout << (solve() ? "YES\n" : "NO\n");
}