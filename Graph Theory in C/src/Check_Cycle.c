// Check a graph contains cycle or not by using dfs algorithm combined with coloring graph
#include <stdio.h>
#include "../storages/AdjacencyMatrixGraph.h"
#define WHITE 0 // represent for a vertex which have not visited yet
#define GRAY 1 // represent for a vertex which is visiting (it visited, but its neighbors do not visit)
#define BLACK 2 // represent for a vertex which visited (it and its neighbors visited)

int color[100];
int cycle;

int dfs1(Graph *G, int u){
	int i;
	if(color[u] == GRAY)
		return 1;
	color[u] = GRAY; // visiting u
//	printf("%d\n", u);
	List list = neighbors(G,u);
	for(i = 1; i <= Size(&list); ++i){
		int y = element_at(&list,i);
		if(color[y] != BLACK && dfs1(G,y))
			return 1; // detected the cycle
		if(color[y] == WHITE)
			y = dfs1(G,y);
	}
	color[u] = BLACK; // visited u
	return 0;
}

void dfs2(Graph *G, int u){
	int v;
	color[u] = GRAY; // visiting u
//	printf("%d\n", u);
	List list = neighbors(G,u);
	for(v = 1; v <= Size(&list); ++v){
		int y = element_at(&list,v);
		if(color[y] == GRAY){
			cycle = 1; // detected the cycle
			return;
		}
		if(color[y] == WHITE)
			dfs2(G,y);
	}
	color[u] = BLACK; // visited u
}

int contains_cycle(Graph *G){
	int i;
	for(i = 1; i <= G->n; ++i)
		color[i] = WHITE;
	cycle = 0;
	for(i = 1; i <= G->n; ++i)
		if(color[i] == WHITE)
			dfs2(G,i);
	return cycle;
} 

int main(){
	Graph G;
	int i;
	init_graph(&G, 5, 'D');
	addEdgeSingle(&G, 2, 4);
	addEdgeSingle(&G, 4, 1);
	addEdgeSingle(&G, 1, 3);
	addEdgeSingle(&G, 3, 5);
	addEdgeSingle(&G, 5, 2);
	addEdgeSingle(&G, 1, 5);
	// testing dfs1()
	/*
	for(i = 1; i <= 5; ++i)
		color[i] = WHITE;
	if(dfs1(&G,1))
		printf("The graph contains cycle.");
	else
		printf("The graph do not contain cycle.");
	*/
		
	// testing dfs2()
	if(contains_cycle(&G))
		printf("The graph contains cycle.");
	else
		printf("The graph do not contain cycle.");
	return 0;
}
