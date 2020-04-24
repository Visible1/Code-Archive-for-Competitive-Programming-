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
#define pb(a) push_back(a)
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ld> vd;
typedef vector<vd> vvd;
typedef pair<ll, ll> pii;
typedef vector<pii> vpii;
const ll INF = 0x3f3f3f3f;
const ll inf =  pow(10,18);
ll modulo = pow(10,9) + 7;
#define MAX (int)(2502 + 10)


// Persistent Segment Tree with point updates and range queries
struct per_seg{
	struct Node{
		int data = 0; // TODO add additional types if needed and update the constructors
		int l, r;			// bounds of this node
		int left, right;	// index of left right child
		Node(){}
		Node(int data, int l, int r, int left, int right) : data(data), l(l), r(r), left(left), right(right) {} 
		Node(Node& other) : l(other.l), r(other.r), data(other.data){} 
		void operator*=(Node& other){	//  merge node value to query value
			data += other.data;
		}
	};
	int indices[MAX];
	Node roots[MAX];
	int count_ = 0;
	void pull(int idx){	// TODO update the pull if needed
		if(roots[idx].l == roots[idx].r){
			return;
		}
		ll lef = roots[idx].left, rig = roots[idx].right;
		roots[idx].data = roots[lef].data + roots[rig].data;
	}
	int create_root(int l, int r){	// return the index of the newly created root
		int cur = count_;
		++count_;
		roots[cur] = Node(0, l, r,0,0);	//  TODO if u need to initialize data put it here
		if(l!=r)	
			roots[cur].left = create_root(l,(l+r)/2),	
			roots[cur].right = create_root((l+r)/2+1,r);
		return cur;
	}
	int create_update(int index, int base, int val){	// index : the point of update, base : previous root
		if(index<roots[base].l || index>roots[base].r)
			return base;
		int cur = count_;
		++count_;
		roots[cur] = Node(roots[base]);
//		cout<<"We wanna update "<<index<<" we at "<<roots[base].l<<" "<<roots[base].r<<"the cur "<<cur<<endl;
		if(roots[base].l == roots[base].r){	
			roots[cur].data = val;
			return cur;
		}
		roots[cur].left  = create_update(index,roots[base].left, val);
		roots[cur].right = create_update(index,roots[base].right, val);
		pull(cur);
		return cur;
	}
	void que(int hd, Node& query){ // the range query , assumption l <= r
//		cout<<" we at "<<hd<<" left: "<<roots[hd].l<<" right: "<<roots[hd].r<<" val : "<<roots[hd].data<<endl;
		if(roots[hd].l > query.r || roots[hd].r < query.l)	return ;
		if(roots[hd].l >= query.l && roots[hd].r <=query.r){	query*=roots[hd]; return; }
		que(roots[hd].left,  query);
		que(roots[hd].right, query);
	}
};

void test(){
	// Modify Node struct accordingly to use
	// usage:
	// per_seg Seg;
	// Seg.indices[0] = Seg.create_root(1,n)    1-based indexing
	// Seg.indices[i] = Seg.create_update( index of update, Seg.indices[i-1] )
	// per_seg::Node 	query( data initialized to 0, left end , right end , -1 , -1)
	// Seg.que( Seg.indices[ "the query root" ] , query );
	// cout<<query.data;
	per_seg Seg;
	Seg.indices[0] = Seg.create_root(1,5);
	for(ll i =1; i<5; i++){
		Seg.indices[i] = Seg.create_update(i, Seg.indices[i-1], 1);
	}
	for(ll i = 0 ; i<5; i++){
		cout<<"!!Segtree number "<<i<<" !!!"<<endl;
		for(ll l = 1; l<=5; l++){
			for(ll r = l; r<=5; r++){
				per_seg::Node 	query( 0, l, r , -1 , -1);
				Seg.que(Seg.indices[i], query);
				cout<<l<<" "<<r<<" "<<query.data<<endl;
			}
		}
	}
}

void deal(){
	
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	test();
	deal();
}    


