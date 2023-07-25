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

int lst[200002][26];
int n;
string s;

void solve(int l, int r) {
  if (l > r) return;
  int pos = -1;
  foru(i, 0, 25) if (lst[r][i] >= l) {
    pos = lst[r][i];
    break;
  }
  // if (pos == -1) return;
  cout << s[pos-1];
  solve(l, pos-1);
  solve(pos+1, r);
}

int main() {
  setIO("input");

  cin >> s;
  n = s.size();
  foru(i, 1, n) {
    foru(j, 0, 25) lst[i][j] = lst[i-1][j];
    lst[i][s[i-1]-'a'] = i;
  }

  solve(1, n);
}