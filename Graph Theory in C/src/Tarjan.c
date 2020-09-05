#include <stdio.h>
#include "../storage/AdjacencyMatrixGraph.h"
#include "../storage/Stack.h"
#define MULTIPLE_EDGE 'M'
#define SINGLE_EDGE 'S'

int min(int a, int b){
	return a < b ? a:b;
}

int num[MAX_VERTICES]; // storage the index of all vertices during traversing
int min_num[MAX_VERTICES]; // min index
int on_stack[MAX_VERTICES]; // mark a vertex is on stack or not 
int idx; // assign the index for num[]
Stack S;

void tarjan(Graph *G, int x){
	int j;
	num[x] = idx;
	min_num[x] = idx;
	++idx;
	push(&S,x);
	on_stack[x] = 1; // x is on stack
	List list = neighbors(G,x);
	for(j = 1; j <= Size(&list); ++j){
		int y = element_at(&list,j);
		if(num[y] == -1){
			tarjan(G,y);
			min_num[x] = min(min_num[x], min_num[y]);
		}
		if(on_stack[y] == 1)
			min_num[x] = min(min_num[x], num[y]);
	}
	if(num[x] == min_num[x]){
		int w;
		do{
			w = top(&S);
			printf("%d\n", w);
			pop(&S);
			on_stack[w] = 0; // remove w from stack
		} while(w != x);
	}
}

int main(){
	Graph G;
	int nbVertices, nbEdges, edge, u, v, s;
	char graphType, edgeType;
	FILE *file;
	file = fopen("../data/graph1.txt", "r");
	
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
//	display(G);

	for(v = 1; v <= nbVertices; ++v){
		num[v] = -1;
		on_stack[v] = 0;
	}
	make_null_stack(&S);
	idx = 1;
	
//	printf("Enter a vertex to start: ");
//	scanf("%d", &s);
//	tarjan(&G,s);
	
	for(v = 1; v <= nbVertices; ++v)
		if(num[v] == -1)
			tarjan(&G,v);
	return 0;
}
