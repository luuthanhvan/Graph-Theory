#include <stdio.h>
#include "../storages/AdjacencyMatrixGraph.h"
#define NO_EDGE 0
#define INFINITY 9999999
#define MULTIPLE_EDGE 'M'
#define SINGLE_EDGE 'S'

int mark[100];
int pi[100];
int p[100];
int sumW = 0;

void prim(Graph G, Graph *T){
	int u, v, it, i, j;
	initGraph(T, G.nbVertices, 'D');
	
	for(u = 1; u <= G.nbVertices; u++){
		mark[u] = 0;
		pi[u]= INFINITY;
		p[u] = 0;
	}
	
	pi[1] = 0;
	
	for(v = 1; v < G.nbVertices; v++)
		if(G.A[1][v] != NO_EDGE){
			pi[v] = G.A[1][v];
			p[v] = 1;
		}
		
	mark[1] = 1;
	
	for(it = 1; it < G.nbVertices; it++){
		int minDist, minVertex;
		minDist = INFINITY;
		
		for(u = 1; u <= G.nbVertices; u++)
			if(mark[u] == 0)
				if(minDist > pi[u]){
					minDist = pi[u];
					minVertex = u;
				}
		
		u = minVertex;
		mark[u] = 1;
		addEdgeSingle(T, u, p[u], minDist);
		sumW += minDist;
		
		for(v = 1; v <= G.nbVertices; v++){
			if(G.A[u][v] != NO_EDGE && mark[v] == 0)
				if(pi[v] > G.A[u][v]){
					pi[v] = G.A[u][v];
					p[v] = u;
				}
		}
	}
}

//	display minimum spanning tree
void printMST(Graph T){
	int u, v;
	for(u = 1; u <= T.nbVertices; u++){
		for(v = 1; v <= T.nbVertices; v++){
			if(T.A[u][v] != 0){
				printf("(%d, %d) = %d\n", u, v, T.A[u][v]);
			}
		}
	}
}

int main(){
	Graph G, T;
	int nbVertices, nbEdges, edge, u, v, w, s, i;
	char graphType, edgeType;
	FILE *file;
	file = fopen("../data/tree.txt", "r");
	
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
	
	prim(G, &T);
	printf("Sum weight = %d\n", sumW);

//	display(T);
	printMST(T);
	return 0;
}
