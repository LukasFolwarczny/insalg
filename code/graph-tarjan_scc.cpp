#include "template.cpp"
#define MaxN 100000

// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

int N;
int T = 1, vis[MaxN], in[MaxN], out[MaxN], backlink[MaxN];
int comp_count, comp[MaxN];
vector<int> E[MaxN];
stack<int> S;

void scc(int v);

//Tarjan algorithm for finding strong components of graph
//Same notation as in graph_dfs
//Time complexity: O(|V|+|E|)
//Output: Vertex v is part of SCC comp[v]
void find_sccs() {
	FOR(i,N) {
		if (!vis[i]) scc(i);
	}
}

void scc(int v) {
	vis[v] = 1;
	in[v] = T++;
	backlink[v] = in[v];
	S.push(v);

	FOR(i,E[v].size())  {
		int w = E[v][i];
		if (!vis[w]) {
			scc(w);
			backlink[v] = min(backlink[v], backlink[w]);
		}
		else if (!comp[w]) { //lies in the stack, is part of the SCC
			backlink[v] = min(backlink[v], in[w]);
		}
	}

	if (backlink[v] == in[v]) { //is root of scc
		comp_count++;
		int w;
		do {
			w = S.top(); S.pop();
			comp[w] = comp_count; 
		}
		while (w != v);
	}
	out[v] = T++;	
}

void example() {
	N = 7;
	E[0] = vector<int>(2,1);
	E[0][1] = 5;
	E[1] = vector<int>(1,2);
	E[2] = vector<int>(1,3);
	E[3] = vector<int>(2,0);
	E[3][1] = 4;
	E[4] = vector<int>(1,5);
	E[5] = vector<int>(1,6);
	E[6] = vector<int>(1,5);
	find_sccs();
	FOR(n,N) printf("vertex %d in component %d\n", n, comp[n]);
}

int main() { example(); return 0; }
