#include <stdio.h>
#include "../storage/Stack.h"
#include "../storage/AdjacencyMatrixGraph.h"
#define MULTIPLE_EDGE 'M'
#define SINGLE_EDGE 'S'

void dfs1(Graph *G, int s){
	int i;
	Stack S;
	for(i = 1; i <= G->n; ++i)
		mark[i] = 0;
	make_null_stack(&S);
	push(&S,s);
	while(!empty(&S)){
		int u = top(&S);
		pop(&S);
		if(mark[u] == 1)
			continue;
		printf("Visit %d\n", u);
		mark[u] = 1;
		List list = neighbors(G,u);
		for(i = 1; i <= Size(&list); ++i){
			int y = element_at(&list,i);
			push(&S,y);
		}
	}
}

// dfs algorithm using recrusion
void dfs2(Graph *G, int x){
	int i;
	if(mark[x] == 1)
		return;
	printf("Visit %d\n", x);
	mark[x] = 1;
	List list = neighbors(G,x);
	for(i = Size(&list); i >= 1; --i){
		int y = element_at(&list,i);
		dfs2(G,y);
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
	
	init_graph(&G, nbVertices, graphType);
	
	if(edgeType == MULTIPLE_EDGE){
		for(edge = 1; edge <= nbEdges; ++edge){
			fscanf(file,"%d%d", &u, &v);
			addEdgeMultiple(&G,u,v);
		}
	}
	else{
		for(edge = 1; edge <= nbEdges; ++edge){
			fscanf(file,"%d%d", &u, &v);
			addEdgeSingle(&G,u,v);
		}
	}
	
	printf("Enter a vertex to start: ");
	scanf("%d", &s);
	dfs1(&G, s);
	
	// test dfs2()
	/*
	int i;
	for(i = 1; i <= nbVertices; ++i)
		mark[i] = 0;
	dfs2(&G, s); */
	return 0;
}
