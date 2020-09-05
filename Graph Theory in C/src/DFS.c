#include <stdio.h>
#include "../storage/Stack.h"
#include "../storage/AdjacencyMatrixGraph.h"
#define MULTIPLE_EDGE 'M'
#define SINGLE_EDGE 'S'

void dfs(Graph *G, int s){
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
	dfs(&G, s);
	return 0;
}
