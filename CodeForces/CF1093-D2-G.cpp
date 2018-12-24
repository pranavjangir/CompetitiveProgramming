/*
  Editorial Solution, same to same.
*/

#include <bits/stdc++.h>

using namespace std;

const int N = 200043;
const int INF = int(1e9);

int T[4 * N][32];
int A[4 * N][5];
int n, k;

void build(int v, int l, int r)
{
	if(l == r - 1)
	{
		for(int i = 0; i < (1 << k); i++)
		{
			int cur = 0;
			for(int j = 0; j < k; j++)
				if(i & (1 << j))
					cur += A[l][j];
				else
					cur -= A[l][j];
			T[v][i] = cur;
		}
	}
	else
	{
		int m = (l + r) / 2;
		build(v * 2 + 1, l, m);
		build(v * 2 + 2, m, r);
		for(int i = 0; i < (1 << k); i++)
			T[v][i] = min(T[v * 2 + 1][i], T[v * 2 + 2][i]);
	}
}

int query(int v, int l, int r, int L, int R, int x)
{
	if(L >= R) return INF;
	if(L == l && R == r)
		return T[v][x];
	int m = (l + r) / 2;
	return min(query(v * 2 + 1, l, m, L, min(R, m), x), query(v * 2 + 2, m, r, max(L, m), R, x));
}

void upd(int v, int l, int r, int z)
{
	if(l == r - 1)
	{
		for(int i = 0; i < (1 << k); i++)
		{
			int cur = 0;
			for(int j = 0; j < k; j++)
				if(i & (1 << j))
					cur += A[l][j];
				else
					cur -= A[l][j];
			T[v][i] = cur;
		}
	}
	else
	{
		int m = (l + r) / 2;
		if(z < m)
			upd(v * 2 + 1, l, m, z);
		else
			upd(v * 2 + 2, m, r, z);
		for(int i = 0; i < (1 << k); i++)
			T[v][i] = min(T[v * 2 + 1][i], T[v * 2 + 2][i]);
	}
}

int main() 
{ 
	scanf("%d %d", &n, &k);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < k; j++)
		{
			scanf("%d", &A[i][j]);
		}
	}
	int q;
	scanf("%d", &q);
	build(0, 0, n);
	for(int i = 0; i < q; i++)
	{
		int t;
		scanf("%d", &t);
		if(t == 1)
		{
			int z;
			scanf("%d", &z);
			--z;
			for(int j = 0; j < k; j++)
				scanf("%d", &A[z][j]);
			upd(0, 0, n, z);
		}
		else
		{
			int ans = 0;
			int l, r;
			scanf("%d %d", &l, &r);
			--l;
			for(int i = 0; i < (1 << (k - 1)); i++)
			{
				int x = query(0, 0, n, l, r, i);
				int y = query(0, 0, n, l, r, ((1 << k) - 1) ^ i);
				ans = max(ans, abs(x + y));
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
