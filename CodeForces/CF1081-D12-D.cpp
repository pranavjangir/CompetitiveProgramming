#include <bits/stdc++.h>
using namespace std;

vector<int> fa;

int find(int x) {
  return fa[x] <= 0 ? x : fa[x] = find(fa[x]);
}

int unite(int x, int y) {
  x = find(x);
  y = find(y);
  if(x != y) {
    fa[x] += fa[y];
    fa[y] = x;
  }
  return fa[x];
}

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  int n, m, k;
  cin >> n >> m >> k;

  fa.resize(n + 1);
  for (int i = 0; i < k; ++i) {
    int x;
    cin >> x;
    fa[x] = -1;
  }

  vector<tuple<int, int, int>> edges(m);
  for (auto& [w, u, v] : edges) {
    cin >> u >> v >> w;
  }

  sort(edges.begin(), edges.end());

  int ans = 0;
  for (auto [w, u, v] : edges) {
    if(u == v) continue;
    if(unite(u, v) == -k) {
      ans = w;
      break;
    }
  }

  for (int i = 1; i <= k; ++i) cout << ans << " ";
}
