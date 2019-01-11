#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll LOGN = 22;
const ll N = 3000001;
const ll MOD = 998244353;
#define sz(a) (long long)((a).size())
ll g = 3;

inline ll mul(ll a, ll b){
	return ll(a * 1ll * b % MOD);
}

inline ll norm(ll a) {
	if(a >= MOD)
		a -= MOD;
	if(a < 0)
		a += MOD;
	return a;
}

inline ll binPow(ll a, ll k) {
	ll ans = 1;
	while(k > 0) {
		if(k & 1)
			ans = mul(ans, a);
		a = mul(a, a);
		k >>= 1;
	}
	return ans;
}

inline ll inv(ll a) {
	return binPow(a, MOD - 2);
}

vector<ll> w[LOGN];
vector<ll> rv[LOGN];

void precalc() {
    ll wb = binPow(g, (MOD - 1) / (1 << LOGN));

    for(ll st = 0; st < LOGN - 1; st++) {
        w[st].assign(1 << st, 1);

        ll bw = binPow(wb, 1 << (LOGN - st - 1));
        ll cw = 1;

        for (ll k = 0; k < (1 << st); k++) {
            w[st][k] = cw;
            cw = mul(cw, bw);
        }
    }
    for(ll st = 0; st < LOGN; st++) {
        rv[st].assign(1 << st, 0);

        if(st == 0) {
            rv[st][0] = 0;
            continue;
        }
        ll h = (1 << (st - 1));
        for(ll k = 0; k < (1 << st); k++)
            rv[st][k] = (rv[st - 1][k & (h - 1)] << 1) | (k >= h);
    }
}

inline void fft(ll a[N], ll n, bool inverse) {
    ll ln = 0;
    while((1 << ln) < n)
        ln++;

    assert((1 << ln) < N);
    n = (1 << ln);

    for(ll i=0;i <  n; i++) {
        ll ni = rv[ln][i];
        if(i < ni)
            swap(a[i], a[ni]);
    }

    for(ll st = 0; (1 << st) < n; st++) {
        ll len = (1 << st);
        for(ll k = 0; k < n; k += (len << 1)) {
            for(ll pos = k; pos < k + len; pos++) {
                ll l = a[pos];
                ll r = mul(a[pos + len], w[st][pos - k]);

                a[pos] = norm(l + r);
                a[pos + len] = norm(l - r);
            }
        }
    }

    if(inverse) {
        ll in = inv(n);
        for(ll i=0;i<n;i++)
            a[i] = mul(a[i], in);
        reverse(a + 1, a + n);
    }
}

ll aa[N], bb[N], cc[N];

inline vector<ll> multiply(const vector<ll> a, const vector<ll> b) {
	ll ln = 1;
	while(ln < (sz(a) + sz(b)))
		ln <<= 1;

	for(ll i=0;i<ln;i++)
		aa[i] = (i < sz(a) ? a[i] : 0);

	for(ll i=0;i<ln;i++)
		bb[i] = (i < sz(b) ? b[i] : 0);

	fft(aa, ln, false);
	fft(bb, ln, false);

	for(ll i=0;i<ln;i++)
		cc[i] = mul(aa[i], bb[i]);

	fft(cc, ln, true);

	vector<ll> c(ln, 0);
	for(ll i=0;i<sz(c);i++)
		c[i] = cc[i];

	while(sz(c) > 1 && c.back() == 0)
		c.pop_back();
	return c;
}
ll n, k;
int main()
{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL); cout.tie(NULL);
        cin >> n >> k;
        vector<ll> dd;
        dd.resize(10, 0);
        for(ll i=0;i<k;i++) {
                        ll x;
                cin >> x;
                dd[x]=1;
        }
        vector< ll > ans(1 , 1);
        precalc();
        ll pw = n/2;
        while(pw) {

                if(pw&1) ans = multiply(ans , dd);
                dd = multiply(dd , dd);
                pw = pw >> 1;
        }
        //cout << "OKAY\n";
        ll ret=0;
        for(ll i=0;i<ans.size();i++) {
                ret = (ret + mul(ans[i] , ans[i]))%MOD;
        }
        cout << ret << endl;
        return 0;
}
