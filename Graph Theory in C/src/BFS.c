#include <stdio.h>
#include "../storage/Queue.h"
#include "../storage/AdjacencyMatrixGraph.h"
#define MULTIPLE_EDGE 'M'
#define SINGLE_EDGE 'S'

void bfs1(Graph *G, int s){
	Queue Q;
	int i;
	make_null_queue(&Q);
	for(i = 1; i <= G->n; ++i)
		mark[i] = 0;
	push(&Q,s);
	printf("Visit %d\n", s);
	mark[s] = 1;
	while(!empty(&Q)){
		int u = top(&Q);
		pop(&Q);
		List list = neighbors(G,u);
		for(i = 1; i <= Size(&list); ++i){
			int v = element_at(&list, i);
			if(mark[v] == 0){
				printf("Visit %d\n", v);
				mark[v] = 1;
				push(&Q,v);
			}
		}
	}
}

void bfs2(Graph *G, int x){
	Queue Q;
	int i;
	make_null_queue(&Q);
	for(i = 1; i <= G->n; ++i)
		mark[i] = 0;
	push(&Q,x);
	mark[x] = 1;
	while(!empty(&Q)){
		int u = top(&Q);
		pop(&Q);
		printf("Visit %d\n", u);
		List list = neighbors(G,u);
		for(i = 1; i <= list.size; ++i){
			int v = element_at(&list, i);
			if(mark[v] == 0){
				mark[v] = 1;
				push(&Q,v);
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
//	bfs1(&G, s);
	bfs2(&G, s);
	return 0;
}
