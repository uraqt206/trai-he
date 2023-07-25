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

const int N = 5005;

string s;
ll dp[N], n, a, b;
int same[N][N];

int main() {
  setIO("input");

  cin >> n >> a >> b >> s;
  s = ":" + s;
  
  foru(i, 1, n)
    foru(j, 1, n) 
      same[i][j] = (s[i] != s[j] ? 0 : same[i-1][j-1] + 1);
  
  foru(i, 1, n) {
    dp[i] = dp[i-1] + a;

    int mx = 0;
    ford(j, i, 1) {
      int can = i-j;
      can = min(can, same[i][j]);
      mx = max(mx, can);
    }
    
    foru(j, 1, mx) {
      dp[i] = min(dp[i], dp[i-j] + b);
    }
  }
  
  cout << dp[n];
}