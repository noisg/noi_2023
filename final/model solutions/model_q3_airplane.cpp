#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

int n, E; 
int H[200005];

vector<int> disS, disE;
vector<int> adj[200005];
int vis[200005];

void dijkstra(int S, vector<int> &dis){
	dis.resize(n+1);
	fill(dis.begin(), dis.end(), 1e9);
	fill(vis,vis+n+1,0);
	
	priority_queue<ii, vector<ii>, greater<ii> > pq;
	dis[S] = 0;
	pq.push(ii(0,S));
	
	while(not pq.empty()){
		int u = pq.top().second; pq.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(int v : adj[u]){
			if(dis[v] > max(H[v], dis[u] + 1)){
				dis[v] = max(H[v], dis[u] + 1);
				pq.push(ii(dis[v],v));
			}
		}
	}
}


signed main(){
	ios_base::sync_with_stdio(false); cin.tie(0); //fast input/output
	
	cin >> n >> E;
	for(int i = 1;i <= n;i++) cin >> H[i];
	for(int i = 1;i <= E;i++){
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	dijkstra(1, disS);
	dijkstra(n, disE);
	
	int ans = 1e9;
	for(int u = 1;u <= n;u++){
		//cerr << disS[u] << " " << disE[u] << '\n';
		ans = min(ans, max(disS[u],disE[u])*2);
		for(int v : adj[u]){
			ans = min(ans, max(disS[u],disE[v])*2 + 1);
			ans = min(ans, max(disS[v],disE[u])*2 + 1);
		}
	}
	
	cout << ans;
}
