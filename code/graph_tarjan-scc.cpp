#include "template.cpp"

#define MaxN 100000

int N;
int T = 1, in[MaxN], out[MaxN], backlink[MAXN];
int comp[MaxN];
int comp_count;
vector<int> E[MaxN];
stack<int> S;

void find_sccs() {
	FOR(i,N) {
		if (!comp[i]) scc(i);
	}
}

void scc(int v) {
	vis[v] = 1;
	in[v] = T++;
	lowlink[v] = in[v];
	S.push(v);

	FOR(i,E[v].size())  {
		int w = E[v][i];
		if (!in[w]) {
			scc(w);
			lowlink[v] = min(lowlink[v], lowlink[w]);
		}
		else if (!comp[w]) { //lies in the stack, is part of the SCC
			lowlink[v] = min(lowlink[v], lowlink[w]);
		}
	}

	if (lowlink[v] == in[v]) { //is root of scc
		comp_count++;
		do {
			int w = S.top(); S.pop();
			comp[w] = comp_count; 
		}
		while (w != v);
	}
	
	out[v] = T++;	
}
