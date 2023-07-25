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

const int N = 3e5+5;
const int MOD = 1e9+7;

int n, m, a[N], pre[N];
bool ans[N];
vector<ii> querys;

int main() {
  setIO("input");
  cin >> n >> m;

  foru(i, 1, n) {
    cin >> a[i];
  }

  foru(i, 1, m) {
    int u, v;
    cin >> u >> v;
    querys.emplace_back(u, v);
  }

  foru(s, 0, 29) {
    foru(t, 0, 29) {
      foru(i, 1, n) {
        pre[i] = pre[i-1];
        if ((a[i] >> s & 1) && (a[i] >> t & 1)) pre[i] += 1;
      }

      foru(j, 0, m-1) if (!ans[j]) {
        int l = querys[j].fi, r = querys[j].se;
        if (!(a[l] >> s & 1)) continue;
        if (!(a[r] >> t & 1)) continue;
        ans[j] = ans[j] | (pre[r]-pre[l-1] > 0);
      }
    }
  }

  foru(i, 0, m-1) cout << (ans[i] ? "Yes\n" : "No\n");
}