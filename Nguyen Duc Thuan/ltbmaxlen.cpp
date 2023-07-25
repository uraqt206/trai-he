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

const ll LINF = 1e18;
const int N = 5e5+5;
int n;
pair<ll, int> info[N];
ll ret = 0, dp[N][3];

int main() {
  setIO("input");

  cin >> n;

  foru(i, 1, n) {
    cin >> info[i].fi >> info[i].se;
  }
  
  sort(begin(info)+1, begin(info)+n+1);
  memset(dp, -0x3f, sizeof(dp));
  foru(i, 1, n) {
    dp[i][0] = info[i].fi + info[i].se;
    dp[i][1] = max(dp[i-1][1], dp[i-1][0]) + info[i].se;
    dp[i][2] = max(dp[i-1][2], max(dp[i-1][0], dp[i-1][1]) - info[i].fi + info[i].se);
    ret = max(ret, max(dp[i][2], ll(info[i].se)));
  } 
  cout << ret;
}