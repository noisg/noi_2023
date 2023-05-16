#include <bits/stdc++.h>
using namespace std;

#define MAXN 200'000
#define MAXM 200'000
#define LOGMAXN 18          // ceil(log2(MAXN))

typedef pair<int, int> ii;

int N, M, depth[MAXN + 5], parent[MAXN + 5][LOGMAXN + 5], fenwick[MAXN + 5];
int subtree_start[MAXN + 5], subtree_end[MAXN + 5], preord_cntr;
int A[MAXM + 5], B[MAXM + 5], app_LCA[MAXM + 5], app_process[MAXM + 5];
bool is_chosen[MAXN + 5];
vector <int> adjlist[MAXN + 5], chosen;

int lsb(int x)
{
	return x & (-x);
}

int fw_point_query(int x)
{
	int v = 0;
	for (; x > 0; x -= lsb(x))
	{
		v += fenwick[x];
	}
	return v;
}

void fw_range_update(int l, int r, int v)
{
	for (; l <= N; l += lsb(l))
	{
		fenwick[l] += v;
	}
	for (r++; r <= N; r += lsb(r))
	{
		fenwick[r] -= v;
	}
}

void dfs_precompute(int v, int u, int d)
{
	depth[v] = d;
	parent[v][0] = u;
	subtree_start[v] = ++preord_cntr;

	for (int b = 1; b <= LOGMAXN; b++)
	{
		parent[v][b] = parent[parent[v][b - 1]][b - 1];
	}

	for (int w : adjlist[v])
	{
		if (w == parent[v][0])
		{
			continue;
		}

		dfs_precompute(w, v, d + 1);
	}

	subtree_end[v] = preord_cntr;
}

int get_lca(int u, int v)
{
	if (depth[u] < depth[v])
	{
		swap(u, v);
	}

	int depth_diff = depth[u] - depth[v];

	for (int b = LOGMAXN; b >= 0; b--)
	{
		if ((1 << b) & depth_diff)
		{
			u = parent[u][b];
		}
	}

	if (u == v)
	{
		return u;
	}

	for (int b = LOGMAXN; b >= 0; b--)
	{
		if (parent[u][b] != parent[v][b])
		{
			u = parent[u][b];
			v = parent[v][b];
		}
	}

	assert(parent[u][0] == parent[v][0]);
	return parent[u][0];
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	for (int i = 1; i <= N - 1; i++)
	{
		int u, v;
		cin >> u >> v;
		adjlist[u].push_back(v);
		adjlist[v].push_back(u);
	}

	for (int j = 1; j <= M; j++)
	{
		cin >> A[j] >> B[j];
	}

	preord_cntr = 0;
	dfs_precompute(1, 1, 1);

	for (int j = 1; j <= M; j++)
	{
		app_LCA[j] = get_lca(A[j], B[j]);
		app_process[j] = j;
	}

	sort(
		app_process + 1, app_process + M + 1, 
		[](int l, int r)
		{
			if (depth[app_LCA[l]] == depth[app_LCA[r]])
			{
				return (l < r);
			}
			else
			{
				return (depth[app_LCA[l]] > depth[app_LCA[r]]);
			}
		}
	);

	for (int i = 1; i <= M; i++)
	{
		int j = app_process[i];
		
		bool resolved = (
			is_chosen[app_LCA[j]] ||
			fw_point_query(subtree_start[A[j]]) > fw_point_query(subtree_start[app_LCA[j]]) ||
			fw_point_query(subtree_start[B[j]]) > fw_point_query(subtree_start[app_LCA[j]])
		);

		if (!resolved)
		{
			is_chosen[app_LCA[j]] = true;
			chosen.push_back(app_LCA[j]);
			fw_range_update(subtree_start[app_LCA[j]], subtree_end[app_LCA[j]], 1);
		}
	}

	cout << chosen.size() << "\n";

	for (int i = 0; i < (int)chosen.size(); i++)
	{
		cout << chosen[i] << " \n"[i + 1 == (int)chosen.size()];
	}

	return 0;
}
