#include <stdio.h>
#include "../storages/AdjacencyMatrixGraph.h"
#define MAX_VERTICES 100
#define MULTIPLE_EDGE 'M'
#define SINGLE_EDGE 'S'

int rank[MAX_VERTICES];
List list;

void ranking(Graph G){
	int d[MAX_VERTICES], x;
	List S1;
	initList(&S1);
	
	for(x = 1; x <= G.nbVertices; x++){
		d[x] = getIndegree(G, x);
		if(d[x] == 0)
			add(&S1, x);
	}
	
	int k = 0;
	while(S1.size > 0){
		List S2;
		initList(&S2);
		
		int i;
		for(i = 1; i <= getSize(S1); i++){
			int u = getElementAt(S1, i);
			rank[u] = k;
			
			add(&list, u); // topological sort
			
			List adjList = getAdjacentVertices(G, u);
			
			int j;
			for(j = 1; j <= adjList.size; j++){
				int v = getElementAt(adjList, j);
				d[v]--;
				if(d[v] == 0)
					add(&S2, v);
			}
		}
		k++;
		S1 = S2;
	}
}

int main(){
	Graph G;
	int nbVertices, nbEdges, edge, u, v, s, i;
	char graphType, edgeType;
	FILE *file;
	file = fopen("../data/ranking.txt", "r");
	
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
	
	ranking(G);
	for(u = 1; u <= nbVertices; u++)
		printf("rank[%d] = %d\n", u, rank[u]);
	
	printf("Topological sort: ");
	for(u = 1; u <= list.size; u++)
		printf("%d ", getElementAt(list, u));
	
	fclose(file);
	return 0;
}
