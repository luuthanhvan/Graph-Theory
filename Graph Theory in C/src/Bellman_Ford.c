#include <stdio.h>
#include "../storages/EdgeListGraph.h"
#define MAX_VERTICES 100
#define INFINITY 99999

int pi[MAX_VERTICES];
int p[MAX_VERTICES];
int path[MAX_VERTICES];

int bellmanFord(Graph G, int s){
	int it, e, u, v, w, i;
	for(i = 1; i <= G.nbVertices; i++)
		pi[i] = INFINITY;
		
	pi[s] = 0;
	p[s] = -1;
	for(it = 1; it < G.nbVertices; it++){
		for(e = 0 ; e < G.nbEdges; e++){
			u = G.edges[e].u;
			v = G.edges[e].v;
			w = G.edges[e].w;
			if(pi[u] + w < pi[v]){
				pi[v] = pi[u] + w;
				p[v] = u;
			}
		}
	}
	
	return u; // return the last visited vertex
}

void printPath(Graph G, int v){
	int curVertex = v; // current vertex
	int cnt = 0, u;
	
	while(curVertex != -1){
		path[cnt] = curVertex;
		cnt++;
		curVertex = p[curVertex];
	}
	
	printf("\nShortest path: ");
	for(u = cnt-1; u >= 0; u--){
		printf("%d", path[u]);
		if(u == 0) break; // prevent to add arrow between 2 vertices
		printf(" -> "); // add arrow between 2 vertices
	}
}

int checkContainNegativeCycle(Graph G){
	int isNegative, e;
	// checking for negative cycle
	for(e = 0; e < G.nbEdges; e++){
		int u = G.edges[e].u;
		int v = G.edges[e].v;
		int w = G.edges[e].w;
		if(pi[u] != INFINITY && pi[u] + w < pi[v]){
			isNegative = 1; // detect a negative cycle
			return isNegative;
		}
	}
}

int main(){
	Graph G;
	int nbVertices, nbEdges, edge, u, v, w, s, i;
	char graphType, edgeType;
	FILE *file;
	file = fopen("../data/shortestPath.txt", "r");
//	file = fopen("../data/shortestPath_negativeCycle.txt", "r");
	
	graphType = fgetc(file);
	edgeType = fgetc(file);
	
	fscanf(file, "%d%d", &nbVertices, &nbEdges);
	
	initGraph(&G, nbVertices);
	
	for(edge = 1; edge <= nbEdges; edge++){
		fscanf(file,"%d%d%d", &u, &v, &w);
		addEdge(&G, u, v, w);
	}
	
	printf("Enter a vertex to start: ");
	scanf("%d", &s);
	
	v = bellmanFord(G, s);
	
	for(u = 1; u <= nbVertices; ++u)
		printf("\nDistance from %d to %d is %d\n", s, u, pi[u]);
	
	printPath(G, v);
	
	/*
	if(checkContainNegativeCycle(G) == 1)
		printf("\nThe graph contains negative cycle.");
	else
		printf("\nThe graph do not contains negative cycle."); 
	*/
	fclose(stdin);
	return 0;
}
