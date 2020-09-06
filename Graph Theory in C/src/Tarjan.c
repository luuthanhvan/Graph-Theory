#include <stdio.h>
#include "../storages/AdjacencyMatrixGraph.h"
#include "../storages/Stack.h"
#define MULTIPLE_EDGE 'M'
#define SINGLE_EDGE 'S'

int min(int a, int b){
	return a < b ? a : b;
}

int num[MAX_VERTICES]; // storage the index of all vertices during traversing
int minNum[MAX_VERTICES]; // min index
int onStack[MAX_VERTICES]; // mark a vertex is on stack or not 
int idx; // assign the index for num[]
Stack S;

void tarjan(Graph G, int x){
	int j;
	num[x] = idx;
	minNum[x] = idx;
	idx++;
	
	push(&S, x);
	onStack[x] = 1; // x is on stack
	
	List adjList = getAdjacentVertices(G, x);
	
	for(j = 1; j <= adjList.size; j++){
		int y = getElementAt(adjList, j);
		if(num[y] == -1){
			tarjan(G, y);
			minNum[x] = min(minNum[x], minNum[y]);
		}
		if(onStack[y] == 1)
			minNum[x] = min(minNum[x], num[y]);
	}
	if(num[x] == minNum[x]){
		int w;
		do{
			w = top(S);
			printf("%d\n", w);
			pop(&S);
			onStack[w] = 0; // remove w from stack
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
//	display(G);

	for(v = 1; v <= nbVertices; ++v){
		num[v] = -1;
		onStack[v] = 0;
	}
	initStack(&S);
	idx = 1;
	
//	printf("Enter a vertex to start: ");
//	scanf("%d", &s);
//	tarjan(&G,s);
	
	for(v = 1; v <= nbVertices; ++v)
		if(num[v] == -1)
			tarjan(G, v);
			
	fclose(file);
	return 0;
}
