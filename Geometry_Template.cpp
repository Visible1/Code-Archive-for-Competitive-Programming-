#include <bits/stdc++.h>
using namespace std;
#define mp(a,b) make_pair(a,b)
#define ff first
#define setp(a) setprecision(a)<<fixed
#define ss second
#define fori(v) for(int i=0; i<v; i++)
#define forj(v) for(int j=0; j<v; j++)
#define fork(v) for(int k=0; k<v; k++)
#define forl(v) for(int l=0; l<v; l++)
#define fort(v) for(int t=0; t<v; t++)
#define forz(v) for(int z=0; z<v; z++)
#define ll long long 
#define MAX (int)(pow(10,5)+ 10)
#define pb(a) push_back(a)
// #define cout out
// #define cin in
ll inf = pow(10,18);
ll modulo = 1000007;
double eps = 1e-6;
ifstream in;
ofstream out;


using namespace std;
using namespace rel_ops;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ld> vd;
typedef vector<vd> vvd;
typedef pair<ll, ll> pii;
typedef vector<pii> vpii;
namespace std {
template<class T>inline bool operator<(const complex<T>& a,const complex<T>& b){
  return a.real()<b.real() || (a.real() == b.real() && a.imag()<b.imag()); } };
const int MAXN=50, MAXM=50, N=50, M=50;
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a%b); }
//*/
// ios::sync_with_stdio(0); cin.tie(0); // faster io, but unsyncs with cstdio
const ll INF = 0x3f3f3f3f; const ld EPS = 1e-9; const ld PI = acos(-1.L);
////////////////////////////////////////////////////////////////////////////////
// Custom Fast complex class (Tested on PacNW2013J Phuket2016G CHICAGO 2012H)
////////////////////////////////////////////////////////////////////////////////
// Tested with FFT on NAIPC 2016E, SWERC14C
// Replace all .real() with .x and .imag() with .y for nonstandard operations
//*!
namespace custom_complex {
//*/
template<class T> struct cplx {
  T x, y; cplx() {x = 0.0; y = 0.0;}
  cplx(T nx, T ny=0) {x = nx; y = ny;}
  cplx operator+(const cplx &c) const {return {x + c.x, y + c.y};}
  cplx operator-(const cplx &c) const {return {x - c.x, y - c.y};}
  cplx operator*(const cplx &c) const {return {x*c.x - y*c.y, x*c.y + y*c.x};}
  cplx& operator*=(const cplx &c) { return *this={x*c.x-y*c.y, x*c.y+y*c.x}; }
  // Only supports right scalar multiplication like p*c
  template<class U> cplx operator*(const U &c) const {return {x*c,y*c};}
  template<class U> cplx operator/(const U &c) const {return {x/c,y/c};} };
#define polar(r,a)  (pt){r*cos(a),r*sin(a)}
typedef cplx<ld> pt;
typedef vector<pt> pol;
pt operator*(ld c, const pt p) { return {p.x*c,p.y*c};} // for left mult. c*p
// useful for debugging
ostream&operator<<(ostream &o,const pt &p){o<<"("<<p.x<<","<<p.y<<")";return o;}
ld cp(const pt& a, const pt& b) { return a.x*b.y - b.x*a.y; }
ld dp(const pt& a, const pt& b) { return a.x*b.x + a.y*b.y; }
inline ld abs(const pt &a) {return sqrt(a.x*a.x + a.y*a.y);}
inline ld arg(const pt &a) {return atan2(a.y,a.x);}
ld ang(pt &a, pt &b, pt &c) { return atan2(cp(a-b,b-c),dp(a-b,b-c)); }
namespace std{
template<class T>inline bool operator<(const cplx<T>& a,const cplx<T>& b){
  return a.x<b.x || (a.x == b.x && a.y<b.y); } };
inline bool cmp_lex(const pt& a, const pt& b) {
  return a.x<b.x-EPS||(a.x<b.x+EPS&&a.y<b.y-EPS);}
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.y<b.y-EPS||(a.y<b.y+EPS&&a.x<b.x-EPS);}
//*!
}
//*/
////////////////////////////////////////////////////////////////////////////////
// General 2D geometry, Polygon cutting, Point in polygon
////////////////////////////////////////////////////////////////////////////////
ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
// dist(const pt& a, const pt& b) ==> abs(a-b)
inline bool eq(const pt &a, const pt &b) { return abs(a-b) < EPS; }
inline ld sgn(const ld& x) { return abs(x) < EPS ? 0 : x/abs(x); }
inline bool cmp_lex(const pt& a, const pt& b) {
  return a.real()<b.real()-EPS||(a.real()<b.real()+EPS&&a.imag()<b.imag()-EPS);}
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS||(a.imag()<b.imag()+EPS&&a.real()<b.real()-EPS);}
// handles ALL cases, uncomment/edit the 3 marked lines to exclude endpoints
bool seg_x_seg(pt a1, pt a2, pt b1, pt b2) {
  //if (eq(a1,a2) || eq(b1,b2)) return false; // uncomment to exclude endpoints
  ld za = abs(a2-a1), zb = abs(b2-b1); za=za>EPS?1/za:0; zb=zb>EPS?1/zb:0;
  int s1 = sgn(cp(a2-a1, b1-a1)*za), s2 = sgn(cp(a2-a1, b2-a1)*za);
  int s3 = sgn(cp(b2-b1, a1-b1)*zb), s4 = sgn(cp(b2-b1, a2-b1)*zb);
  if(!s1 && !s2 && !s3) { // collinear
    if (cmp_lex(a2, a1)) swap(a1, a2); if (cmp_lex(b2, b1)) swap(b1, b2);
    //return cmp_lex(a1, b2) && cmp_lex(b1, a2);//uncomment to exclude endpoints
    return !cmp_lex(b2, a1) && !cmp_lex(a2, b1);
  } return s1*s2 <= 0 && s3*s4 <= 0; } //change to < to exclude endpoints
 
inline pt line_inter(const pt &a, const pt &b, const pt &c, const pt &d) {
  return a + cp(c - a, d - c) / cp(b - a, d - c) * (b - a); }
 
// Projection of (a -> p) to vector (a -> b), SIGNED - positive in front
inline ld proj_dist(const pt &a, const pt &b, const pt &p) {
  return dp(b - a, p - a) / abs(b - a); }
 
// SIGNED distance. Pt on the right of vector (a -> b) will be NEGATIVE.
inline ld lp_dist(const pt &a, const pt &b, const pt &p) {
  return cp(b - a, p - a) / abs(b - a); }
 
// Line segment (a, b) to pt p distance.
inline ld lsp_dist(const pt &a, const pt &b, const pt &p) {
  return dp(b - a, p - a) > 0 && dp(a - b, p - b) > 0 ?
    abs(cp(b - a, p - a) / abs(b - a)) : min(abs(a - p), abs(b - p)); }
 
// Closest pt on line segment (a, b) to pt p.
inline pt lsp_closest(const pt &a, const pt &b, const pt &p) {
  if (dp(b - a, p - a) > 0 && dp(a - b, p - b) > 0)
    return abs(cp(b-a, p-a)) < EPS ? p : line_inter(a, b, p, p+(a-b)*pt(0,1));
  return abs(a - p) < abs(b - p) ? a : b; }
 
// Area of a polygon (convex or concave). Always non-negative.
ld area(const pol &v) { ld s = 0; int n = v.size();
  for(int i = n-1, j = 0; j < n; i = j++) s += cp(v[i], v[j]); return abs(s)/2;}
 
// orientation does not matter
pt centroid(const pol &v) {
  pt res; ld A = 0; int n = v.size();
  for(int i=n-1,j=0;j<n;i=j++) A+=cp(v[i],v[j]), res+=(v[i]+v[j])*cp(v[i],v[j]);
  return abs(A) < EPS ? res : res/3.L/A; }
 
// Left of the vector (a -> b) will be cut off. Convex polygons tested UVa 10117
// Simple polygon tested KTH Challenge 2013 G
pol cut_polygon(const pol &v, const pt &a, const pt &b) { pol out;
  for(int i = v.size() - 1, j = 0; j < v.size(); i = j++) {
    if(cp(b-a, v[i]-a) < EPS) out.push_back(v[i]);
    if(sgn(cp(b-a, v[i]-a)) * sgn(cp(b-a, v[j]-a)) < 0) {
      pt p = line_inter(a, b, v[i], v[j]);
      if(!out.size() || abs(out.back() - p) > EPS) out.push_back(p); } }
  while(out.size() && abs(out[0] - out.back()) < EPS) out.pop_back();
  return out; }
 
 ////////////////////////////////////////////////////////////////////////////////
// Circle-circle intersection (TESTED UVa 453)
////////////////////////////////////////////////////////////////////////////////
// Return number of intersections. Circles must not be identical.
int cc_inter(pt p1, ld r1, pt p2, ld r2, pt &i1, pt &i2) {
  ld dq=norm(p1-p2), rq=r1*r1-r2*r2; pt c=(p1+p2)*0.5L + (p2-p1)*rq*0.5L/dq;
  ld dt=2.0*dq*(r1*r1+r2*r2)-dq*dq-rq*rq;
  if(dt < -EPS) return 0; if(dt < EPS) { i1=i2=c; return 1; }
  dt=sqrt(dt)*0.5/dq; i1=c+(p2-p1)*pt(0,1)*dt; i2=c-(p2-p1)*pt(0,1)*dt;
  return 2; }
  
// Does NOT include points on the ends of the segment.
inline bool on_segment(const pt &a, const pt &b, const pt &p) {
  return abs(cp(b-a, p-a)) < EPS && dp(b-a, p-a) > 0 && dp(a-b, p-b) > 0; }
 
// Checks if p lies on the boundary of a polygon v.
inline bool on_boundary(const pol &v, const pt &p) { bool res = false;
  for(int i=v.size()-1,j=0;j<v.size();i=j++)
    res |= on_segment(v[i], v[j], p) | (abs(p-v[i]) < EPS); return res; }
 
// orientation does not matter !!!
bool pt_in_polygon(const pt &p, const pol &v){ if(on_boundary(v,p)) return true;
  ld res = 0; for(int i = v.size() - 1, j = 0; j < v.size(); i = j++)
    res += atan2(cp(v[i] - p, v[j] - p), dp(v[i] - p, v[j] - p));
  return abs(res) > 1; } // will be either 2*PI or 0


// points outside polygon
// minimum radius to cover whole Polygon

void test(){
	ll n , m ;
	cin>>n;
	pol pl;
	fori(n){
		ld x,y;
		cin>>x>>y;
		pl.pb(pt(x,y));
	}
	pol crc;
	cin>>m;
	fori(m){
		ld x,y;
		cin>>x>>y;
		crc.pb(pt(x,y));
	}
	ld lo = 0, hi = 1e9;
	while((hi-lo)>eps){
		ld mid = (lo+hi)/2;
		pol check;
		fori(m){
			for(ll j = i+1; j<m; j++){
				pt one(pl[0]), two(pl[0]);
				cc_inter(crc[i],mid,crc[j], mid, one,two);
				if(pt_in_polygon(one, pl))
				check.pb(one);
				if(pt_in_polygon(two, pl))
				check.pb(two);
			}
		}
		for(auto& el : pl)
			check.pb(el);
		bool good = 1;
		for(auto& el: check){
			bool ok = 0;
			fori(m){
				if(lsp_dist(el, el, crc[i])+eps < mid){
					ok = 1;
					break;
				}
			}
			good &= ok;
			if(!good)
				break;
		}
		if(good)
			hi = mid;
		else
			lo = mid;
	}
	cout<<setp(13)<<lo;
}
 

int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	deal();
}



/* 
6 8 
1 2
2 3
3 4
4 1
2 5
3 5
1 6
4 6
*/
