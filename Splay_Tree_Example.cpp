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
#define ll int
#define double long double
#define MAX 2000010
#define N 2000010
#define pb(a) push_back(a)
const ll INF = 0x3f3f3f3f;
const ll inf = pow(10,18);
ll modulo = pow(10,9)+7;
 
 
struct node; using pn = node*;
struct node { pn l, r, p; ll key, val, cnt; bool rev;
  node() = default; node(ll k, ll v);
  inline int dir() { return this == p->r; }
  inline void setc(pn c, bool right) { (right?r:l) = c; c->p = this; }
} dat[N];
pn nil = [](){ pn x=dat; x->l=x->r=x->p=x; /*x->acc=INF;*/ return x; }();  //RMQ
node::node(ll k, ll v):
  l(nil), r(nil), p(nil), key(k), val(v), cnt(1),rev(0) {}
int nodeid = 0; template <class... T> pn new_node(T&& ...args) {
  return &(dat[++nodeid] = node(forward<T>(args)...)); }
 
namespace SplayTree {
//%%== Code for upwards propagating property (eg. count, min)
inline void pull(pn x) { if (x != nil) { x->cnt = 1 + x->l->cnt + x->r->cnt;
  /*x->acc = min(x->l->acc, min(x->val, x->r->acc));*/ } }                 //RMQ
//%%== Code for downward lazy propagating property (eg. reverse subtree, add)
void rev(pn x) { if (x != nil) { x->rev ^= 1; swap(x->l, x->r); } }
inline void modifyNode(pn x, ll v) { if (x != nil) {
  /*x->val += v; x->acc += v; x->lazy += v;*/ } }                          //RMQ
inline void push(pn x) {if (x->rev) { rev(x->l); rev(x->r); x->rev=0; } //REV
  /*modifyNode(x->l, x->lazy); modifyNode(x->r, x->lazy); x->lazy=0;*/ }   //RMQ
//%%== call pushTo() before using node if an ancestor may have un-pushed lazy
void pushTo(pn c) { if (c->p != nil) pushTo(c->p); push(c); }
//%%== Core splay tree code (rotate, splay, delete)
inline void rot(pn x) { pn p = x->p; push(p); push(x); bool d = x->dir();
  p->setc(d ? x->l : x->r, d); p->p->setc(x, p->dir()); x->setc(p, !d);
  pull(p); pull(x); }
// splays node x until it is a child of node to
pn splay(pn x, pn to=nil) { if (x!=nil) { while (x->p!=to) { if (x->p->p!=to)
  rot(x->dir() == x->p->dir() ? x->p : x); rot(x); } } return x; }
pn del(pn y) { pn x=splay(y)->r; if (x==nil) x=y->l; else {
  while (push(x), x->l != nil) x = x->l; splay(x,y)->setc(y->l,0); }
  x->p=nil; pull(x); return x; }
//%%== BST methods (lb, find, insert) (conflicts with other features, see above)
pn lb(pn c, ll k) { if (c == nil) return c; push(c); // c MUST BE THE ROOT
  if (c->key>=k) { pn l=lb(c->l,k); return l==nil?c:l; } return lb(c->r,k); }
pn lowerBound(pn ref, ll k) { return lb(splay(ref), k); }
pn find(pn c, ll k) { c=lb(splay(c),k); return c->key!=k?nil:splay(c); }
pn insert(pn c, pn x) { if (splay(c) == nil) return x;
  ll k=x->key; pn p; while(c!=nil) { push(c); p=c; c=(p->key>k?p->l:p->r); }
  p->setc(x,p->key<=k); return splay(x); }
//%%== Utility code (rank, nth order statistic) (requires count maintained)
int idx(pn x) { return splay(x)->l->cnt; } // rank; for size, remove '->l'
pn nth(pn c, int n) { splay(c); while (c!=nil) { push(c); int l=c->l->cnt;
  if (n==l) break; if (n < l) c = c->l; else n = n-l-1, c = c->r; } return c; }
//%%== Iterator-based access, returns nil when iterator exhausted
pn first(pn c) { if (splay(c)!=nil) while (push(c),c->l!=nil)c=c->l; return c; }
pn  last(pn c) { if (splay(c)!=nil) while (push(c),c->r!=nil)c=c->r; return c; }
pn prv(pn x) { if (splay(x)->l == nil) return nil; x = x->l;
  while (push(x), x->r != nil) x = x->r; return x; }
pn nxt(pn x) { if (splay(x)->r == nil) return nil; x = x->r;
  while (push(x), x->l != nil) x = x->l; return x; }
//%%== Iterator-based insert, does NOT work with BST code unless key sorted
pn insertBefore(pn c, pn at, pn x) { // to insert "last", use at=nil
  if (at==nil) { if (splay(c)!=nil) last(c)->setc(x,1); } else { pn p=prv(at);
  if (p==nil) at->setc(x,0); else p->setc(x,1); } return splay(x); }
//%%== Range query and update operations by iterator, range is EXCLUSIVE!
pn range(pn c, pn l, pn r) { if (l == nil) { if (r == nil) return splay(c);
  return splay(r)->l; } if (l == r) return nil; splay(l);
  if (r == nil) return l->r; return splay(r,l)->l;}
ll pQuery(pn x) { return splay(x)->val; }
void pUpdate(pn x, ll v) { splay(x)->val += v; pull(x); }                  //RMQ
void rUpdate(pn c, pn l, pn r, ll v) {
  pn u = range(c, l, r); modifyNode(u, v); splay(u); }
//%%== Rope operations: split and merge, nil = right end
pn splitBefore(pn x) { if (splay(x)==nil) return nil; push(x); if (x->l!=nil)
  push(x->l); pn ret=x->l; x->l=x->l->p=nil; pull(ret); pull(x);return ret; }
pn append(pn l, pn r) { if (splay(l) == nil) return r;
  if (splay(r) == nil) return l; pn x = splay(last(l)); push(x);
  push(r); x->setc(r,1); pull(x->r); pull(x); return x; } }
 
using namespace SplayTree;
 
void test(){
	
	pn root = new node(-1, 0);
	
/*	for(ll i = 1; i<=10;i++){
		pn z =  new node(-1, i*100);
		insertBefore(root, nth(root, i), z);         // x is now rank 15
		
	}
	rev(range(root, nth(root, 4), nth(root, 11)));
	
	for(ll i = 1; i<=10; i++){
		pn z = nth(root, i);
		cout<<z->val<<endl;
	}
	*/
	
	
	ll n ,l , r;
	cin>>n>>l>>r;
	fori(n){
		char f;
		cin>>f;
		pn z = new node(-1, f-'a');
		insertBefore(root, nth(root, i+1), z); 
	}
	
	ll m;
	cin>>m;
	fori(m){
		char f;
		cin>>f;
	//	cout<<"query "<<i+1<<" "<<l<<" "<<r<<endl;
		if( f== 'R'){
			rev(range(root, nth(root, l-1), nth(root, r+1)));
		}
		else if(f=='Q'){
			cin>>f;
			pn z;
			if(f == 'L'){
				z =  nth(root, l);
			}
			else{
				z =  nth(root, r);
			}
			cout<<(char)('a' + (z->val));
		}
		else{
			cin>>f;
			char f1;
			cin>>f1;
			ll inc = 1;
			if(f1 == 'L'){
				inc = -1;
			}
			if(f == 'L'){
				l+=inc;
			}
			else{
				r+=inc;
			}
		}
	}
}
 
 
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	test();
}
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
