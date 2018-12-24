    #include <bits/stdc++.h>
    using namespace std;
     
    typedef long long ll;
    typedef pair <int, int> ii;
     
    const int Maxn = 100005;
    const int mod = 998244353;
     
    int n;
    int diag[Maxn], dif[Maxn];
    map <ii, int> M;
    int dp[Maxn][2];
     
    int main()
    {
        fill(diag, diag + Maxn, -1);
        fill(dif, dif + Maxn, -1);
        scanf("%d", &n);
        int m; scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            int r, c, val; scanf("%d %d %d", &r, &c, &val);
            if (r == c)
                if (diag[r] != -1 && diag[r] != val) {
                    printf("0\n"); return 0;
                } else diag[r] = val;
            else {
                if (r < c) swap(r, c);
                map <ii, int>::iterator it = M.find(ii(r, c));
                int oldval = it == M.end()? -1: it->second;
                int st = r - c;
                if (st == 1)
                    if (oldval == -1) M[ii(r, c)] = val;
                    else {
                        int wr = oldval != val;
                        if (dif[r] != -1 && dif[r] != wr) {
                            printf("0\n"); return 0;
                        } else dif[r] = wr;
                    }
                else if (st == 2)
                    if (oldval == -1) M[ii(r, c)] = val;
                    else {
                        int wr = oldval != val;
                        if (diag[r - 1] != -1 && diag[r - 1] != wr) {
                            printf("0\n"); return 0;
                        } else diag[r - 1] = wr;
                    }
                else if (oldval == -1) M[ii(r, c)] = val;
                     else if (oldval != val) {
                        printf("0\n"); return 0;
                     }
            }
        }
        dp[1][0] = 1;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < 2; j++) if (dp[i][j])
                for (int k = 0; k < 2; k++) {
                    if (diag[i] != -1 && diag[i] != k) continue;
                    if (dif[i] != -1 && dif[i] != (j != k)) continue;
                    dp[i + 1][k] = (dp[i + 1][k] + dp[i][j]) % mod;
                }
        int res = (dp[n + 1][0] + dp[n + 1][1]) % mod;
        ll rem = (ll(n) * n - n) / 2 - int(M.size());
        int a = 2;
        while (rem) {
            if (rem & 1) res = ll(res) * a % mod;
            rem >>= 1ll; a = ll(a) * a % mod;
        }
        cout << res << endl;
        return 0;
    }
