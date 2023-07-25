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
  if (!name.empty()) {
    freopen((name + ".inp").c_str(), "r", stdin);
    freopen((name + ".out").c_str(), "w", stdout);
  }
}

int n, m, a[1000100];

int main() {
  setIO("input");
  cin >> n;

  vector<int> nw;
  foru(i, 1, n) {
    cin >> a[i];
    nw.push_back(a[i]);
  }
  int ans = 0;
  ford(i, 29, 0) {
    // if (i == 0) {
    //   for(int x : nw) cout << x << " ";
    //   cout << "\n";
    // }
    // if (sz(nw) < 2);
    vector<int> at[2];
    for(int x : nw) at[x>>i&1].push_back(x);

    if (sz(at[1]) >= 2) {
      nw = at[1];
      ans += (1 << i);
    }
  }
  cout << ans;
}