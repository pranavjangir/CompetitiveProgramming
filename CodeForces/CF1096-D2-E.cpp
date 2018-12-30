#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

const int MOD = 998244353;
const int N = 10 * 1000 + 7;
const int M = 100 + 7;

int fact[N], rfact[N];

int add(int a, int b){
	a += b;
	if (a >= MOD) a -= MOD;
	if (a < 0) a += MOD;
	return a;
}

int mul(int a, int b){
	return (a * 1ll * b) % MOD;
}

int binpow(int a, int b){
	int res = 1;
	while (b){
		if (b & 1)
			res = mul(res, a);
		a = mul(a, a);
		b >>= 1;
	}
	return res;
}

int cnk(int n, int k){
	if (n == k) return 1;
	if (k < 0 || k > n) return 0;
	return mul(fact[n], mul(rfact[k], rfact[n - k]));
}

int g(int s, int p, int m){
	int res = 0;
	forn(i, p + 1)
		res = add(res, mul(i & 1 ? MOD - 1 : 1, mul(cnk(p, i), cnk(s + p - 1 - i * (m + 1), p - 1))));
	return res;
}

int inv(int x){
	return mul(rfact[x], fact[x - 1]);
}

int main() {
	fact[0] = 1;
	for (int i = 1; i < N; ++i) fact[i] = mul(fact[i - 1], i);
	rfact[N - 1] = binpow(fact[N - 1], MOD - 2);
	for (int i = N - 2; i >= 0; --i) rfact[i] = mul(rfact[i + 1], i + 1);
	
	int p, s, r;
	scanf("%d%d%d", &p, &s, &r);
	
	int Q = cnk(s - r + p - 1, p - 1);
	int P = 0;
	for (int t = r; t <= s; ++t) for (int q = 1; q <= p; ++q)
		P = add(P, mul(mul(cnk(p - 1, q - 1), inv(q)), g(s - q * t, p - q, t - 1)));
	
	printf("%d\n", mul(P, binpow(Q, MOD - 2)));
	return 0;
}
