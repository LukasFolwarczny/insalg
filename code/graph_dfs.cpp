#include "template.cpp"

#define MaxN 100000

int T = 1, vis[MaxN], in[MaxN], out[MaxN];
vector<int> E[MaxN];

void dfs(int v) {
	vis[v] = 1;
	in[v] = T++;
	FOR(i,E[v].size())  {
		if (!visited[E[v][i]])
			dfs(E[v][i]);
	}
	out[v] = T++;	
}
