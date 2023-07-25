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

const int MAX = 50;
vector<vector<int>> per;
double dp[MAX+1][40321];
int n, m;
vector<int> a;

int get(vector<int> a) {
  return lower_bound(all(per), a) - per.begin();
}

int main() {
  setIO("input");

  cin >> n;
  a.resize(n);
  for(auto &x : a) { cin >> x; --x; }

  vector<int> tmp(n);
  iota(all(tmp), 0);
  do {
    per.emplace_back(tmp);
  } while (next_permutation(all(tmp)));
  sort(all(per));

  dp[0][get(a)] = 1.0;
  
  foru(step, 0, MAX-1) {
    foru(state, 0, sz(per)-1) {
      vector<int> &at = per[state];
      bool opt = (step % 2 == 0);
      
      int cnt = 0;
      if (opt) { foru(i, 0, n-2) if (at[i+1] < at[i]) ++cnt; }
      else cnt = n-1;

      foru(i, 0, n-2) {
        if (opt && at[i+1] > at[i]) continue;
        swap(at[i+1], at[i]);
        int idx = get(at);
        dp[step+1][idx] += dp[step][state] / (double)(cnt); 
        swap(at[i+1], at[i]);
      }
    }
  }

  double ans = 0;
  foru(i, 0, MAX) ans += (double) (i) * dp[i][0];
  // cout << setprecision(5) << fixed << ans << "\n";
  cout << dp[2][get({1, 2, 3})];
} 