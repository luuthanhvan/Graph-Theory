#include "List.h"
#define MAX_VERTICES 100
#define DIRECTED 'D'
#define UNDIRECTED 'U'

int mark[MAX_VERTICES];

// represent an adjacency matrix graph
typedef struct{
	int n;
	int A[MAX_VERTICES][MAX_VERTICES];
	char directed;
} Graph;

void init_graph(Graph *G, int n, char directed){
	int i, j;
	G->n = n;
	G->directed = directed;
	for(i = 1; i <= n; ++i)
		for(j = 1; j <= n; ++j)
			G->A[i][j] = 0;
}

// add edge for a graph which have multiple edges
void addEdgeMultiple(Graph *G, int u, int v){
	if(G->directed == DIRECTED){
		G->A[u][v] += 1;
	}
	else{
		G->A[u][v] += 1;
		G->A[v][u] += 1;
	}
}

// add edge for a graph which have single edge
void addEdgeSingle(Graph *G, int u, int v){
	if(G->directed == DIRECTED){
		G->A[u][v] = 1;
	}
	else{
		G->A[u][v] = 1;
		G->A[v][u] = 1;
	}
}

int degree(Graph *G, int x){
	int deg = 0, y;
	for(y = 1; y <= G->n; ++y)
		if(G->A[x][y] == 1)
			deg += G->A[x][y];
	return deg;
}

int adjacent(Graph *G, int x, int y){
	return G->A[x][y] > 0;
}

List neighbors(Graph *G, int x){
	int y;
	List list;
	make_null(&list);
	for(y = 1; y <= G->n; ++y)
		if(adjacent(G,x,y))
			push_back(&list,y);
	return list;
}
