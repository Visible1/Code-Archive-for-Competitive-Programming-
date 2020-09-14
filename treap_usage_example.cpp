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
#define MAX (int)(5*pow(10,3) + 5)
#define pb(a) push_back(a)
const ll INF = 0x3f3f3f3f;
const ll inf = pow(10,18);
ll modulo = pow(10,9)+7;

ofstream out;
ifstream in;

#define cout out
#define cin in

/**
 * Author: luccasiau
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Usage:
 *  - Put all the info that you need to save on the node
 *  - Update the update (might be helpful to create helper functions like count)
 *  - rand() is being used, so remember to initialize the seed
 *  - Create a node with new node(value, rand())
 *  - Empty treap is NULL node pointer
 *  - To delete, pass a node with the same value (random priority)
 * Time: $O(\log N)$
 * Status: tested SPOJ TREAP, ORDERSET; CF62D, Kattis GCPC, OBI15P2F2, SPOJ GSS6, TWIST, CERC07S
 */

// COMMON FUNCTIONS FOR REGULAR AND IMPLICIT TREAP ---------------------
struct node{ node *l, *r; int v, p, lazy, count; // regular & implicit
  node(int v_=0, int p_=0){ l=r=NULL; v=v_; p=p_; lazy=0; count=1; } };
  
int count(node *x){ return (x == NULL)?0:x->count; } // regular&implicit
//change Lazy and Update for lazy-propagation (only use it in implicit)

void lazy(node *&x){ 
	if(x == NULL) return; 
	x->lazy = x->v;
	if(x->l){
		x->lazy = min(x->lazy, x->l->lazy);
	}
	
	if(x->r){
		x->lazy = min(x->lazy, x->r->lazy);
	}

}

void update(node *&curr){ if (!curr) return; // regular & implicit
  curr->count = count(curr->l) + count(curr->r) + 1; lazy(curr); }
  
void merge(node *&curr, node *l, node *r){ // regular & implicit
  lazy(l); lazy(r); if(l == NULL || r == NULL) curr = (l == NULL)?r:l;
  else if( l->p < r->p ){ merge(r->l, l, r->l); curr = r;
  }else{ merge(l->r, l->r, r); curr = l; } update(curr); }
  
  
node* kth_element(node *&treap, int k){ // 1-indexed. Kth element from L to R
  lazy(treap); if(k - count(treap->l) == 1) return treap;
  if(k <= count(treap->l)) return kth_element(treap->l, k);
  return kth_element(treap->r, k - count(treap->l) - 1); }
  
// FUNCTIONS ONLY FOR REGULAR TREAP ------------------------------------
void split(node *curr, node *&l, node *&r, int key){ // regular
  if(curr == NULL){ l = r = NULL; return; }
  if(curr->v <= key){ split(curr->r, curr->r, r, key); l=curr;
  }else{ split(curr->l, l, curr->l, key); r=curr; } update(curr); }
  
void insert(node *&treap, node *x){ node *l=0,*r=0,*aux=0; // regular
  split(treap, l, r, x->v); merge(aux, l, x); merge(treap, aux, r); aux = NULL;}
  
void erase(node *&treap, int v){ node *l=0,*r=0,*l2=0,*r2=0;// regular
  split(treap, l, r, v); split(l, l2, r2, v-1); if(count(r2) > 1){
    merge(r2, r2->l, r2->r); merge(l2, l2, r2); } merge(treap, l2, r); }
    
bool isInTreap(node *treap, int x){ // regular | checks if x is in treap
  if(treap == NULL) return false; if(treap->v == x) return true;
  if(treap->v < x) return isInTreap(treap->r,x);
  return isInTreap(treap->l,x); }
  
  
// FUNCTIONS ONLY FOR IMPLICIT TREAP -----------------------------------
void splitImplicit(node *curr, node *&l, node *&r, int key){ // implicit
  lazy(curr); if(curr == NULL){ l = r = NULL; return; }
  if(count(curr->l) + 1 <= key){
    splitImplicit(curr->r,curr->r,r,key-count(curr->l)-1); l=curr;
  }else{splitImplicit(curr->l,l,curr->l,key); r=curr;}update(curr);}
  
// implicit | inserts node at pos (1-indexed)
void insertImplicit(node *&treap, node *x, int pos){
  lazy(treap); node *l=0,*r=0,*aux=0; splitImplicit(treap, l, r, pos-1);
  merge(aux, l, x); merge(treap, aux, r); aux = 0; }
  
void eraseImplicit(node *&treap, int pos){ // deletes node at pos
  lazy(treap); node *l=0,*r=0,*l2=0,*r2=0;
  splitImplicit(treap, l, r, pos); splitImplicit(l, l2, r2, pos-1);
  merge(treap, l2, r); l2 = r2 = l = r = NULL; }


void test(){
	node* root = 0;
	
	for(ll i = 1; i<=5; i++){
		ll v = rand() % 10;
		cout<<"value "<<v<<" at position "<<6-i<<endl;
		node* x = new node(v, rand());
		insertImplicit(root, x, 1);
	}
	cout<<"we here "<<endl;
	
	for(ll l = 1; l<= 5; l++){
		for(ll r = l; r<=5; r++){
			node *t1 = 0, *t2 = 0, *t3 = 0;
			splitImplicit(root, t1, t2, l-1);
			splitImplicit(t2, t2, t3, r-l+1);
			cout<<"we at "<<l<<" "<<r<<endl;
			cout<<t2->lazy<<endl;
			merge(root, t1, t2);
			merge(root, root, t3);
		}
	}
}

void deal(){
	in.open("rmq.in");
	out.open("rmq.out");
	ll n;
	cin>>n;
	
	
	node* root = 0;
	fori(n){
		char f;
		cin>>f;
		if(f == '+'){
			ll ps, v;
			cin>>ps>>v;
			++ps;
			node* x = new node( v, rand());
			insertImplicit(root, x, ps);
		}
		else{
			ll l, r;
			cin>>l>>r;
			node *t1 = 0, *t2 = 0, *t3 = 0;
			splitImplicit(root, t1, t2, l-1);
			splitImplicit(t2, t2, t3, r-l+1);
			cout<<t2->lazy<<'\n';
			merge(root, t1, t2);
			merge(root, root, t3);
		}
	}
	
}



int main(){
	srand(time(NULL));
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	deal();
}





