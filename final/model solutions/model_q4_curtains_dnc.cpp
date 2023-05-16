#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
#define show(x) cerr << #x << " is " << x << endl;
#define show2(x,y) cerr << #x << " is " << x << " " << #y << " is " << y << endl;
typedef pair<int,int> ii;

const int MAXN = 500005;
const int inf = (1<<24);

vector<int> toRight[MAXN];
vector<int> toLeft[MAXN];
int closest[MAXN];

struct query{ int l, r, id; };
int ans[MAXN];

void dnc(int s, int e, vector<query> queries){
	if(queries.empty()) return;
	if(s == e){
		bool can = false;
		for(int x : toRight[s]) if(x == e) can = true;
		for(query q : queries) ans[q.id] = can;
		return;
	}
	int m = (s+e)/2;
	
	vector<ii> mono;
	for(int i = m;i >= s;i--){
		int beforeR = -1;
		int afterR = inf;
		for(int r : toRight[i]){
			if(r > e) continue;
			if(r >= m) afterR = min(afterR, r);
			else beforeR = max(beforeR, r);
		}
		
		closest[i] = inf;
		if(afterR != inf) closest[i] = min(closest[i], afterR);
		while(not mono.empty()){
			ii t = mono.back();
			if(t.first <= beforeR+1 or closest[i] <= t.second){
				mono.pop_back();
				closest[i] = min(closest[i], t.second);
			}
			else break;
		}
		mono.push_back(ii(i,closest[i]));
	}
	
	mono.clear();
	for(int i = m+1;i <= e;i++){
		int beforeL = inf;
		int afterL = -1;
		for(int l : toLeft[i]){
			if(l < s) continue;
			if(l <= m+1) afterL = max(afterL, l);
			else beforeL = min(beforeL, l);
		}
		
		closest[i] = -1;
		if(afterL <= m+1) closest[i] = max(closest[i], afterL);
		while(not mono.empty()){
			ii t = mono.back();
			if(beforeL-1 <= t.first or closest[i] >= t.second){
				mono.pop_back();
				closest[i] = max(closest[i], t.second);
			}
			else break;
		}
		mono.push_back(ii(i,closest[i]));
	}
	
	vector<query> leftqueries, rightqueries, now;
	for(query q : queries){
		if(q.r <= m) leftqueries.push_back(q);
		else if(q.l >= m+1) rightqueries.push_back(q);
		else{
			 ans[q.id] = (closest[q.l] <= q.r and closest[q.r] >= q.l);
		}
	}
	
	//if(s == 5 and e == 8) show2(closest[6], closest[8]);
	
	dnc(s, m, leftqueries);
	dnc(m+1, e, rightqueries);
	
	
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    
	int n, m, q; cin >> n >> m >> q;
	
	for(int i = 1;i <= m;i++){
		int l, r; cin >> l >> r;
		toRight[l].push_back(r);
		toLeft[r].push_back(l);
	}
	
	vector<query> queries;
	for(int i = 1;i <= q;i++){
		int l, r; cin >> l >> r;
		queries.push_back({l,r,i});
	}
	
	dnc(1,n,queries);
	
	for(int i = 1;i <= q;i++){
		if(ans[i]) cout << "YES\n";
		else cout << "NO\n";
	}
}


