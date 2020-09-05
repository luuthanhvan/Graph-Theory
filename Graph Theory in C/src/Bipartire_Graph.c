// Check a graph is a bipartire graph or not by using dfs algorithm combined with coloring graph
#include <stdio.h>
#include "../storages/AdjacencyMatrixGraph.h"
#define WHITE -1 // represent for a vertex which have not visited yet
#define BLUE 0 // represent for a vertex which visited and coloring blue
#define RED 1 // represent for a vertex which visited and coloring red

int color[100];
int conflict;

int dfs1(Graph *G, int u, int c){
	int v;
	color[u] = c;
//	printf("Visit %d\n", u);
	List list = neighbors(G,u);
	for(v = 1; v <= Size(&list); ++v){
		int y = element_at(&list,v);
		if(color[y] == WHITE)
			y = dfs1(G,y,!c);
		else
			if(color[y] == c)
				return 1; // conflict
	}
}

void dfs2(Graph *G, int u, int c){
	int v;
	if(color[u] == WHITE){
		color[u] = c; // coloring u
//		printf("%d\n", u);
		List list = neighbors(G,u);
		for(v = 1; v <= Size(&list); ++v){
			int y = element_at(&list,v);
			dfs2(G,y,!c);
		}
	}
	else
		if(color[u] != c){
			conflict = 1;
			return;
		}
}

int contains_cycle(Graph *G){
	int i;
	for(i = 1; i <= G->n; ++i)
		color[i] = WHITE;
	conflict = 0;
	for(i = 1; i <= G->n; ++i)
		if(color[i] == WHITE)
			dfs2(G, i, BLUE);
	return conflict;
} 

int main(){
	Graph G;
	int i;
	init_graph(&G, 6, 'U');
	addEdgeSingle(&G,1, 3, 0);
	addEdgeSingle(&G,1, 4, 0);
	addEdgeSingle(&G,3, 4, 0);
	addEdgeSingle(&G,3, 5, 0);
	addEdgeSingle(&G,4, 2, 0);
	addEdgeSingle(&G,5, 2, 0);
	
	// testing dfs2()
	if(contains_cycle(&G))
		printf("The graph is not a bipartire graph.");
	else
		printf("The graph is a bipartire graph.");

	// testing dfs1()
	/*
	for(i = 1; i <= 6; ++i)
		color[i] = WHITE;
	if(dfs1(&G, 1, BLUE))
		printf("The graph is not a bipartire graph."); // xay ra dung do thi ko phai la do thi phan doi
	else
		printf("The graph is a bipartire graph."); */
	return 0;
}
