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

const int LOG = 17;
const int INF = 1e9;
const int MOD = 1e9+7;
const int N = 1e5+1, V = 1e5;

int n, m, cnt[11][11];
int dp[2][N];

int knapsack(vector<ii> &a) {
  int n = a.size();
  memset(dp[0], -0x3f, sizeof(dp));
  dp[0][0] = 0;
  foru(i, 0, n-1) {
    int at = i&1, nxt = at^1;
    memset(dp[nxt], -0x3f, sizeof(dp[nxt]));
    foru(j, 0, m) if (dp[at][j] > -INF) {
      dp[nxt][j] = max(dp[nxt][j], dp[at][j]);
      if (j+a[i].fi <= m) dp[nxt][j+a[i].fi] = max(dp[nxt][j+a[i].fi], dp[at][j] + a[i].se);
    }
  }
  return *max_element(begin(dp[n&1]), end(dp[n&1]));
}

int main() {
  setIO("input");
  cin >> n >> m;
  foru(i, 1, n) {
    int w, v;
    cin >> w >> v;
    cnt[w][v] += 1;
  }
  vector<ii> objects;
  foru(w, 1, 10) {
    foru(v, 1, 10) if (cnt[w][v] > 0) {
      int copy = cnt[w][v];
      // cout << "from " << copy << " divide into \n";
      while (copy != 0) {
        int sum = 0;
        for(int j=0; j<LOG; ++j) {
          if (sum+(1<<j) <= copy) sum += (1 << j);
          else break;
          // cout << (1 << j) << " ";
          objects.emplace_back(w * (1 << j), v * (1 << j));
        }
        // cout << "\n";
        copy -= sum;
      }
    }
  }
  cout << knapsack(objects);
}