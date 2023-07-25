#include <bits/stdc++.h>
#include <chrono>
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

mt19937 rng(chrono::steady_clock().now().time_since_epoch().count());

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

// segment tree here
ll sgt[N * 4], lazy[N * 4];

void app(int id) {
  lazy[id*2] += lazy[id];
  lazy[id*2+1] += lazy[id];
  sgt[id*2] -= lazy[id];
  sgt[id*2+1] -= lazy[id];
  lazy[id] = 0;
}

void propaganda(int id, int lb, int rb) {
  if (lb == rb) {
    for(int i : divs[lb]) if ((cnt[i] -= 1) == 0) {
      ans[i] = now;
    }
    sgt[id] = LINF;
    return;
  }
  app(id);
  int mb = (lb + rb) >> 1;
  if (sgt[id*2] <= 0) propaganda(id*2, lb, mb);
  if (sgt[id*2+1] <= 0) propaganda(id*2+1, mb+1, rb);
  sgt[id] = min(sgt[id*2], sgt[id*2+1]);
}

void build(int id, int lb, int rb) {
  if (lb ^ rb) {
    int mb = (lb + rb) >> 1;
    build(id*2, lb, mb);
    build(id*2+1, mb+1, rb);
    sgt[id] = min(sgt[id*2], sgt[id*2+1]);
  } else sgt[id] = a[lb];
}

void upd(int id, int lb, int rb, int l, int r, int v) {
  if (l <= lb && rb <= r) {
    lazy[id] += v;
    if ((sgt[id]-=v) <= 0) propaganda(id, lb, rb);
    return;
  } 
  if (rb < l || lb > r) {
    return;
  }
  app(id);
  int mb = (lb + rb) >> 1;
  upd(id*2, lb, mb, l, r, v);
  upd(id*2+1, mb+1, rb, l, r, v);
  sgt[id] = min(sgt[id*2], sgt[id*2+1]);
}

int cnt2[N], b[N], c[N], ans2[N];

void upd2(int l, int r, int v) {
  foru(i, l, r) {
    if (b[i] <= 0) continue;
    if ((b[i]-=v) <= 0) for(int j : divs[i]) if (--cnt2[j] == 0) ans2[j] = now;
  }
}

int range(int l, int r) { 
  return rng() % (r - l + 1) + l;
}

int main() {
  setIO("input");
  prep();
    
//   cin >> n >> q;
int trie = 1;
while (trie--) {
  memset(cnt, 0, sizeof(cnt));
  memset(cnt2, 0, sizeof(cnt2));
  memset(ans, 0, sizeof(ans));
  memset(ans2, 0, sizeof(ans2));
  memset(lazy, 0, sizeof(lazy));
  memset(sgt, 0, sizeof(sgt));

  n = range(5000, 5000);
  q = range(5000, 5000);

  foru(i, 1, n) {
    // cin >> a[i];
    a[i] = range(100, 10000);
    b[i] = a[i];
    c[i] = a[i];
    for(int j : divs[i])  {
      cnt[j] += 1;
      cnt2[j] += 1;
    }
  }

  build(1, 1, n);

  for(now=1; now<=q; ++now) {
    int u, v, w;
    // cin >> u >> v >> w;
    u = range(1, n);
    v = range(u, n);
    w = range(100, 10000);
    upd(1, 1, n, u, v, w);
    upd2(u, v, w);
  }

  foru(i, 1, n) {
    int t1 = (cnt[i] > 0 ? -1 : ans[i]);
    // cout << t1 << " ";
    int t2 = (cnt2[i] > 0 ? -1 : ans2[i]);
    cout << t1 << " ";
    if (t1 != t2) {

      cout << n << " " << q << "\n";
      foru(i, 1, n) cout << c[i] << " ";
      cout << "\n";
      return 0;
    }
  }
}
}