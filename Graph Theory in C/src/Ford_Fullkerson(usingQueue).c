#include <stdio.h>
#include "../storages/Queue.h"
#define MAXN 100
#define NO_EDGE 0
#define INF 99999999

typedef struct{
	int nbVertices;
	int c[MAXN][MAXN]; // capacity of an edge
	int f[MAXN][MAXN]; // flow
} Graph;

typedef struct{
	int dir; // >0: + label, <0: - label, =0: no label
	int pre; // previous vertex of u vertex
	int sigma; // the amount of flow which can increase flow
} Label;

void initGraph(Graph *G, int n){
	int i, j;
	G->nbVertices = n;
	for(i = 1; i <= n; i++)
		for(j = 1; j <= n; j++)
			G->c[i][j] = NO_EDGE;
}

void initFlow(Graph *G){
	int i, j;
	for(i = 1; i <= G->nbVertices; i++)
		for(j = 1; j <= G->nbVertices; j++)
			G->f[i][j] = 0;
}

void addEdge(Graph *G, int u, int v, int w){
	G->c[u][v] = w;
}

int adjacent(Graph G, int x, int y){
	return G.c[x][y] != 0;
}

int min(int a, int b){
	return a < b ? a:b;
}

Label labels[MAXN];

int fordFullkerson(Graph G, int s, int t){
	int i, j, u, v, sumFlow = 0;
	Queue Q;
	initFlow(&G);
	while(1){
		int found = 0;
		for(i = 1; i <= G.nbVertices; i++)
			labels[i].dir = 0;
		labels[s].dir = 1;
		labels[s].pre = s;
		labels[s].sigma = INF;
		initQueue(&Q);
		push(&Q,s);
		while(!empty(Q)){
			u = top(Q);
			pop(&Q);
			for(v = 1; v <= G.nbVertices; v++){
				if(labels[v].dir == 0 && adjacent(G,u,v) && G.f[u][v] < G.c[u][v]){
					labels[v].dir = 1;
					labels[v].pre = u;
					labels[v].sigma = min(labels[u].sigma, G.c[u][v] - G.f[u][v]);
					push(&Q,v);
				}
				if(labels[v].dir == 0 && adjacent(G,v,u) && G.f[v][u] > 0){
					labels[v].dir = -1;
					labels[v].pre = u;
					labels[v].sigma = min(labels[u].sigma, G.f[v][u]);
					push(&Q,v);
				}
			}
			if(labels[t].dir != 0){
				found = 1;
				break;
			}
		}
		int x, sigma;
		if(found == 1){
			x = t;
			sigma = labels[t].sigma;
			sumFlow += sigma;
			while(x != s){
				u = labels[x].pre;
				if(labels[x].dir > 0) 
					G.f[u][x] += sigma; // increasing flow
				else 
					G.f[x][u] -= sigma; // decreasing flow 
				x = u;
			}
		}
		else
			break;
	}
	return sumFlow;
}

void minimumCut(Graph G){
	int i;
	printf("\nX0: ");
	for(i = 1; i <= G.nbVertices; ++i)
		if(labels[i].dir != 0)
	printf("%d ", i);
	printf("\nY0: ");
	for(i = 1; i <= G.nbVertices; ++i)
		if(labels[i].dir == 0)	
			printf("%d ", i);
}

int main(){
	Graph G;
	int n, m, e, u, v, w, i, j;
	freopen("../data/network.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	initGraph(&G, n);
	
	for(e = 0; e < m; ++e){
		scanf("%d%d%d", &u, &v, &w);
		addEdge(&G,u,v,w);
	}
	
	int maxFlow = fordFullkerson(G,1,n);
	
	// display the maximum network flow	
	printf("Max Flow: %d", maxFlow);	

	// display minimum s-t cut
	minimumCut(G);
	/*
	printf("\nX0: ");
	for(i = 1; i <= n; ++i)
		if(labels[i].dir != 0)
			printf("%d ", i);
	
	printf("\nY0: ");
	for(i = 1; i <= n; ++i)
		if(labels[i].dir == 0)
			printf("%d ", i); */
			
	close(stdin);
	return 0;
}
