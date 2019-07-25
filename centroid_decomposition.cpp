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
#define MAX 100000
#define N 100000
// #define cout out
// #define cin in
ll inf = pow(10,9);
ll modulo = inf;
double eps = 1e-10;
ifstream in;
ofstream out;
namespace centroid{
	bool dlt[MAX]; 						// whether the node was deleted
	vector<ll> g[MAX];					// graph
	vector<pair<ll,ll> > roots[MAX];	// all the parents (in centroid tree) of node i 
	ll sz[MAX];						// sizes of subtrees
	void dfs(ll hd, ll pr){			// dfs to update sizes
		sz[hd] = 1;
		for(auto hr : g[hd]){
			if(hr==pr || dlt[hr])
				continue;
			dfs(hr,hd);
			sz[hd]+=sz[hr];
		}
	}
	ll centre(ll hd,ll pr, ll siz){						// find the centre of the given tree 
		for(auto hr : g[hd]){
			if(hr == pr || dlt[hr])
				continue;
			if(sz[hr] > siz/2 )
				return centre(hr,hd,siz);
		}
		return hd;
	}
	void push_root(ll hd, ll pr, ll root, ll dt){		// push the chosen root to all the descendants in centroid tree
		roots[hd].push_back(mp(root,dt));
		for(auto hr : g[hd]){
			if(hr==pr || dlt[hr])
				continue;
			push_root(hr,hd,root,dt+1);
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
			for(auto hr : g[cnt]){
				if(!dlt[hr])
					create(hr);
			}
	}
}


void deal(){
	// usage
	// add edges : g[i].pb(j)  
	// call create(0);
}


int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	deal();
}



