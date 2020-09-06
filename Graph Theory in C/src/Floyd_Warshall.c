#include <stdio.h>
#include "../storages/AdjacencyMatrixGraph.h"
#define MAX_VERTICES 100
#define INFINITY 9999999
#define MULTIPLE_EDGE 'M'
#define SINGLE_EDGE 'S'

int pi[MAX_VERTICES][MAX_VERTICES]; //  store the shortest distance from u vertex to v vertex 
int next[MAX_VERTICES][MAX_VERTICES]; // the next vertex of u vertex on the shortest distance from u vertex to v vertex 

void floydWarshall(Graph G, int s){
	int u, v, k;
	
	// init pi[u][v] = oo and next[u][v] = -1
	for(u = 1; u <= G.nbVertices; u++)
		for(v = 1; v <= G.nbVertices; v++){
			pi[u][v] = INFINITY;
			next[u][v] = -1;
		}
	
	// init distance from u to itself is zero
	for(u = 1; u <= G.nbVertices; u++)
		pi[u][u] = 0;
	
	// init the direct path from u to v is the weight of edge (u, v)
	for(u = 1; u <= G.nbVertices; u++)
		for(v = 1; v <= G.nbVertices; v++)
			if(G.A[u][v] != 0){
				pi[u][v] = G.A[u][v];
				next[u][v] = v;
			}
	
	for(k = 1; k <= G.nbVertices; k++)
		for(u = 1; u <= G.nbVertices; u++)
			for(v = 1; v <= G.nbVertices; v++)
			// if found a new path which have better distance than the old path
				if(pi[u][k] + pi[k][v] < pi[u][v]){
					pi[u][v] = pi[u][k] + pi[k][v]; // update the old path with the new path
					/* update the next u vertex on the shortest distance from u vertex to v vertex is
					the next u vertex on the shortest distance from u vertex to k vertex
					*/
					next[u][v] = next[u][k]; 
				}
}

int main(){
Graph G;
	int nbVertices, nbEdges, edge, u, v, w, s, i, j;
	char graphType, edgeType;
	FILE *file;
	file = fopen("../data/shortestPath1.txt", "r");
	
	graphType = fgetc(file);
	edgeType = fgetc(file);
	
	fscanf(file, "%d%d", &nbVertices, &nbEdges);
	
	initGraph(&G, nbVertices, graphType);
	
	if(edgeType == MULTIPLE_EDGE){
		for(edge = 1; edge <= nbEdges; edge++){
			fscanf(file,"%d%d%d", &u, &v, &w);
			addEdgeMultiple(&G, u, v, w);
		}
	}
	else{
		for(edge = 1; edge <= nbEdges; edge++){
			fscanf(file,"%d%d%d", &u, &v, &w);
			addEdgeSingle(&G, u, v, w);
		}
	}
	
	printf("Enter a vertex to start: ");
	scanf("%d", &s);
	
	floydWarshall(G, s);
	
	for(i = 1; i <= nbVertices; ++i)
		for(j = 1; j <= nbVertices; ++j){
			printf("%d -> %d = %d\n", i, j, pi[i][j]);
		//	printf("%d\n", G.next[i][j]);
		}
	
	fclose(file);
	return 0;
}
