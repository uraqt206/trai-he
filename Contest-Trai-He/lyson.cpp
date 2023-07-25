#include <bits/stdc++.h>
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

const int INF = 1e9;
const int N = 250000;

int theta, n, q, a[N], dp[N];
ll f[2][N][4];
char want;
int x, y;

// segment tree
int sgt[N * 4];

void upd(int id, int lb, int rb, int i, int v) {
  if (lb ^ rb) {
    int mb = (lb + rb) >> 1;
    if (i <= mb) upd(id*2, lb, mb, i, v);
    else upd(id*2+1, mb+1, rb, i, v);
    sgt[id] = max(sgt[id*2], sgt[id*2+1]);
  } else sgt[id] = v;
}

int query(int id, int lb, int rb, int l, int r) {
  if (l <= lb && rb <= r) return sgt[id];
  if (lb > r || rb < l) return -INF;
  int mb = (lb + rb) >> 1;
  return max(query(id*2, lb, mb, l, r), query(id*2+1, mb+1, rb, l, r));
}

// sub 4

void prep() {
  memset(f, -0x3f, sizeof(f));
  f[0][0][3] = f[1][n+1][3] = 0;

  foru(i, 1, n) {
    foru(j, 0, 3) f[0][i][j] = f[0][i-1][j];
    f[0][i][1] = max(f[0][i][1], f[0][i-1][3] - a[i]);
    f[0][i][2] = max(f[0][i][2], f[0][i-1][3] + a[i]);
    f[0][i][3] = max(f[0][i][3], max(f[0][i-1][1] + a[i], f[0][i-1][2] - a[i]));
    // cout << f[0][i][3] << " ";
  }
  // cout << "\n";

  ford(i, n, 1) {
    foru(j, 0, 3) f[1][i][j] = f[1][i+1][j];
    f[1][i][1] = max(f[1][i][1], f[1][i+1][3] - a[i]);
    f[1][i][2] = max(f[1][i][2], f[1][i+1][3] + a[i]);
    f[1][i][3] = max(f[1][i][3], max(f[1][i+1][1] + a[i], f[1][i+1][2] - a[i]));
    // cout << f[1][i][3] << " ";
  }
  // cout << "\n";
}

// sub 1

bool check(int l, int r) { 
  if (want == 'L') {
    if (l <= y && y <= r && x < l) return 0;
    if (l <= x && x <= r && y > r) return 0;
  }
  if (want == 'H') {
    if (l <= y && y <= r && x >= l) return 0;
    if (l <= x && x <= r && y <= r) return 0;
  }
  return 1;
}

int sub1() {
  foru(i, 0, n) dp[i] = -INF;
  dp[0] = 0;
  foru(i, 1, n) {
    int mx = a[i], mn = a[i];
    ford(j, i, 1) {
      mx = max(mx, a[j]);
      mn = min(mn, a[j]);
      if (check(j, i)) dp[i] = max(dp[i], dp[j-1] + mx - mn);
    }
  }
  return dp[n];
}

int sub2() {
  return query(1, 1, n, x, y-1);
}

int main() {
  setIO("input");

  cin >> theta >> n >> q;
  foru(i, 1, n) cin >> a[i]; 
  prep();
  foru(i, 1, n-1) upd(1, 1, n, i, f[0][i][3] + f[1][i+1][3]);

  if (theta <= 3) cout << sub1() << " ";
  else cout << f[0][n][3] << " ";

  foru(i, 1, q) {
    cin >> want >> x >> y;
    if (x > y) swap(x, y);
    if (theta <= 3) cout << sub1() << " ";
    else if (theta <= 5) cout << sub2() << " ";
  }
}