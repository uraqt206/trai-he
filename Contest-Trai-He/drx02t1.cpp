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

const int N = 1e5+5;
int n, k, cnt[26], disc;
string s;

void add(char c) {
  if (++cnt[c-'a'] == 1) ++disc;
}

void rem(char c) {
  if (--cnt[c-'a'] == 0) --disc;
}

int main() {
  setIO("drx02t1");

  cin >> n >> k >> s;
  
  int j = 0;
  ll ans = 0;
  foru(i, 0, n-1) {
    add(s[i]);
    while (disc >= k) {
      rem(s[j]);
      if (disc < k) {
        add(s[j]);
        break;
      } else ++j;
    }
    if (disc >= k) ans += j+1;
  }

  cout << ans;
}