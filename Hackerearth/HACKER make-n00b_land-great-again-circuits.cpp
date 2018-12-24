

    #include<bits/stdc++.h>
    using namespace std;
    const int N = 500331;
    int n, m;
    vector<int> g[N];
    int owner[N];
    long long thold[N];
    long long F[N], X[N], D[N];
    int Q;
    vector<int> entries[N];
    int l[N], r[N];
    vector<int> tocheck[N];
    int used[N];
    int tin[N];
    int timer;
    long long dep[N];
    int tout[N];
    long long t[3][N];
    long long get(int id, int r)
    {
    	long long res = 0;
    	for (; r >= 0; r = (r&(r + 1)) - 1)
    		res += t[id][r];
    	return res;
    }
    void add(int id, int i, long long val)
    {
    	for (; i < N; i = (i | (i + 1)))
    		t[id][i] += val;
    }
    void trace(int v)
    {
    	used[v] = 1;
    	++timer;
    	tin[v] = timer;
    	for (int i = 0; i < g[v].size(); i++)
    	{
    		int to = g[v][i];
    		if (used[to])
    			continue;
    		dep[to] = dep[v] + 1;
    		trace(to);
    	}
    	tout[v] = timer;
    }
    void clean_stuff()
    {
    	for (int i = 0; i < N; i++)
    		t[0][i] = t[1][i] = 0;
    	for (int i = 1; i <= Q + 1; i++)
    		tocheck[i].clear();
    	for (int i = 1; i <= m; i++)
    	{
    		if (l[i] == r[i])
    			continue;
    		int mid = l[i] + r[i];
    		mid /= 2;
    		tocheck[mid].push_back(i);
    	}
    }
    int main(){
    	ios_base::sync_with_stdio(0);
    	cin >> n >> m;
    	for (int i = 2; i <= n; i++)
    	{
    		int v;
    		cin >> v;
    		g[v].push_back(i);
    	}
    	for (int i = 1; i <= n; i++)
    	{
    		cin >> owner[i];
    		entries[owner[i]].push_back(i);
    	}
    	for (int i = 1; i <= m; i++)
    	{
    		cin >> thold[i];
    	}
    	
    	cin >> Q;
    	for (int i = 1; i <= Q; i++)
    	{
    		cin >> F[i] >> X[i] >> D[i];
    	}
    	F[Q + 1] = 1;
    	trace(1);
    	for (int i = 1; i <= n; i++)
    	{
    		l[i] = 1;
    		r[i] = Q + 1;
    	}
    	for (int iter = 1; iter <= 20; iter++)
    	{
    		clean_stuff();
    		int C = 0;
    		for (int i = 1; i <= Q + 1; i++)
    		{
    			long long on_ground = X[i] - 1ll * dep[F[i]] * D[i];
    			add(1, tin[F[i]], on_ground);
    			add(1, tout[F[i]] + 1, -on_ground);
    			add(0, tin[F[i]], D[i]);
    			add(0, tout[F[i]] + 1, -D[i]);
    			for (int j = 0; j < tocheck[i].size(); j++)
    			{
    				++C;
    				int id = tocheck[i][j];
    				long long res = 0;
    				for (int q = 0; q < entries[id].size(); q++)
    				{
    					int ps = entries[id][q];
    					res += get(1, tin[ps]);
    					res += 1ll * get(0, tin[ps])*dep[ps];
    					if (res>2e18)
    						res = 2e18;
    				}
    				if (res >= thold[id])
    					r[id] = i;
    				else
    					l[id] = i + 1;
    			}
    		}
    		if (C == 0)
    			break;
    	}
    	for (int i = 1; i <= m; i++)
    	{
    		if (l[i] == Q + 1)
    			cout << "rekt" << "\n";
    		else
    			cout << l[i] << "\n";
    	}
    	return 0;
    }

