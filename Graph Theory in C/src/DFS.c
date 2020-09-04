#include <stdio.h>
#define MAX_VERTICES 50
#define MAX_ELEMENTS 50

// represent a List
typedef struct{
	int Elements[MAX_ELEMENTS];
	int last;
} List;

void make_null(List *L){
	L->last = 0;
}

void push_back(List *L, int x){
	L->Elements[L->last] = x;
	++L->last;
}

int element_at(List *L, int i){
	return L->Elements[i-1];
}

int Size(List *L){
	return L->last;
}

// represent a Stack
typedef struct{
	int data[MAX_ELEMENTS];
	int size;
} Stack;

void make_null_stack(Stack *S){
	S->size = 0;
}

void push(Stack *S, int x){
	S->data[S->size] = x;
	++S->size;
}

int top(Stack *S){
	return S->data[S->size-1];
}

void pop(Stack *S){
	--S->size;
}

int empty(Stack *S){
	return S->size == 0;
}

// represent an adjacency matrix graph
typedef struct{
	int n;
	int A[MAX_VERTICES][MAX_VERTICES]; 
} Graph;

void init_graph(Graph *G, int n){
	int i, j;
	G->n = n;
	for(i = 1; i <= n; ++i)
		for(j = 1; j <= n; ++j)
			G->A[i][j] = 0;
}

void add_edge(Graph *G, int x, int y){
	G->A[x][y] += 1;
	G->A[y][x] += 1;
}

int degree(Graph *G, int x){
	int deg = 0, y;
	for(y = 1; y <= G->n; ++y)
		if(G->A[x][y] == 1)
			deg += G->A[x][y];
	return deg;
}

int adjacent(Graph *G, int x, int y){
	return G->A[x][y] > 0;
}

List neighbors(Graph *G, int x){
	int y;
	List list;
	make_null(&list);
	for(y = 1; y <= G->n; ++y)
		if(adjacent(G,x,y))
			push_back(&list,y);
	return list;
}

int mark[MAX_VERTICES];

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
	int n, m, e, u, v, s;
	FILE *file;
	file = fopen("../data/graph.txt", "r");
	fscanf(file, "%d%d", &n, &m);
	init_graph(&G,n);
	for(e = 1; e <= m; ++e){
		fscanf(file,"%d%d", &u, &v);
		add_edge(&G,u,v);
	}
	printf("Enter a vertex to start: ");
	scanf("%d", &s);
	dfs(&G,1);
	return 0;
}
