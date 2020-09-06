#include <stdio.h>
#include "../storages/Stack.h"
#include "../storages/AdjacencyMatrixGraph.h"
#define MULTIPLE_EDGE 'M'
#define SINGLE_EDGE 'S'

void dfs1(Graph G, int s){
	int i;
	Stack S;
	
	// init all vertices do not visit
	for(i = 1; i <= G.nbVertices; i++)
		mark[i] = 0;
		
	initStack(&S);
	
	// push s into Stack
	push(&S, s);
	
	// while Stack does not empty
	while(!empty(S)){
		int u = top(S); // get the vertex at the top of Queue
		pop(&S); // remove it
		
		// if u is visited, then skip it
		if(mark[u] == 1)
			continue;
			
		printf("Visit %d\n", u);
		mark[u] = 1; // else visited u
		
		// get all adjacent vertices
		List adjList = getAdjacentVertices(G, u);
		
		// traversing all adjacent vertices
		for(i = 1; i <= adjList.size; i++){
			int y = getElementAt(adjList,i);
			push(&S, y); // push y into Stack
		}
	}
}

// dfs algorithm using recrusion
void dfs2(Graph G, int x){
	int i;
	// if x is visited, stop
	if(mark[x] == 1)
		return;
	printf("Visit %d\n", x);
	mark[x] = 1; // else visted x
	
	// get all adjacent vertices
	List adjList = getAdjacentVertices(G, x);
	
	// traversing all adjacent vertices 
	for(i = adjList.size; i >= 1; i--){
		int y = getElementAt(adjList, i);
		dfs2(G, y); // visit y
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
	dfs1(G, s);
	
	// test dfs2()
	/*	
	int i;
	for(i = 1; i <= nbVertices; ++i)
		mark[i] = 0;
	dfs2(G, s); */
	
	fclose(file);
	return 0;
}
