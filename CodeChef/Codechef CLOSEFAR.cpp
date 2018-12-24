
/*
	Editorial solution :
		https://discuss.codechef.com/questions/83729/closefar-editorial
		http://codeforces.com/blog/entry/43230
*/

#include <bits/stdc++.h>
using namespace std;
#define lli long long

int n , q , sq;
int a[112345];
pair<lli,int> b[112345];
int pos[112345];
// ----------------------

vector<int> v[112345];
int dfsOrder[212345]; int taim = 1;
int start[112345] , finish[112345];
int depth[112345];
const int LogN = 20;
int sp[112345][LogN];
// ----------------------

void dfs( int x , int p , int d )
{
	depth[x] = d;
	dfsOrder[taim] = x;
	start[x] = taim;
	taim++;

	sp[x][0] = p;
	for ( int i=1 ; i<LogN ; i++ )
	{
		int q = sp[x][i-1];
		sp[x][i] = sp[q][i-1];
	}

	int vs = v[x].size();
	for ( int i=0 ; i<vs ; i++ )
	{
		int y = v[x][i];
		if ( y != p )
			dfs( y , x , d+1 );
	}

	dfsOrder[taim] = x;
	finish[x] = taim;
	taim++;
}

int lca( int x , int y )
{
	int dx = depth[x] , dy = depth[y];
	if ( dx < dy )
		swap( x , y ), swap( dx , dy );

	int dif = dx - dy;
	for ( int i=LogN-1 ; i>=0 ; i-- )
	{
		if ( dif >= ( 1<<i ) )
			x = sp[x][i] , dif -= (1<<i);
	}
	dx = dy;
	if ( x == y ) return x;

	for ( int i=LogN-1 ; i>=0 ; i-- )
	{
		if ( sp[x][i] != sp[y][i] )
		{
			x = sp[x][i];
			y = sp[y][i];
		}
	}
	x = sp[x][0];
	return x;
}

// ----------------------------------------------------------

const int NotMin = 100001 , NotMax = 0;
const lli NotMinDif = 5e9 + 5;
bool on[112345];
int cnt[112345];

struct Node
{
	lli minDif;
	int l , r;
};

struct SegmentTree
{
	int n;
	vector<Node> st;
	vector<int> pos;

	inline int left ( int x ) { return (x<<1); }
	inline int right( int x ) { return (x<<1) + 1; }

	void build( int p , int L , int R )
	{
		if ( L == R )
		{
			pos[L] = p;
			st[p].l = NotMin;
			st[p].r = NotMax;
			st[p].minDif = NotMinDif;
		}
		else
		{
			int l = left( p ) , r = right( p );
			int mid = ( L + R ) >> 1;
			build( l , L , mid );
			build( r , mid+1 , R );

			st[p].l = min( st[l].l , st[r].l );
			st[p].r = max( st[l].r , st[r].r );

			st[p].minDif = min( st[l].minDif , st[r].minDif );
			int ll = st[l].r , rr = st[r].l;
			st[p].minDif = min( st[p].minDif , b[rr].first - b[ll].first );
		}
	}



	SegmentTree( int _n )
	{
		n = _n;
		st.resize( n * 4 + 5 );
		pos.resize( n + 1 );
		build( 1 , 1 , n );
	}

	int getMaxDif( int dad )
	{
		bool lcaState = on[dad];
		if ( lcaState == 0 ) update( dad , 1 );
		int l = st[1].l , r = st[1].r;
		if ( lcaState == 0 ) update( dad , 0 );

		return b[r].first - b[l].first;
	}

	int getMinDif( int dad )
	{
		bool lcaState = on[dad];
		if ( lcaState == 0 ) update( dad , 1 );
		int ret = st[1].minDif;
		if ( lcaState == 0 ) update( dad , 0 );

		return ret;
	}

	void update( int x , int s )
	{
		if ( on[x] == s ) return;

		int p = pos[x];
		if ( s == 1 ) on[x] = 1 , st[p].l = x , st[p].r = x;
		else on[x] = 0 , st[p].l = NotMin , st[p].r = NotMax;

		p >>= 1;
		while ( p )
		{
			int l = left( p ) , r = right( p );
			st[p].l = min( st[l].l , st[r].l );
			st[p].r = max( st[l].r , st[r].r );

			st[p].minDif = min( st[l].minDif , st[r].minDif );
			int ll = st[l].r , rr = st[r].l;
			st[p].minDif = min( st[p].minDif , b[rr].first - b[ll].first );

			p >>= 1;
		}
	}
} *st;

// ----------------------------------------------------------

// Mo's Algorithm

struct Qu
{
	int l , r , dad; char t;
	int id;

	bool friend operator < ( Qu x , Qu y )
	{
		int sqL = x.l / sq , sqR = y.l / sq;
		if ( sqL != sqR ) return sqL < sqR;
		return ( (sqL%2==0) ?  (x.r < y.r) : (x.r > y.r) );
	}

} Q[112345];
int ans[112345];

int moL = 1 , moR = 1;

void add( int t )
{
	int x = dfsOrder[t];
	x = pos[x];
	cnt[x]++;
	if ( cnt[x] == 1 ) st->update( x , 1 );
	else st->update( x , 0 );
}

void del( int t )
{
	int x = dfsOrder[t];
	x = pos[x];
	cnt[x]--;
	if ( cnt[x] == 1 ) st->update( x , 1 );
	else st->update( x , 0 );
}

// ----------------------------------------------------------

int main()
{

	scanf( "%d" , &n ); sq = sqrt( 2.0*n );
	for ( int i=1 ; i<=n ; i++ )
	{
		scanf( "%d" , &a[i] );
		b[i] = make_pair( a[i] , i );
	}
	sort( b+1 , b+1+n );
	for ( int i=1 ; i<=n ; i++ ) pos[ b[i].second ] = i;
	b[NotMin].first = +5e9 + 5;
	b[NotMax].first = -5e9 - 5;

	for ( int i=1 ; i<n ; i++ )
	{
		int x , y;
		scanf( "%d %d" , &x , &y );
		v[x].push_back( y );
		v[y].push_back( x );
	}
	for ( int i=0 ; i<LogN ; i++ ) sp[1][i] = 1;
	dfs( 1 , 1 , 1 );

	scanf( "%d" , &q );
	for ( int i=1 ; i<=q ; i++ )
	{
		int x , y;
		scanf( " %c %d %d" , &Q[i].t , &x , &y );

		Q[i].id = i;
		if ( start[x] > start[y] ) swap( x , y );

		int dad = lca( x , y );
		if ( dad == x || dad == y ) Q[i].l = start[x] , Q[i].r = start[y] , Q[i].dad = dad;
		else Q[i].l = finish[x] , Q[i].r = start[y] , Q[i].dad = dad;
	}
	sort( Q+1 , Q+1+q );

	st = new SegmentTree( 112345 );
	for ( int i=1 ; i<=q ; i++ )
	{
		char t; int l , r , dad , id;
		t = Q[i].t , l = Q[i].l , r = Q[i].r , dad = Q[i].dad , id = Q[i].id;
		r++;

		while ( moR < r ) { add(moR); moR++; }
		while ( moR > r ) { moR--; del(moR); }

		while ( moL < l ) { del(moL); moL++; }
		while ( moL > l ) { moL--; add(moL); }

		if ( t == 'F' )
		{
			ans[id] = st->getMaxDif( pos[dad] );
		}
		else
		{
			ans[id] = st->getMinDif( pos[dad] );
		}
	}

	for ( int i=1 ; i<=q ; i++ )
		printf( "%d\n" , ans[i] );
	return 0;
}
