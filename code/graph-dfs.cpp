#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

#define MaxN 100000
int N, T = 1, vis[MaxN], in[MaxN], out[MaxN];
vector<int> E[MaxN];

void dfs(int v);

// Traverses oriented graph in depth-first order, N=|V|
// E - for each vertex gives the list
// of second vertices of oriented edges
// Time complexity: O(|V|+|E|)
// vis[v] determines whether v was visited
// in[v] - time of arrival to v
// out[v] - time of departure from v
/*pdf*/
void dfs_graph() {
	FOR(i,N)
		if (!vis[i]) dfs(i);
}

void dfs(int v) {
	vis[v] = 1;
	in[v] = T++;
	FOR(i,(int)E[v].size())  {
		if (!vis[E[v][i]])
			dfs(E[v][i]);
	}
	out[v] = T++;	
}
/*pdf*/

void dfs_demo() {
	N = 9;
	E[0] = vector<int>(2,1);
	E[0][1] = 5;
	E[1] = vector<int>(1,2);
	E[2] = vector<int>(1,3);
	E[3] = vector<int>(2,0);
	E[3][1] = 4;
	E[4] = vector<int>(1,5);
	E[5] = vector<int>(1,6);
	E[6] = vector<int>(1,5);
	E[7] = vector<int>(1,8);
	dfs_graph();
	FOR(n,N) printf("vertex %d in %d out %d\n", n, in[n], out[n]);
}
#ifdef RUNDEMO
int main() { dfs_demo(); return 0; }
#endif
