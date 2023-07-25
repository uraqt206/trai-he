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

const int N = 1e6+1;
int n, dp[N], prv[N];
ii a[N];

int main() {
  setIO("input");

  cin >> n;

  foru(i, 1, n) {
    cin >> a[i].fi;
    a[i].se = i;
  }
  sort(a+1, a+n+1);

  int j = 1;
  dp[1] = 1; prv[1] = 1;
  foru(i, 2, n) {
    while (a[j].fi + a[j+1].fi <= a[i].fi) ++j;
    dp[i] = i-j+1;
    prv[i] = j;
  }

  int pos = -1; 
  foru(i, 1, n) if (pos == -1 || dp[pos] < dp[i]) pos = i;

  vector<int> seg;
  foru(i, prv[pos], pos) seg.push_back(a[i].se);

  sort(all(seg));
  cout << dp[pos] << "\n";  
  for(int x : seg) cout << x << " ";
}