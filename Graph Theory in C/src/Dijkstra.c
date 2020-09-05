#include <stdio.h>
#include "../storages/AdjacencyMatrixGraph.h"
#define MAX_VERTICES 100
#define NO_EDGE 0
#define INFINITY 99999
#define MULTIPLE_EDGE 'M'
#define SINGLE_EDGE 'S'

int pi[MAX_VERTICES]; // store shortest distance from u vertex to v vertex
int p[MAX_VERTICES]; // store parent of u vertex in shortest distance from u vertex to v vertex
int mark[MAX_VERTICES]; // check a vertex is visited or not
int path[MAX_VERTICES];

int dijkstra(Graph *G, int s){
	int it, i, j, v, u;
	
	// init pi[i] = oo and mark[i] = 0
	for(i = 1; i <= G->n; ++i){
		pi[i] = INFINITY;
		mark[i] = 0;
	}
	
	pi[s] = 0; // init distance from s to itself  is zero
	p[s] = -1; // s vertex has not parent
	
	// loop n-1 (or n) times
	for(it = 1; it < G->n; ++it){
		// find a vertex with minimum pi and do not visited
		int min_pi = INFINITY;
		for(j = 1; j <= G->n; ++j)
			if(mark[j] == 0 && pi[j] < min_pi){
				min_pi = pi[j];
				u = j; // save u
			}
		mark[u] = 1; // visited u
		
		// get all adjacent vertices
		List list = neighbors(G, u);
		
		// traversing all adjacent vertices
		for(i = 1; i <= Size(&list); ++i){
			int v = element_at(&list, i);
			
			// if found a new path with better distance than the old path
			if(pi[u] + G->A[u][v] < pi[v]){
				pi[v] = pi[u] + G->A[u][v]; // update the old path with the new path
				p[v] = u; // update parent of v
			}
		}
//		for(v = 1; v <= G->n; ++v)
//			if(G->A[u][v] != NO_EDGE && mark[v] == 0)
//				if(pi[u] + G->A[u][v] < pi[v]){
//					pi[v] = pi[u] + G->A[u][v];
//					p[v] = u;
//				}
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

int main(){
	Graph G;
	int nbVertices, nbEdges, edge, u, v, w, s, i;
	char graphType, edgeType;
	FILE *file;
	file = fopen("../data/shortestPath.txt", "r");
	
	graphType = fgetc(file);
	edgeType = fgetc(file);
	
	fscanf(file, "%d%d", &nbVertices, &nbEdges);
	
	init_graph(&G, nbVertices, graphType);
	
	if(edgeType == MULTIPLE_EDGE){
		for(edge = 1; edge <= nbEdges; ++edge){
			fscanf(file,"%d%d%d", &u, &v, &w);
			addEdgeMultiple(&G, u, v, w);
		}
	}
	else{
		for(edge = 1; edge <= nbEdges; ++edge){
			fscanf(file,"%d%d%d", &u, &v, &w);
			addEdgeSingle(&G, u, v, w);
		}
	}
	
	printf("Enter a vertex to start: ");
	scanf("%d", &s);
	
	v = dijkstra(&G, s);
	
	for(u = 1; u <= nbVertices; ++u)
		printf("\nDistance from %d to %d is %d\n", s, u, pi[u]);
	
	printPath(G, v);
	
	fclose(stdin);
	return 0;
}
