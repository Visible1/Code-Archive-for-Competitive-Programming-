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
const ll INF = 0x3f3f3f3f;
const ll inf =  pow(10,18);
ll modulo = pow(10,9) + 7;
#define MAX (int)(2502 + 10)
struct  Node
{
    Node* left ;
	Node* right ;
	int leftsay = 0;
	int rightsay = 0;	
};
void Insert(Node* Root , int eded, int necenci)
{
	while(necenci>-1){
		if(eded & (1<<necenci))
		{
	//		cout<<"rrrrrrrr \n";
			Root->rightsay++;
			if(Root->right == NULL)
				Root->right = new Node();
			Root = Root->right;
		}
		else{
	//		cout<<"llllllll \n";
			Root->leftsay++;
			if(Root->left == NULL)
				Root->left = new Node();
			Root = Root->left;
		}
		--necenci;
	}
}
void checker(Node* root, int eded, int nece, int& cons){
	while(nece>-1){
	//	cout<<"we are at level "<<nece<<" the leftsay: "<<root->leftsay<<" the rightsay: "<<root->rightsay<<endl;
		if((1<<nece)&eded){
			if(root->rightsay>0){
				root->rightsay--;
				root = root->right;
			}
			else{
				root->leftsay--;
				cons^=(1<<nece);
				root = root->left;
			}
		}
		else{
			if(root->leftsay>0){
				root->leftsay--;
				root = root->left;
			}
			else{
				root->rightsay--;
				cons^=(1<<nece);
				root = root->right;
			}
		}
		--nece;
	}
}

void deal(){
	// Node struct for typical Xor Maximization Problems
}



int main()  
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	deal();
} 



























