#include <bits/stdc++.h>
using namespace std;
#define mp(a,b) make_pair(a,b)
#define ff first
#define setp(a) setprecision(a)<<fixed
#define ss second
#define fori(v) for(ll i=0; i<v; i++)
#define forj(v) for(ll j=0; j<v; j++)
#define fork(v) for(ll k=0; k<v; k++)
#define forl(v) for(ll l=0; l<v; l++)
#define fort(v) for(ll t=0; t<v; t++)
#define forz(v) for(ll z=0; z<v; z++)	
#define forx(v) for(ll x=0; x<v; x++)
#define fory(v) for(ll y=0; y<v; y++)
#define ll long long
#define double long double
#define pb(a) push_back(a)
const ll INF = 0x3f3f3f3f;
const ll inf = pow(10,18);
ll modulo = 998244353  ;
#define MAX (int)(pow(10,5)+ 10)

// by  kartikkukreja

class UF    {
	public:
    ll *id, cnt, *sz;
    ll ans;
	// Create an empty union find data structure with N isolated sets.
    UF(int N)   {
    	ans = 0;
        cnt = N;
		id = new ll[N];
		sz = new ll[N];
        for(ll i=0; i<N; i++)	{
            id[i] = i;
	    sz[i] = 1;
	}
    }
    ~UF()	{
	delete [] id;
	delete [] sz;
    }
	// Return the id of component corresponding to object p.
    ll find(ll p)	{
        ll root = p;
        while (root != id[root])
            root = id[root];
        while (p != root) {
            ll newp = id[p];
            id[p] = root;
            p = newp;
        }
        return root;
    }
	// Replace sets containing x and y with their union.
    void merge(int x, int y)	{
        ll i = find(x);
        ll j = find(y);
        if (i == j) return;
		ans-=sz[i]*(sz[i]-1)/2;
		ans-=sz[j]*(sz[j]-1)/2;
		ans+=(sz[i]+sz[j])*(sz[i]+sz[j]-1)/2;
//		cout<<"we mergin "<<sz[i]<<" "<<sz[j]<<endl;
		// make smaller root point to larger one
        if   (sz[i] < sz[j])	{ 
		id[i] = j; 
		sz[j] += sz[i]; 
	} else	{ 
		id[j] = i; 
		sz[i] += sz[j]; 
	}
        cnt--;
    }
	// Are objects x and y in the same set?
    bool connected(ll x, ll y)    {
        return find(x) == find(y);
    }
	// Return the number of disjoint sets.
    ll count() {
        return cnt;
    }
};
void deal(){
	
}

int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	deal();
}


/*



*/
