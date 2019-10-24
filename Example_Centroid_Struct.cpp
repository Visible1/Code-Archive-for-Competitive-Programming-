#include <bits/stdc++.h>
using namespace std;
#define mp(a,b) make_pair(a,b)
#define ff first
#define setp setprecision(12)<<fixed
#define ss second
#define fori(v) for(int i=0; i<v; i++)
#define forj(v) for(int j=0; j<v; j++)
#define fork(v) for(int k=0; k<v; k++)
#define forl(v) for(int l=0; l<v; l++)
#define fort(v) for(int t=0; t<v; t++)
#define forz(v) for(int z=0; z<v; z++)
#define ll long long int
#define double long double
#define MAX (int)(pow(10,6) + 10)
#define pb(a) push_back(a)
// #define cout out
// #define cin in
ll inf = pow(10,18);
ll modulo = inf;
double eps = 1e-10;
ifstream in;
ofstream out;

// start time 19:52
struct centroid{
	bool *dlt; 						// whether the node was deleted
	vector<pair<ll, ll> >* g;					// graph
	vector<pair<int,ll> >* roots;	// all the parents (in centroid tree) of node i 
	ll* sz;						// sizes of subtrees
	
	centroid( ll n){
		dlt = new bool[n];
		fori(n)	dlt[i] = 0;
		g =  new vector<pair<ll,ll> > [n];
		roots = new vector<pair<int,ll> > [n];
		sz = new ll [n];
	}
	
	void dfs(ll hd, ll pr){			// dfs to update sizes
		sz[hd] = 1;
		for(auto el : g[hd]){
			auto hr = el.ff;
			if(hr==pr || dlt[hr])
				continue;
			dfs(hr,hd);
			sz[hd]+=sz[hr];
		}
	}
	ll centre(ll hd,ll pr, ll siz){						// find the centre of the given tree 
		for(auto el : g[hd]){
			auto hr = el.ff;
			if(hr == pr || dlt[hr])
				continue;
			if(sz[hr] > siz/2 )
				return centre(hr,hd,siz);
		}
		return hd;
	}
	void push_root(ll hd, ll pr, ll root, ll dt){		// push the chosen root to all the descendants in centroid tree
		roots[hd].push_back(mp(root,dt));
		for(auto el : g[hd]){
			auto hr = el.ff;
			if(hr==pr || dlt[hr])
				continue;
			push_root(hr,hd,root,dt+el.ss);
		}
	}
	void create(ll st){									// create the centroid tree
		dfs(st,-1);
	//	cout<<"we started  "<<st<<endl;
		ll cnt = centre(st,-1,sz[st]);
	//	cout<<"the centre "<<cnt<<endl;
		push_root(cnt,-1,cnt,0);
	//	cout<<"we pushed the centre ( root ) "<<endl;
		dlt[cnt] = 1;
		if(sz[st]!=1)
			for(auto el : g[cnt]){
				auto hr = el.ff;
				if(!dlt[hr])
					create(hr);
			}
	}
	void ini(ll n){
		fori(n)
			dlt[i] = 0, g[i].clear(), roots[i].clear(), sz[i] = 0;
	}
};

ll global[MAX];
pair<ll,ll> mins[MAX];
int  last[MAX];
#define MAX2 (int)(5*pow(10,6)+10)
vector<ll>  batch[MAX2];
ll  idx = 0;
bool observe = 0;

void push_root2(centroid& c2, int hd, int pr, int root2, ll dt, centroid& c1){		// push the chosen root to all the descendants in centroid tree
		c2.roots[hd].push_back(mp(root2,dt));
//		cout<<"we here ballin with root "<<root2+1<<" and node "<<hd+1<<" and observe "<<observe<<endl;
		if(observe){
			cout<<"we explorin "<<hd<<endl;
		}
		for(auto el : c2.g[hd]){
			auto hr = el.ff;
			if(hr==pr || c2.dlt[hr])
				continue;
			push_root2(c2, hr,hd,root2,dt+el.ss, c1);
		}
		for(auto& el : c1.roots[hd]){
			int root = el.ff;
			ll sum = el.ss + dt;
			// update mins
			if(observe){
				cout<<"node "<<hd+1<<"  root "<<el.ff<<" the distance to root in tree1 "<<el.ss<<"  distance to current root which is "<<root2<<"  is "<<dt<<endl;
			}
			if(sum < mins[root].ff)
				mins[root].ss = mins[root].ff, mins[root].ff = sum;
			else if(sum < mins[root].ss)
				mins[root].ss = sum;
			// push to batch
			batch[idx++] = (vector<ll>({hd, root, sum}));
			last[root] = hd;
		}
}


void create2(ll st, centroid& c2, centroid& c1){
	c2.dfs(st,-1);
	//	cout<<"we started  "<<st<<endl;
	ll cnt = c2.centre(st,-1,c2.sz[st]);
	//	cout<<"the centre "<<cnt<<endl;
//	if(cnt == 5)
//		observe = 1;
	push_root2(c2, cnt,-1,cnt,0, c1);
	// after batch is done
	fori(idx){
		auto& el = batch[i];
		int node = el[0];
		int root = el[1];
		ll sum  = el[2];
		ll sum2 = mins[root].ff;
//		cout<<"node "<<node+1<<" root "<<root+1<<" sum : "<<sum<<endl;
		if( sum2 == sum)
			sum2 = mins[root].ss;
		if(sum + sum2 < global[node])
			global[node] = sum + sum2;
		if(last[root] == node)
			mins[root].ff = inf, mins[root].ss = inf;
	}
//	if(cnt == 5)
//		cout<<"\n\n\n\n", observe = 0;
	idx = 0;
	
	//	cout<<"we pushed the centre ( root ) "<<endl;
	c2.dlt[cnt] = 1;
	if(c2.sz[st]!=1)
		for(auto el : c2.g[cnt]){
			auto hr = el.ff;
			if(!c2.dlt[hr])
				create2(hr, c2, c1);
		}
}

void output_roots(centroid& c, ll n){
	fori(n){
		cout<<"for node "<<i+1<<endl;
		for(auto el : c.roots[i])
			cout<<"root "<<el.ff+1<<" distance "<<el.ss<<endl;
	}
}

// given 2 trees t1, t2 with number of nodes <= 2.5*10^5.
// for each node "i" in t1 , find the node "j" in t2
// such that dist(i, j, t1 ) + dist(i,j, t2) is minimized
// Open Cup Grand Prix of Korea 2019
// Problem K

void test(){
	// usage
	// add edges : g[i].pb(j)  
	// call create(0);
	fori(MAX)
		mins[i].ff = inf, mins[i].ss = inf, global[i] = inf;
	ll n;
	cin>>n;
	centroid c1(n),c2(n);
	fori(n-1){
		ll a , b, w;
		cin>>a>>b>>w; --a, --b;
		c1.g[a].pb(mp(b,w));
		c1.g[b].pb(mp(a,w));
	}
	fori(n-1){
		ll a, b, w;
		cin>>a>>b>>w; --a, --b;
		c2.g[a].pb(mp(b,w));
		c2.g[b].pb(mp(a,w));
	}
	c1.create(0);
	create2(0, c2, c1);
/*	cout<<"for tree 1 "<<endl;
	output_roots(c1, n);
	cout<<"\n\n\n\nfor tree 2 "<<endl;
	output_roots(c2, n);
*/	fori(n)
		cout<<global[i]<<'\n';
}


int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	test();
}














