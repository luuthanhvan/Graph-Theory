#include <stdio.h>
#include "../storages/EdgeListGraph.h"
#define MAX_VERTICES 50
#define NO_EDGE 0

void swap(Edge *edge1, Edge *edge2){
	Edge tmp;
	tmp = *edge1;
	*edge1 = *edge2;
	*edge2 = tmp;
}

void sort(Graph *G){
	int i, j;
	for(i = 0; i <= G->nbEdges-2; i++)
		for(j = i+1; j <= G->nbEdges-1; j++)
			if(G->edges[j].w < G->edges[i].w){
				swap(&G->edges[j], &G->edges[i]);
			/*	Edge tmp;
				tmp = G->edges[j];
				G->edges[j] = G->edges[i];
				G->edges[i] = tmp; */
			}
}

int parent[MAX_VERTICES];

int findRoot(int u){
	while(u != parent[u])
		u = parent[u];
	return u;
}

int kruskal(Graph G, Graph *T){
	int u, v, w, root_u, root_v, e,  sumW = 0;
	sort(&G);
	initGraph(T, G.nbVertices);
	
	for(u = 1; u <= G.nbVertices; u++)
		parent[u] = u;
	
	for(e = 0; e < G.nbEdges; e++){
		u = G.edges[e].u;
		v = G.edges[e].v;
		w = G.edges[e].w;
		root_u = findRoot(u);
		root_v = findRoot(v);
		
		if(root_u != root_v){
			addEdge(T, u, v, w);
			parent[root_v] = root_u;
			sumW += w;
		}
	}
	return sumW; // sum weight of minimum spanning tree
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
	
	initGraph(&G, nbVertices);
	
	for(edge = 1; edge <= nbEdges; edge++){
		fscanf(file,"%d%d%d", &u, &v, &w);
		addEdge(&G, u, v, w);
	}
	
	int sumWeight = kruskal(G, &T);
	printf("Sum weight: %d\n", sumWeight);
	display(T); // print minimum spanning tree
	
	fclose(file);
	return 0;
}
