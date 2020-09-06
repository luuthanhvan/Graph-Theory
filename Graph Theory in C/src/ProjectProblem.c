#include <stdio.h>
#include "../storages/AdjacencyMatrixGraph.h"
#include "../storages/Queue.h"
#define MAX_VERTICES 100
#define MINIMUM -99999
#define MAXIMUM 99999

int max(int num1, int num2){
	return num1 > num2 ? num1 : num2;
}

int min(int num1, int num2){
	return num1 < num2 ? num1 : num2;
}

void toposort(Graph G, List *list){
	int d[MAX_VERTICES], u;
	Queue Q;
	initQueue(&Q);
	
	for(u = 1; u <= G.nbVertices; u++){
		d[u] = getIndegree(G, u);
		if(d[u] == 0)
			push(&Q, u);
	}
	
	while(!empty(Q)){
		int u = top(Q);
		pop(&Q);
		
		add(list, u); // store topo sort
		
		List adjList = getAdjacentVertices(G, u);
		int j;
		for(j = 1; j <= adjList.size; j++){
			int v = getElementAt(adjList, j);
			d[v]--;
			if(d[v] == 0)
				push(&Q, v);
		}
	}
}

/*
file jobList.txt:
- first line: the number of job
- other lines:
	+ first column: finish time a job
	+ second column: the previous job 
*/

int main(){
	Graph G;
	int nbVertices, edge, u, v, s, i, j;
	int d[MAX_VERTICES], deg;
	List list;
	char graphType, edgeType;
	FILE *file;
	file = fopen("../data/joblist.txt", "r");
	
	graphType = fgetc(file);
	edgeType = fgetc(file);
	
	fscanf(file, "%d", &nbVertices);
	
	initGraph(&G, nbVertices+2, graphType); // add two nodes alpha and beta into graph
	
	for(u = 1; u <= nbVertices; u++){
		fscanf(file, "%d", &d[u]);
		do{
			fscanf(file, "%d", &v);
			if(v > 0)
				addEdgeSingle(&G, v, u, 0);
		}while(v > 0);
	}

	// add edge (alpha, u) | u vertices have indegree is zero
	for(u = 1; u <= nbVertices; u++){
		deg = getIndegree(G, u);
		if(deg == 0)
			addEdgeSingle(&G, nbVertices+1, u, 0);
	}
	
	// add edge (u, beta) | u vertices have outdegree is zero
	for(u = 1; u <= nbVertices; u++){
		deg = getOutdegree(G, u);
		if(deg == 0)
			addEdgeSingle(&G, u, nbVertices+2, 0);
	}
	
	toposort(G, &list);
	
	// calculating t[u]
	int t[MAX_VERTICES];
	t[nbVertices+1] = 0; // t[alpha] = 0
	d[nbVertices+1] = 0; // d[alpha] = 0
	for(j = 2; j <= list.size; j++){
		u = list.elements[j];
		t[u] = MINIMUM;
		for(v = 1; v <= nbVertices+1; v++)
			if(G.A[v][u] != 0)
				t[u] = max(t[u], t[v] + d[v]);
	}
	
	// calculating T[u]
	int T[MAX_VERTICES];
	T[nbVertices+2] = t[nbVertices+2]; // T[beta] = t[beta]
	for(i = list.size-2; i >= 1; i--){
		u = list.elements[i];
		T[u] = MAXIMUM;
		for(v = 1; v <= nbVertices+2; v++)
			if(G.A[u][v] != 0)
				T[u] = min(T[u], T[v] - d[u]);
	}
	
	/*
	printf("Topo: ");
	for(j = 1; j <= list.size; j++)
		printf("%d ", getElementAt(list,j)); */
		
	for(u = 1; u <= nbVertices+2; u++){
		printf("t[%d] = %d\tT[%d] = %d\n", u, t[u], u, T[u]);
	}
		
	fclose(file);
	return 0;
}
