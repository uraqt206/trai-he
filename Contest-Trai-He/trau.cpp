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
    freopen((name + ".out2").c_str(), "w", stdout);
  }
}

const ll LINF = 1e18;
const int N = 5e5+5, V = 5e5;

int cnt[N];
vector<int> divs[V+1];

void prep() {
  foru(i, 1, V) {
    int j = i;
    while (j <= V) {
      divs[j].push_back(i);
      j += i;
    }
  }
}

int n, q, a[N], ans[N];
int now;

int main() {
  setIO("test");
  cin >> n >> q;
  memset(ans, 0x3f, sizeof(ans));
  prep();

  foru(i, 1, n) {
    cin >> a[i];
    if (a[i] > 0) fore(j, divs[i]) cnt[j] += 1;
  }

  foru(i, 1, n) {
    if (cnt[i] == 0) ans[i] = 0;
  }

  for(now=1; now<=q; ++now) {
    int l, r, w;
    cin >> l >> r >> w;
    foru(i, l, r) {
      if (a[i] <= 0) continue;
      if ((a[i] -= w) <= 0) fore(j, divs[i]) if (--cnt[j] == 0) ans[j] = min(ans[j], now);
    }
  }
  

  foru(i, 1, n) cout << (cnt[i] == 0 ? ans[i] : -1) << " ";
}