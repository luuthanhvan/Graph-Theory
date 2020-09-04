#include <stdio.h>
#define MAX_VERTICES 50
#define MAX_ELEMENTS 50

typedef struct{
	int Elements[MAX_ELEMENTS];
	int size;
} List;

void make_null(List *L){
	L->size = 0;
}

void push_back(List *L, int x){
	L->Elements[L->size] = x;
	++L->size;
}

int element_at(List *L, int i){
	return L->Elements[i-1];
}

int Size(List *L){
	return L->size;
}

typedef struct{
	int front, rear;
	int data[MAX_ELEMENTS];
} Queue;

void make_null_queue(Queue *Q){
	Q->front = 0;
	Q->rear = -1;
}

void push(Queue *Q, int x){
	++Q->rear;
	Q->data[Q->rear] = x;
}

int top(Queue *Q){
	return Q->data[Q->front];
}

void pop(Queue *Q){
	++Q->front;
}

int empty(Queue *Q){
	return Q->front > Q->rear;
}

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
			++deg;
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
//	bfs1(&G, s);
	bfs2(&G, s);
	return 0;
}
