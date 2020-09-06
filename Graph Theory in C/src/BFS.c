#include <stdio.h>
#include "../storages/Queue.h"
#include "../storages/AdjacencyMatrixGraph.h"
#define MULTIPLE_EDGE 'M'
#define SINGLE_EDGE 'S'

void bfs1(Graph G, int s){
	Queue Q;
	int i;
	initQueue(&Q);
	
	// init all vertices do not visit
	for(i = 1; i <= G.nbVertices; i++)
		mark[i] = 0;
	
	// push s into Queue	
	push(&Q,s);
	
	printf("Visit %d\n", s);
	mark[s] = 1; // visited s
	
	// while Queue does not empty
	while(!empty(Q)){
		int u = top(Q); // get the vertex at the top of Queue
		pop(&Q); // remove it
		
		// get all adjacent vertices
		List adjList = getAdjacentVertices(G, u);
		
		// traversing all adjacent vertices
		for(i = 1; i <= adjList.size; i++){
			int v = getElementAt(adjList, i);
			// if there is a vertex v do not visit
			if(mark[v] == 0){
				printf("Visit %d\n", v);
				mark[v] = 1; // visited v
				push(&Q,v); // push v into Queue
			}
		}
	}
}

void bfs2(Graph G, int x){
	Queue Q;
	int i;
	initQueue(&Q);
	
	// init all vertices do not visit
	for(i = 1; i <= G.nbVertices; i++)
		mark[i] = 0;
	
	// push s into Queue
	push(&Q,x);
	mark[x] = 1; // visited s
	
	// while Queue does not empty
	while(!empty(Q)){
		// get the vertex at the top of Queue
		int u = top(Q); 
		pop(&Q); // remove it
		
		printf("Visit %d\n", u);
		
		// get all adjacent vertices
		List adjList = getAdjacentVertices(G,u);
		
		// traversing all adjacent vertices
		for(i = 1; i <= adjList.size; i++){
			int v = getElementAt(adjList, i);
			// if there is a vertex v do not visit
			if(mark[v] == 0){
				mark[v] = 1; // visited v
				push(&Q,v); // push v into Queue
			}
		}
	}
}

int main(){
	Graph G;
	int nbVertices, nbEdges, edge, u, v, s;
	char graphType, edgeType;
	FILE *file;
	file = fopen("../data/graph.txt", "r");
	
	graphType = fgetc(file);
	edgeType = fgetc(file);
	
	fscanf(file, "%d%d", &nbVertices, &nbEdges);
	
	initGraph(&G, nbVertices, graphType);
	
	if(edgeType == MULTIPLE_EDGE){
		for(edge = 1; edge <= nbEdges; edge++){
			fscanf(file,"%d%d", &u, &v);
			addEdgeMultiple(&G, u, v, 0);
		}
	}
	else{
		for(edge = 1; edge <= nbEdges; edge++){
			fscanf(file,"%d%d", &u, &v);
			addEdgeSingle(&G, u, v, 0);
		}
	}
	
	printf("Enter a vertex to start: ");
	scanf("%d", &s);
//	bfs1(&G, s);
	bfs2(G, s);
	
	fclose(file);
	return 0;
}
