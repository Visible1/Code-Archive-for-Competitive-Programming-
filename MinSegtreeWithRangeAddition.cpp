#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#pragma GCC optimize("unroll-loops")
 
 
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
#define lll __int128
#define pb(a) push_back(a)
#define mt make_tuple
typedef long double ld;
const ll INF = 0x3f3f3f3f;
const ll inf =  pow(10, 18);
ll modulo = pow(10,9) + 7;
 
#define MAX 4'000'010
 
ll mn[MAX];
ll mnidx[MAX];
ll lz[MAX];
 
void init(ll node, ll l, ll r){
	mn[node] = 0;
	lz[node] = 0;
	mnidx[node] = l;
	if(l == r){
		return;
	}
	init(node<<1, l, (l+r)/2);
	init(((node<<1)|1), (l+r)/2+1, r);
}
 
void pull(ll node){
	ll li = (node<<1), ri = ((node<<1)|1);
	lz[node] = 0;
	if(mn[li] < mn[ri]){
		mn[node] = mn[li];
		mnidx[node] = mnidx[li];
	}
	else{
		mn[node] = mn[ri];
		mnidx[node] = mnidx[ri];
	}
}
 
void push(ll node, ll l, ll r){
	if(l != r){
		lz[node<<1] += lz[node];
		lz[(node<<1)|1]+=lz[node];
	}
	mn[node]+=lz[node];
	lz[node] = 0;
}
 
void upd(ll node, ll l, ll r, ll lu, ll ru, ll val){
	push(node, l, r);
	if(r < lu || ru < l){
		return;
	}
	if(lu <= l && r <= ru){
		lz[node] += val;
		push(node, l, r);
		return;
	}
	upd((node<<1), l, (l+r)/2, lu, ru, val);
	upd(((node<<1)|1), (l+r)/2 + 1, r, lu, ru, val);
	pull(node);
}
 
void que(ll node, ll l, ll r, ll ql, ll qr, ll& bst, ll& id){
	push(node, l, r);
	if(r < ql || qr < l){
		return;
	}
	if(ql <= l && r <= qr){
		if(mn[node] < bst){
			bst = mn[node];
			id = mnidx[node];
		}
		return;
	}
	que((node<<1), l , (l+r)/2, ql, qr, bst, id);
	que(((node<<1)|1) , (l+r)/2 + 1, r, ql, qr, bst, id);
	pull(node);
}

void handle(){
	// example
	// for initialization change init function
	ll n, q;
	cin>>n>>q;
	init(1, 0, n-1);
	for(ll i = 1; i<q; i++){
		ll ty;
		cin>>ty;
		if(ty == 1){
			// range add
			ll l, r, val; // 1-indexed l,r
			cin>>l>>r>>val;
			--l, --r;
			upd(1, 0, n-1, l, r, val);
		}
		else{
			ll l, r;
			cin>>l>>r;
			ll bst = inf, id;
			--l, --r;
			que(1, 0, n-1, l, r, bst, id);
			cout<<"best index is "<<id+1<<" with value "<<bst<<endl;
		}
	}
}

void deal(){
	
}
 
 
int main()  {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	deal();
}
