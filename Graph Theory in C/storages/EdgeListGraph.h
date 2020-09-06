#include <stdio.h>
#include "List.h"
#define MAX_EDGE 100

// represent an edge
typedef struct{
	int u, v, w;
} Edge;

// represent an edge list graph
typedef struct{
	int nbVertices, nbEdges; // number of vertices and edges
	Edge edges[MAX_EDGE]; // list of edges
} Graph;

// initializing the edge list graph
void initGraph(Graph *G, int nbVertices){
	G->nbVertices = nbVertices;
	G->nbEdges = 0;
}

// display the graph
void display(Graph G){
	int e;
	for(e = 0; e < G.nbEdges; e++){
		if(G.edges[e].w != 0){
			printf("(%d, %d) = %d\n", G.edges[e].u, G.edges[e].v, G.edges[e].w);
		}
		else{
			printf("(%d, %d) = %d\n", G.edges[e].u, G.edges[e].v, 0);
		}
	}
}

void addEdge(Graph *G, int u, int v, int w){
	if((u < 1 && u > G->nbVertices) && (v < 1 && v > G->nbVertices))
        return;
	if(w != 0){
		G->edges[G->nbEdges].u = u;
		G->edges[G->nbEdges].v = v;
		G->edges[G->nbEdges].w = w;
		G->nbEdges++;
	}
	else{
		G->edges[G->nbEdges].u = u;
		G->edges[G->nbEdges].v = v;
		G->nbEdges++;
	}
}

int getDegree(Graph G, int u){
	int e, deg = 0;
	for(e = 1; e <= G.nbEdges; e++)
		if(G.edges[e].u == u || G.edges[e].v == u)
			deg++;
	return deg;
}

int isAdjacent(Graph G, int u, int v){
	int e;
	for(e = 0; e < G.nbEdges; e++)
		if((G.edges[e].u == u && G.edges[e].v == v) || 
			(G.edges[e].u == v && G.edges[e].v == u))
			return 1;
	return 0;
}

List getAdjacentVertices(Graph G, int u){
	int v;
	List adjList;
	initList(&adjList);
	for(v = 1; v <= G.nbVertices; v++)
		if(isAdjacent(G, u, v))
			add(&adjList, v);
	return adjList;
}
