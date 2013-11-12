#include "template.cpp"
// Lukas Folwarczny, 2013
// http://atrey.karlin.mff.cuni.cz/~folwar/insalg/

// Goldberg algorithm for finding the maximum flow.
// It is more widely known as the Push-Relabel algorithm.
// This is the FIFO variant of Goldberg/Push-Relabel.
// Algorithm runs in O(|V|^3).

// Alpha-version - serious test have not yet been run.

/*pdf*/
// Input: A symmetric oriented graph on the vertices {0,...,N-1} with M edges.
// Multiedges are allowed.
// C[i][0] gives the capacity of oriented edge E[i][0] -> E[i][1]
// C[i][1] gives the capacity of oriented edge E[i][1] -> E[i][0]
// s is a source vertex, t is a target vertex.
// Returns field F, F[i][0] is flow in the edge E[i][0] -> E[i][1], F[i][1] is the flow in
// the opposite edge. Size of the flow is stored in F_size.
int ** goldberg(int N, int M, int E[][2], int C[][2], int s, int t, int * F_size) {
	int ** F = new int * [M];
	for (int i = 0; i < M; i++) { F[i] = new int [2](); }
	int * H = new int [N](); // height of each vertex
	int * X = new int [N](); // excess at each vertex
	vector<int> * L = new vector<int> [N]();
	vector<int> * Ne = new vector<int> [N]();

	queue<int> Q;

	for (int i = 0; i < M; i++) {
		Ne[E[i][0]].push_back(i); Ne[E[i][1]].push_back(i); }
	
	// Init the algorithm - raise source and construct the initial preflow
	H[s] = N;
	for (int i = 0; i < Ne[s].size(); i++) {
		int e = Ne[s][i];
		bool o = E[e][1] == s;
		int w = E[e][1-o];
		F[e][o] = C[e][o];
		X[s] -= C[e][o];
		X[w] += C[e][o];
	}

	// All active vertices go to the queue
	for (int v = 0; v < N; v++)
		if (X[v] > 0)
			Q.push(v);

	while (!Q.empty()) {
		int v = Q.front(); Q.pop();
		if (v == t) continue;
		while (X[v] > 0 && !L[v].empty()) {
			int e = L[v].back();
			L[v].pop_back();
			int o = E[e][1] == v;
			int w = E[e][1-o];

			// Delta is the amount of flow we push
			int delta = min(X[v], C[e][o] - F[e][o] + F[e][1-o]);
			
			if (delta == 0 || H[v] <= H[w]) continue;
			if (X[w] == 0) Q.push(w);

			X[v] -= delta; X[w] += delta;
			int x = C[e][o] - F[e][o];
			F[e][o] += min(delta, C[e][o] - F[e][o]);
			delta -= x;
			if (delta > 0) F[e][1-o] -= delta;
		}
		if (X[v] > 0) {
			// If the vertex still has excess, we raise it and compute L - list
			// of edges ready to push
			H[v]++;
			for (int i = 0; i < Ne[v].size(); i++) {
				int e = Ne[v][i];
				bool o = E[e][1] == v;
				int w = E[e][1-o];
				if (H[v] > H[w] &&  C[e][o] - F[e][o] + F[e][1-o] > 0) {

					L[v].push_back(e);
					DP("e %d\n", e);
				}
			}
			Q.push(v);
		}
	}

	*F_size = X[t];

	delete [] H;
	delete [] X;
	delete [] L;
	delete [] Ne;
	return F;
}
/*pdf*/

void goldberg_demo() {
	int N1 = 4, M1 = 5;
	int E1[5][2] = { {0, 1},  {0, 2}, {1, 2}, {1, 3}, {2, 3}};
	int C1[5][2] = { {500, 0}, {400, 0},  {1, 0}, {200, 0},  {300, 0} };
	int s1 = 0, t1 = 3;
	int F1size;
	int ** F1 = goldberg(N1, M1, E1, C1, s1, t1, &F1size);
	printf("Max flow size: %d\n", F1size);
	for (int i = 0; i < M1; i++) {
		printf("Edge e = %d -> %d, c(e) = %d, f(e) = %d\n", E1[i][0], E1[i][1], C1[i][0],
		F1[i][0]);
		printf("Edge e = %d -> %d, c(e) = %d, f(e) = %d\n", E1[i][1], E1[i][0], C1[i][1],
		F1[i][1]);
	}
}

#ifdef RUNDEMO
int main() { goldberg_demo(); return 0; }
#endif
