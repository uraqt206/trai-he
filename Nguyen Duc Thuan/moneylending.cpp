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
const int INF = 2e9;
const int N = 5005;

struct service {
  ll a, b, k;
  service(ll _a=0, ll _b=0, ll _k=0) : a(_a), b(_b), k(_k) {}
  bool operator < (const service &s) const {
    return b > s.b;
  }
};

int n, m, k;
ll dp[N][N];
vector<service> sv;

int main() {
  setIO("input");

  cin >> n;
  foru(i, 1, n) {
    int a, b, k;
    cin >> a >> b >> k;
    sv.emplace_back(a, b, k);
  }

  sort(all(sv));
  memset(dp, -0x3f, sizeof(dp));
  dp[0][0] = 0;

  foru(i, 0, n-1) {
    foru(j, 0, i) if (dp[i][j] > -LINF) {
      ll cur = dp[i][j];
      dp[i+1][j+1] = max(dp[i+1][j+1], cur + sv[i].a - sv[i].b * j);
      dp[i+1][j] = max(dp[i+1][j], cur + sv[i].a - sv[i].b * sv[i].k);
      dp[i+1][j] = max(dp[i+1][j], cur);
    }
  }

  cout << *max_element(begin(dp[n]), end(dp[n]));
}