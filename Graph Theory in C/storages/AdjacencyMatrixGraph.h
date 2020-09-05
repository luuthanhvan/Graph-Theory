#include <stdio.h>
#include "List.h"
#define MAX_VERTICES 100
#define DIRECTED 'D'
#define UNDIRECTED 'U'

int mark[MAX_VERTICES];

// represent an adjacency matrix graph
typedef struct{
	int nbVertices;
	int A[MAX_VERTICES][MAX_VERTICES];
	char directed;
} Graph;

// initializing the adjacency matrix graph
void initGraph(Graph *G, int nbVertices, char directed){
	int u, v;
	G->nbVertices = nbVertices;
	G->directed = directed;
	for(u = 1; u <= nbVertices; u++)
		for(v = 1; v <= nbVertices; v++)
			G->A[u][v] = 0;
}

// display the graph
void display(Graph G){
	int u, v;
	for(u = 1; u <= G.nbVertices; u++){
		for(v = 1; v <= G.nbVertices; v++){
			printf("%d ", G.A[u][v]);
		}
		printf("\n");
	}
}

// add edge for a graph which have multiple edges
// an edge: (u, v) = 1 || (x > 1) || w
void addEdgeMultiple(Graph *G, int u, int v, int w){
	// if the edge have the weight on it (u, v) = w
	if(w != 0){
		if(G->directed == DIRECTED){
			G->A[u][v] = w;
		}
		else{
			G->A[u][v] = w;
			G->A[v][u] = w;
		}
	}
	else{ // else (u, v) = 1 || (x > 1)
		if(G->directed == DIRECTED){
			G->A[u][v] += 1;
		}
		else{
			G->A[u][v] += 1;
			G->A[v][u] += 1;
		}	
	}
}

// add edge for a graph which have single edge
// an edge: (u, v) = w || 1
void addEdgeSingle(Graph *G, int u, int v, int w){
	// if the edge have the weight on it (u, v) = w
	if(w != 0){
		if(G->directed == DIRECTED){
			G->A[u][v] = w;
		}
		else{
			G->A[u][v] = w;
			G->A[v][u] = w;
		}
	}
	else{ // else (u, v) = 1
		if(G->directed == DIRECTED){
			G->A[u][v] = 1;
		}
		else{
			G->A[u][v] = 1;
			G->A[v][u] = 1;
		}	
	}
}

int isAdjacent(Graph G, int u, int v){
	return G.A[u][v] > 0;
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

// get indegree of a directed graph (indegree >< outdegree)
int getIndegree(Graph G, int u){
	int v, deg = 0;
	for(v = 1; v <= G.nbVertices; v++)
		if(isAdjacent(G, v, u))
			deg++;
	return deg;
}

// get outdegree of a graph
int getOutdegree(Graph G, int u){
	int v, deg = 0;
	for(v = 1; v <= G.nbVertices; v++)
		if(isAdjacent(G, u, v))
			deg++;
	return deg;
}

// get degree of a undirected graph (indegree = outdegree)
int getDegree(Graph G, int u){
	return getAdjacentVertices(G, u).size;
}
